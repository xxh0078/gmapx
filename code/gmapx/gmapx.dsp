# Microsoft Developer Studio Project File - Name="gmapx" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=gmapx - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gmapx.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gmapx.mak" CFG="gmapx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gmapx - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gmapx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gmapx - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gmapx - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gmapx - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"../bin/gmapx.ocx"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=\work\gmapx1\gmapx\code\bin\gmapx.ocx
InputPath=\work\gmapx1\gmapx\code\bin\gmapx.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gmapx - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../bin/gmapx.ocx" /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=\work\gmapx1\gmapx\code\bin\gmapx.ocx
InputPath=\work\gmapx1\gmapx\code\bin\gmapx.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gmapx - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Ext "ocx"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\gmapx.ocx
InputPath=.\DebugU\gmapx.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gmapx - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\gmapx.ocx
InputPath=.\ReleaseU\gmapx.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "gmapx - Win32 Release"
# Name "gmapx - Win32 Debug"
# Name "gmapx - Win32 Unicode Debug"
# Name "gmapx - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgMapSymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\gmapx.cpp
# End Source File
# Begin Source File

SOURCE=.\gmapx.def
# End Source File
# Begin Source File

SOURCE=.\gmapx.odl
# End Source File
# Begin Source File

SOURCE=.\gmapx.rc
# End Source File
# Begin Source File

SOURCE=.\GmapxCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\GmapxPpg.cpp
# End Source File
# Begin Source File

SOURCE=.\InputBox.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgMapSymbol.h
# End Source File
# Begin Source File

SOURCE=.\DlgProperty.h
# End Source File
# Begin Source File

SOURCE=.\gmapx.h
# End Source File
# Begin Source File

SOURCE=.\GmapxCtl.h
# End Source File
# Begin Source File

SOURCE=.\GmapxPpg.h
# End Source File
# Begin Source File

SOURCE=.\InputBox.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\gmapx.ico
# End Source File
# Begin Source File

SOURCE=.\GmapxCtl.bmp
# End Source File
# End Group
# Begin Group "MapEngine"

# PROP Default_Filter ""
# Begin Group "VOSBase"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\include\agg-2.5\src\agg_vcgen_contour.cpp"
# End Source File
# Begin Source File

SOURCE="..\include\agg-2.5\src\agg_vcgen_markers_term.cpp"
# End Source File
# Begin Source File

SOURCE="..\include\agg-2.5\src\agg_vcgen_stroke.cpp"
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\bspng.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\bspng.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\MD5.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\MD5.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\PngImage.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\PngImage.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\Project.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\Project.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSBase.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSDefine.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSFile.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSFile.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSImage.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSImage.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VosTime.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VosTime.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSURL.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSURL.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\VOSBase\VOSUtil.h
# End Source File
# End Group
# Begin Group "MapDisp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapBlockUnit.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapBlockUnit.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapData.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapData.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapDataDown.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapDataDown.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapDisp.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapDisp.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapDispLayer.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapDisp\MapDispLayer.h
# End Source File
# End Group
# Begin Group "MapBase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\MapEngine\MapBase\FourTree.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\FourTree.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\MapBase.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\MapBase.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\MapDefine.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\MapFourTree.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\MapFourTree.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\MapUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\MapUtil.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\SqliteDB.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapBase\SqliteDB.h
# End Source File
# End Group
# Begin Group "MapLayer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\MapEngine\MapLayer\BackLayer.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\BackLayer.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapAround.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapAround.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapLayer.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapLayer.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapLeyerMan.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapLeyerMan.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapLine.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapLine.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPoi.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPoi.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPoiInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPoiInfo.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPoint.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPoiRes.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPoiRes.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPolygon.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapPolygon.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapRule.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapRule.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapText.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapLayer\MapText.h
# End Source File
# End Group
# Begin Group "MapCtrol"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapButton.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapButton.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapComBox.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapComBox.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapCtrl.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapCtrol.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapCtrol.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapDirRule.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapDirRule.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapEdit.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapSymbolEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapSymbolEdit.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapToolAround.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapToolAround.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapToolLine.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapToolLine.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapToolPolygon.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapToolPolygon.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapToolRect.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapToolRect.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MapWnd.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MarkMapPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\MarkMapPoint.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\SlideButton.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\SlideButton.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\UrlLink.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapCtrol\UrlLink.h
# End Source File
# End Group
# Begin Group "MapOffSet"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\MapEngine\MapOffSet\MapOffSet.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapOffSet\MapOffSet.h
# End Source File
# End Group
# Begin Group "MIF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\MapEngine\mif\dbfFile.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapField.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapField.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapFields.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapFields.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapParts.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapParts.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapPoints.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapPoints.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapRecordSet.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapRectangle.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapRectangle.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapTableDesc.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MapTableDesc.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\mifdefine.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MifMan.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\MifMan.h
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\shpFile.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\mif\shpFile.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\MapEngine\MapEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\MapEngine\MapEngine.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
