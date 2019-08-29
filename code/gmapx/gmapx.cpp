// gmapx.cpp : Implementation of CGmapxApp and DLL registration.

#include "stdafx.h"
#include "gmapx.h"
#include <comcat.h>
#include <initguid.h>
//#include "Gmapx_i.c"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CGmapxApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x63d13f3a, 0xeabc, 0x48b1, { 0x8b, 0x9e, 0x74, 0x16, 0x34, 0x73, 0x6d, 0x96 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

//×¢²áÌí¼Ó
const CATID CATID_SafeForScripting1 = {0x7dd95801,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}}; 
const CATID CATID_SafeForInitializing1 = {0x7dd95802,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}};

const GUID CDECL BASED_CODE _ctlid = {0x0AD6CBF6, 0xE7E0, 0x466F,{ 0x8a, 0xa3, 0x10, 0xe5, 0x9f, 0x2c, 0xba, 0x0c}};

//0AD6CBF6-E7E0-466F-8AA3-10E59F2CBA0C
// Helper function to create a component category and associated 
// description 
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription) 
{ 
	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ; 
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr); 
	if (FAILED(hr))
		return hr; 
	// Make sure the HKCR\Component Categories\{..catid...} 
	// key is registered 
	CATEGORYINFO catinfo; 
	catinfo.catid = catid; 
	catinfo.lcid = 0x0409 ; // english 
	// Make sure the provided description is not too long. 
	// Only copy the first 127 characters if it is 
	int len = wcslen(catDescription); 
	if (len>127) len = 127;
	wcsncpy(catinfo.szDescription, catDescription, len); 
	// Make sure the description is null terminated 
	catinfo.szDescription[len] = '\0'; 
	hr = pcr->RegisterCategories(1, &catinfo); 
	pcr->Release(); 
	return hr; 
} 
// Helper function to register a CLSID as belonging to a component 
// category 
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid) 
{ 
	// Register your component categories information. 
	ICatRegister* pcr = NULL ; 
	HRESULT hr = S_OK ;
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr); 
	if (SUCCEEDED(hr))
	{ 
		// Register this category as being "implemented" by 
		// the class. 
		CATID rgcatid[1] ; 
		rgcatid[0] = catid; 
		hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
	} 
	if (pcr != NULL) 
		pcr->Release(); 
	return hr;
}
//--------------Ìí¼Ó½áÊø
////////////////////////////////////////////////////////////////////////////
// CGmapxApp::InitInstance - DLL initialization

BOOL CGmapxApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CGmapxApp::ExitInstance - DLL termination

int CGmapxApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	if (FAILED( CreateComponentCategory( CATID_SafeForScripting1, L"Controls that are safely scriptable") )) 
		return ResultFromScode(SELFREG_E_CLASS); 
	if (FAILED( CreateComponentCategory( CATID_SafeForInitializing1, L"Controls safely initializable from persistent data") )) 
		return ResultFromScode(SELFREG_E_CLASS); 
	if (FAILED( RegisterCLSIDInCategory( _ctlid, CATID_SafeForScripting1) ))
		return ResultFromScode(SELFREG_E_CLASS);
	if (FAILED( RegisterCLSIDInCategory( _ctlid, CATID_SafeForInitializing1) )) 
		return ResultFromScode(SELFREG_E_CLASS);
	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
