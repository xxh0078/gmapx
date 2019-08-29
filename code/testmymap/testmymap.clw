; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestmymapDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "testmymap.h"

ClassCount=4
Class1=CTestmymapApp
Class2=CTestmymapDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DLGMOVEMAP
Resource2=IDR_MAINFRAME
Resource3=IDD_TESTMYMAP_DIALOG
Resource4=IDR_MENU1
Class4=CDlgMoveMap
Resource5=IDD_ABOUTBOX

[CLS:CTestmymapApp]
Type=0
HeaderFile=testmymap.h
ImplementationFile=testmymap.cpp
Filter=N

[CLS:CTestmymapDlg]
Type=0
HeaderFile=testmymapDlg.h
ImplementationFile=testmymapDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_GMAPXCTRL1

[CLS:CAboutDlg]
Type=0
HeaderFile=testmymapDlg.h
ImplementationFile=testmymapDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTMYMAP_DIALOG]
Type=1
Class=CTestmymapDlg
ControlCount=1
Control1=IDC_GMAPXCTRL1,{0AD6CBF6-E7E0-466F-8AA3-10E59F2CBA0C},1342242816

[MNU:IDR_MENU1]
Type=1
Class=CTestmymapDlg
Command1=ID_MENUITEM32771
Command2=ID_MENUITEM32775
Command3=ID_MENUITEM32776
Command4=ID_MENUITEM32777
Command5=ID_MENUITEM32778
Command6=ID_MENUITEM32779
Command7=ID_MENUITEM32780
Command8=ID_MENUITEM32772
Command9=ID_MENUITEM32773
Command10=ID_MENUITEM32774
Command11=ID_MENUITEM32781
Command12=ID_MENUITEM32782
Command13=ID_MENUITEM32783
Command14=ID_MENUITEM32784
CommandCount=14

[DLG:IDD_DLGMOVEMAP]
Type=1
Class=CDlgMoveMap
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_BUTTON2,button,1342242816

[CLS:CDlgMoveMap]
Type=0
HeaderFile=DlgMoveMap.h
ImplementationFile=DlgMoveMap.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON2
VirtualFilter=dWC

