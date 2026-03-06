#include "inifile.h"
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "spa.h"
#include "SunAngle.h"
#include <mdnUDP.h>   

# define FIXED_RANGE 995000	 // Max valid range for Posnet


spa_data spa;
static IniText lista;
static int 	second,
			hour,
			minute,
			year,
			day,
			month;

//*******   UDP Parameters    ************
static int 	Posnet_Port, 
			udpHandle;
			
static char *Posnet_Interface;
static char posnet_str[128];

//***************************************

			
static double lat,lon,alt,tzone;			

static int panelHandle;



// function prototypes..........
void SystemInit(void);  
int  udpOpen(int);
int  udpWrite(int, char*, char*);  



int main (int argc, char *argv[])
					
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "SunAngle.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	SystemInit();
	
	 
	if(udpOpen(Posnet_Port) != 0)		// Open UDP connection
	{
	  printf("UDP Open Problem...");
	}
	
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}



int CVICALLBACK quit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			UDPClose (udpHandle);
			QuitUserInterface (0);
			break;
		}
	return 0;
}




void SystemInit()   //	System Initiation form configuration file  
												
{
    // Load system parameters from .ini file
    lista = Ini_New (1);
	Ini_ReadFromFile (lista, "sunangle.ini");
	
	Ini_GetDouble(lista,"Groundstn", "latitude", &lat);
	Ini_GetDouble(lista,"Groundstn", "longitude", &lon);
	Ini_GetDouble(lista,"Groundstn", "alt(msl)", &alt); 
	Ini_GetDouble(lista,"Groundstn", "timezone", &tzone);
	
	Ini_GetInt(lista,  "UDP", "Posnet_Port", &Posnet_Port);
	Ini_GetStringCopy(lista, "UDP", "PosNet_Interface", &Posnet_Interface);
	
	Ini_Dispose (lista);
}	

 


int CVICALLBACK timer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int posnet_chksum=0,
	    index,
		gr_Range,
		x = 0, 
		y = 0, 
		z = 0;
	
	char posnet_chksumstr[8], 
		 x_sign = '+', 
		 y_sign = '+',
		 z_sign = '+',
		 posnet_provider_str[64]="",
		 xyzStr[64]="";
	
	double azimuth, elevation, rad_az, rad_el;
	
	switch (event)
		{
		case EVENT_TIMER_TICK:
			 
			 GetSystemDate (&month, &day, &year);
			 GetSystemTime (&hour, &minute, &second);
			 
			 spa.year 		= year;
			 spa.month 		= month;
			 spa.day 		= day;
			 spa.hour		= hour;
			 spa.minute 	= minute;
			 spa.second 	= second;
			 spa.pressure 	= 1013;
			 
			 spa.delta_t		= 0;
			 spa.timezone		= tzone;    // 1;
			 spa.latitude		= lat;	    // from config file
			 spa.longitude		= lon;      // from config file
			 spa.elevation		= alt;      // from config file
			 spa.temperature 	= 0;
			 spa.slope		 	= 0;
			 spa.azm_rotation 	= 0;
			 spa.atmos_refract 	= 0.5667;
			
			 spa_calculate(&spa);
			 
			 azimuth   = spa.azimuth;
			 elevation = (90-spa.zenith);
	   
			 SetCtrlVal(panelHandle,PANEL_AZIMUTH, azimuth);
			 SetCtrlVal(panelHandle,PANEL_ELEVATION, elevation);
			 
			 // convert degrees to radians
			 rad_az = DegToRad (azimuth);
			 rad_el = DegToRad (elevation);
			
			 // Compute local vector
			 gr_Range = FIXED_RANGE * cos(rad_el);
			 x = gr_Range * sin(HalfPi() - rad_az);
			 y = gr_Range * cos(HalfPi() - rad_az);
			 z = FIXED_RANGE * sin(rad_el);
			 
			 
			 if ( x < 0) 
				 x_sign = '-';
			 
			 if ( y < 0) 
				 y_sign = '-';
			 
			 if ( z < 0) 
				 z_sign = '-';
			 
			 
			 x = abs(x);
			 y = abs(y);
			 z = abs(z);
			 
			 // Create legacy format outstr
	 		 sprintf(xyzStr, "SUN;0;X:%c%07d;Y:%c%07d;Z:%c%07d\r\n", x_sign, x, y_sign, y, z_sign, z);
			 
			 udpWrite(Posnet_Port, Posnet_Interface, xyzStr);      

			 
 		  break;
		}
	
	return 0;
}	


int udpOpen(int port)
{
	 return UDPOpen (port, &udpHandle);
}


int udpWrite(int port, char *interface, char *posnet_str)
{
  	return UDPWrite (udpHandle, posnet_str, strlen(posnet_str), interface, port);  
}			

 

	

	


