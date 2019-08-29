# Microsoft Developer Studio Project File - Name="EasyMap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=EasyMap - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EasyMap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EasyMap.mak" CFG="EasyMap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EasyMap - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "EasyMap - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EasyMap - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "EasyMap - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "EasyMap - Win32 Release"
# Name "EasyMap - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgMapLegend.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMapSingle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMapUnique.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtSymbolSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EasyMap.cpp
# End Source File
# Begin Source File

SOURCE=.\EasyMap.rc
# End Source File
# Begin Source File

SOURCE=.\EasyMapDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\EasyMapView.cpp
# End Source File
# Begin Source File

SOURCE=.\JMComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\JMCOOLMENU.CPP
# End Source File
# Begin Source File

SOURCE=.\JMToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\JMTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\LayersCtrlView.cpp
# End Source File
# Begin Source File

SOURCE=.\LengendCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapField.cpp
# End Source File
# Begin Source File

SOURCE=.\MapFields.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLayers.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLine.cpp
# End Source File
# Begin Source File

SOURCE=.\MapParts.cpp
# End Source File
# Begin Source File

SOURCE=.\MapPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\MapPoints.cpp
# End Source File
# Begin Source File

SOURCE=.\MapPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\MapRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\MapRectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\MapRender.cpp
# End Source File
# Begin Source File

SOURCE=.\MapTableDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\MapTip.cpp
# End Source File
# Begin Source File

SOURCE=.\shpFile.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dbfFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgMapLegend.h
# End Source File
# Begin Source File

SOURCE=.\DlgMapSingle.h
# End Source File
# Begin Source File

SOURCE=.\DlgMapUnique.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtSymbolSet.h
# End Source File
# Begin Source File

SOURCE=.\EasyMap.h
# End Source File
# Begin Source File

SOURCE=.\EasyMapDoc.h
# End Source File
# Begin Source File

SOURCE=.\EasyMapView.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\JMComboBox.h
# End Source File
# Begin Source File

SOURCE=.\JMCOOLMENU.H
# End Source File
# Begin Source File

SOURCE=.\JMToolBar.h
# End Source File
# Begin Source File

SOURCE=.\JMTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\LayersCtrlView.h
# End Source File
# Begin Source File

SOURCE=.\LengendCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapCommand.h
# End Source File
# Begin Source File

SOURCE=.\MapField.h
# End Source File
# Begin Source File

SOURCE=.\MapFields.h
# End Source File
# Begin Source File

SOURCE=.\MapLayer.h
# End Source File
# Begin Source File

SOURCE=.\MapLayers.h
# End Source File
# Begin Source File

SOURCE=.\MapLine.h
# End Source File
# Begin Source File

SOURCE=.\MapParts.h
# End Source File
# Begin Source File

SOURCE=.\MapPoint.h
# End Source File
# Begin Source File

SOURCE=.\MapPoints.h
# End Source File
# Begin Source File

SOURCE=.\MapPolygon.h
# End Source File
# Begin Source File

SOURCE=.\MapRecordSet.h
# End Source File
# Begin Source File

SOURCE=.\MapRectangle.h
# End Source File
# Begin Source File

SOURCE=.\MapRender.h
# End Source File
# Begin Source File

SOURCE=.\MapTableDesc.h
# End Source File
# Begin Source File

SOURCE=.\MapTip.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\shpFile.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\book.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cancel.ico
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\curfind.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\curzinwi.cur
# End Source File
# Begin Source File

SOURCE=.\res\EasyMap.ico
# End Source File
# Begin Source File

SOURCE=.\res\EasyMap.rc2
# End Source File
# Begin Source File

SOURCE=.\res\EasyMapDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
