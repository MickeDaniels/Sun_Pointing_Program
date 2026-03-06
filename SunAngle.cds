<distribution version="10.0.0" name="SunAngle" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{1A3A3739-698D-4781-9B7F-2DE8CFB86EBE}">
		<general appName="SunAngle" outputLocation="c:\sunangle" outputLocationWithVars="c:\sunangle" upgradeBehavior="1" autoIncrement="false" version="1.0.1">
			<arp company="" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="English" showPaths="true" readMe="" license="">
			<dlgstrings welcomeTitle="SunAngle" welcomeText=""/></userinterface>
		<dirs appDirID="100">
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="SunAngle" dirID="100" parentID="2" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="SunAngle" dirID="101" parentID="7" isMSIDir="false" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="c:\data\Sun_Pointing_Program\sunangle.ini" relSourcePath="sunangle.ini" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="c:\data\Sun_Pointing_Program\cvibuild.SunAngle\Release\SunAngle.exe" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="c:\data\Sun_Pointing_Program\SunAngle.uir" relSourcePath="SunAngle.uir" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="100" projectID="0">
				<fileID>1</fileID></projectOutput></fileGroups>
		<shortcuts>
			<shortcut name="SunAngle" targetFileID="1" destDirID="101" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine cvirte="true" instrsup="false" lvrt="false" analysis="false" netvarsup="false" dotnetsup="false" activeXsup="false" lowlevelsup="false" rtutilsup="false" installToAppDir="false"/>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WINXP</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>c:\program files (x86)\national instruments\cvi2010\bin\msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="c:\data\Sun_Pointing_Program\SunAngle.prj" ProjectRelativePath="SunAngle.prj"/></Projects>
		<buildData progressBarRate="1.840264998159735">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.050000000000000</ProductsAdded>
				<DPConfigured>1.250000000000000</DPConfigured>
				<DPMergeModulesAdded>11.279999999999999</DPMergeModulesAdded>
				<DPClosed>41.280000000000001</DPClosed>
				<DistributionsCopied>42.280000000000001</DistributionsCopied>
				<End>54.340000000000003</End></progressTimes></buildData>
	</msi>
</distribution>
