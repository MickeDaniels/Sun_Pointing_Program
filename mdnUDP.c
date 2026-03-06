#include <ansi_c.h>
#include <winsock.h>
#include "UDP.h"



int UDPOpen (int port, int *socketHandle)
{
	SOCKADDR_IN sin;
	WORD wVersionRequested; 
	WSADATA wsaData; 
	int err, t = 1; 
	char ttl = 32;  
	
	unsigned long u = 0;
	
	wVersionRequested = MAKEWORD(1, 1); 
	if((err = WSAStartup(wVersionRequested, &wsaData)) != 0)
	{
		WSACleanup();
		return err;
	}
	
	
	// Open a socket
	*socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	  
	if(*socketHandle == INVALID_SOCKET)
	{
		err = WSAGetLastError();
		closesocket(*socketHandle);
		WSACleanup();
		return err;
	}
	

	
	
	/*  MDN
	// bind the socket to an Address and Port
	sin.sin_family = AF_INET; 
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if((err = bind(*socketHandle, (LPSOCKADDR)&sin, sizeof(sin))) != 0)
	{
		err = WSAGetLastError();
		closesocket(*socketHandle);
		WSACleanup();
		return err;
	}
	
	*/
	
	
	// Set the socket to Blocking I/O
	if (ioctlsocket(*socketHandle, FIONBIO, &u) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}//ioctlsocket(*socketHandle, FIONBIO, &u);
	
	
	
	
	// Set the socket to Broadcast
	if((setsockopt(*socketHandle, SOL_SOCKET, SO_BROADCAST, (char*)&t, sizeof(int)))== SOCKET_ERROR)
	{
		return WSAGetLastError();
	}//setsockopt(*socketHandle, SOL_SOCKET, SO_BROADCAST, (char*)&t, sizeof(int));
	
   
	
	/////  MDN  ( Sets the "Time To Live"  parameter for the outgoing multicast datagrams) //////////
	
	if((setsockopt(*socketHandle, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl)))== SOCKET_ERROR)
	{
		return WSAGetLastError();
	}


	return 0;
}

 


int UDPRead (int socketHandle, void *data, int maxSize, int timeout)
{
	int fromSize;
	SOCKADDR_IN sin;
	
	fromSize = sizeof(sin);
	// Set the receive timeout period to the one specified by the timeout parameter.
	setsockopt(socketHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(int));
	// Recieve the data on the port.
	if(recvfrom(socketHandle, data, maxSize, 0, (LPSOCKADDR)&sin, &fromSize) < 0)
		return WSAGetLastError();
	return 0;
}



int UDPWrite (int socketHandle, void *data, int dataSize, void */*int*/ address, int port)
{
	SOCKADDR_IN sin;
	int err;
	
	// Set the address and port option for the write operation
	sin.sin_family = AF_INET; 
	//sin.sin_addr.s_addr = address; //Modified to handle addressed udp....
	sin.sin_addr.s_addr = inet_addr((char*)address);
	sin.sin_port = htons(port);
	// Write the data out the socket
	if(sendto(socketHandle, data, dataSize, 0, (LPSOCKADDR)&sin, sizeof(SOCKADDR_IN)) < 0)
		return WSAGetLastError();
	return 0;
}




int UDPClose (int socketHandle)
{
	// Close the socket
	closesocket(socketHandle);
	return 0;
}




char *UDPErrorString(int error)
{
	switch(error)
	{
		case 0:
			return "No Error.";
			break;
		case WSAENETDOWN:
			return "The network subsystem has failed.";
			break;
		case WSAEADDRINUSE:
			return "Socket address is already in use.";
			break;
		case WSAEINPROGRESS:
		case WSAENOBUFS:
			return "Another Windows Socket Operation is in Progress.";
			break;
		case WSAEMFILE:
			return "Not Enough Available Socket Resources.";
			break;
		case WSAENOTSOCK:
			return "Not a Socket.";
			break;
		case WSAESHUTDOWN:
			return "The Socket has been Shutdown.";
			break;
		case WSAEMSGSIZE:
			return "The data was to large to fit in the specified buffer and has been truncated.";
			break;
		case WSAECONNABORTED:
			return "The connection has been aborted";
			break;
		case WSAECONNRESET:
			return "The connection was reset by the remote site.";
			break;
		case WSAETIMEDOUT:
			return "The connection timed out.";
			break;
		case WSANOTINITIALISED:
			return "Unknown System Error.";
			break;
		case WSAEACCES:
			return "Unknown System Error.";
			break;
		case WSAEINTR:
			return "Unknown System Error.";
			break;
		case WSAEFAULT:
			return "Unknown System Error.";
			break;
		case WSAENETRESET:
			return "Unknown System Error.";
			break;
		case WSAENOTCONN:
			return "Unknown System Error.";
			break;
		case WSAEOPNOTSUPP:
			return "Unknown System Error.";
			break;
		case WSAEWOULDBLOCK:
			return "Unknown System Error.";
			break;
		case WSAEINVAL:
			return "Unknown System Error.";
			break;
		default:
			return "Unknown System Error.";
			break;
	}
	return "Unknown System Error.";
}
////// MDN

