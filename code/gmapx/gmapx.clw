; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgMapSymbol
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gmapx.h"
CDK=Y

ClassCount=6
Class1=CGmapxCtrl
Class2=CGmapxPropPage

ResourceCount=6
LastPage=0
Resource1=IDD_DLGMAPSYMBOL
Resource2=IDD_DLGPROPERTY
Class3=CDlgMapText
Resource3=IDD_PROPPAGE_GMAPX
Class4=CDlgProperty
Resource4=IDD_ABOUTBOX_GMAPX
Class5=CInputBox
Resource5=IDD_DLGIMPUT
Class6=CDlgMapSymbol
Resource6=IDR_RBTN_MENU

[CLS:CGmapxCtrl]
Type=0
HeaderFile=GmapxCtl.h
ImplementationFile=GmapxCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=IDC_EDIT1

[CLS:CGmapxPropPage]
Type=0
HeaderFile=GmapxPpg.h
ImplementationFile=GmapxPpg.cpp
Filter=D

[DLG:IDD_ABOUTBOX_GMAPX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_GMAPX]
Type=1
Class=CGmapxPropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[MNU:IDR_RBTN_MENU]
Type=1
Class=CGmapxCtrl
Command1=ID_MENUITEM32768
Command2=ID_MENUITEM32769
Command3=ID_MENUITEM32770
CommandCount=3

[CLS:CDlgMapText]
Type=0
HeaderFile=DlgMapText.h
ImplementationFile=DlgMapText.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MENUITEM32768
VirtualFilter=dWC

[DLG:IDD_DLGPROPERTY]
Type=1
Class=CDlgProperty
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631424

[CLS:CDlgProperty]
Type=0
HeaderFile=DlgProperty.h
ImplementationFile=DlgProperty.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST1

[DLG:IDD_DLGIMPUT]
Type=1
Class=CInputBox
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:CInputBox]
Type=0
HeaderFile=InputBox.h
ImplementationFile=InputBox.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInputBox

[DLG:IDD_DLGMAPSYMBOL]
Type=1
Class=CDlgMapSymbol
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_RADIO1,button,1342177289
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_RADIO3,button,1342177289
Control8=IDC_RADIO4,button,1342177289
Control9=IDC_STATIC,button,1342177287

[CLS:CDlgMapSymbol]
Type=0
HeaderFile=DlgMapSymbol.h
ImplementationFile=DlgMapSymbol.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgMapSymbol

