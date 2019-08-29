; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgMapUnique
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "easymap.h"
LastPage=0

ClassCount=14
Class1=CDlgMapSingle
Class2=CDlgPtSymbolSet
Class3=CEasyMapApp
Class4=CAboutDlg
Class5=CEasyMapDoc
Class6=CEasyMapView
Class7=CJMComboBox
Class8=CJMToolBar
Class9=CJMTreeCtrl
Class10=CLayersCtrlView
Class11=CMainFrame
Class12=CMapTip

ResourceCount=9
Resource1=IDR_EASYMAP
Resource2=IDD_DLG_PTSYMBOL
Resource3=IDD_DLG_MAPUNIQUE
Resource4=IDR_MAINFRAME
Resource5=IDD_DLG_LAYERCTRL
Resource6=IDD_ABOUTBOX
Resource7=IDD_DLG_MAPSINGLE
Class13=CDlgMapUnique
Resource8=IDR_MENUPOP
Class14=CDlgMapLegend
Resource9=IDD_DLG_MAPFILL

[CLS:CDlgMapSingle]
Type=0
BaseClass=CPropertyPage
HeaderFile=DlgMapSingle.h
ImplementationFile=DlgMapSingle.cpp
Filter=D
VirtualFilter=idWC
LastObject=CDlgMapSingle

[CLS:CDlgPtSymbolSet]
Type=0
BaseClass=CDialog
HeaderFile=DlgPtSymbolSet.h
ImplementationFile=DlgPtSymbolSet.cpp
LastObject=CDlgPtSymbolSet
Filter=D
VirtualFilter=dWC

[CLS:CEasyMapApp]
Type=0
BaseClass=CWinApp
HeaderFile=EasyMap.h
ImplementationFile=EasyMap.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=EasyMap.cpp
ImplementationFile=EasyMap.cpp
LastObject=CAboutDlg

[CLS:CEasyMapDoc]
Type=0
BaseClass=CDocument
HeaderFile=EasyMapDoc.h
ImplementationFile=EasyMapDoc.cpp
Filter=N
VirtualFilter=DC

[CLS:CEasyMapView]
Type=0
BaseClass=CView
HeaderFile=EasyMapView.h
ImplementationFile=EasyMapView.cpp

[CLS:CJMComboBox]
Type=0
BaseClass=CComboBox
HeaderFile=JMComboBox.h
ImplementationFile=JMComboBox.cpp

[CLS:CJMToolBar]
Type=0
BaseClass=CToolBar
HeaderFile=JMToolBar.h
ImplementationFile=JMToolBar.cpp

[CLS:CJMTreeCtrl]
Type=0
BaseClass=CTreeCtrl
HeaderFile=JMTreeCtrl.h
ImplementationFile=JMTreeCtrl.cpp

[CLS:CLayersCtrlView]
Type=0
BaseClass=CFormView
HeaderFile=LayersCtrlView.h
ImplementationFile=LayersCtrlView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMapTip]
Type=0
BaseClass=CToolTipCtrl
HeaderFile=MapTip.h
ImplementationFile=MapTip.cpp

[DLG:IDD_DLG_MAPSINGLE]
Type=1
Class=CDlgMapSingle
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CMBSTYLE,combobox,1344339971

[DLG:IDD_DLG_PTSYMBOL]
Type=1
Class=CDlgPtSymbolSet
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBOFONT,combobox,1344340227
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DLG_LAYERCTRL]
Type=1
Class=CLayersCtrlView
ControlCount=4
Control1=IDC_LAYERTREE,SysTreeView32,1350631687
Control2=IDC_STATIC2,static,1342177289
Control3=IDC_STATIC1,static,1350565895
Control4=IDC_TAB,SysTabControl32,1342177280

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_SHPADD
Command2=ID_FILE_SAVE
Command3=ID_EDIT_CUT
Command4=ID_MAP_ZOOM_IN
Command5=ID_MAP_ZOOM_OUT
Command6=ID_MAP_ZOOM_WINDOW
Command7=ID_MAP_ZOOM_ALL
Command8=ID_MAP_PAN
Command9=ID_MAP_SRHPT
Command10=ID_MAP_TIP
Command11=IDC_COMBOX_LAYER
Command12=IDC_COMBOX_FIELD
CommandCount=12

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[MNU:IDR_EASYMAP]
Type=1
Class=?
Command1=ID_FILE_SHPADD
Command2=ID_MAP_NOTHING
Command3=ID_MAP_ZOOM_IN
Command4=ID_MAP_ZOOM_OUT
Command5=ID_MAP_ZOOM_WINDOW
Command6=ID_MAP_PAN
Command7=ID_MAP_ZOOM_ALL
Command8=ID_MAP_TIP
Command9=ID_MAP_PTSYMBOL
Command10=ID_MAP_SRHPT
CommandCount=10

[MNU:IDR_MENUPOP]
Type=1
Class=?
Command1=ID_ADD_LAYER
Command2=ID_DEL_LAYER
Command3=ID_ATTRIBUTE_LAYER
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DLG_MAPUNIQUE]
Type=1
Class=CDlgMapUnique
ControlCount=4
Control1=IDC_LISTLEGEND,SysListView32,1350632449
Control2=IDC_CMBFIELD,combobox,1344339971
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BTNSET,button,1342242816

[CLS:CDlgMapUnique]
Type=0
HeaderFile=DlgMapUnique.h
ImplementationFile=DlgMapUnique.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CDlgMapUnique
VirtualFilter=idWC

[DLG:IDD_DLG_MAPFILL]
Type=1
Class=?
ControlCount=0

[CLS:CDlgMapLegend]
Type=0
HeaderFile=DlgMapLegend.h
ImplementationFile=DlgMapLegend.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CDlgMapLegend

