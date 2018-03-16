#include <Commons.h>

#include <ShadyGL.h>
#include "ShadyApp.h"
#include "ShString.h"
#include "FileUtils.h"
#include "ModelLoader.h"
#include "StringUtils.h"
#include "ShMath.h"

using namespace Shady;

/*
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

GUID psGUID;


BOOL DIEnumDevicesCallback(LPCDIDEVICEINSTANCE devInst, LPVOID value)
{
	if(StrCompare(devInst->tszProductName, L"Wireless Controller"))
	{
		psGUID = devInst->guidInstance;
	}
	
	return TRUE;
}

BOOL CALLBACK DIEnumDeviceObjectsCallback( 
                      LPCDIDEVICEOBJECTINSTANCE lpddoi,
                      LPVOID pvRef) 
{ 
	DEBUG_OUT_INFO("Obj name: %S", lpddoi->tszName);
	return TRUE;
}

void func()
{
	LPDIRECTINPUT8 dInput;
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
												IID_IDirectInput8, (LPVOID*)&dInput, NULL);

	dInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACKW)DIEnumDevicesCallback,
												 0, DIEDFL_ATTACHEDONLY);

	LPDIRECTINPUTDEVICE8W ps4;
	HRESULT result = dInput->CreateDevice(psGUID, &ps4, NULL);
	DIDEVCAPS psCaps;
	if(result == DI_OK)
	{
		DEBUG_OUT_INFO("PS4 controller created");
		
		psCaps.dwSize = sizeof(DIDEVCAPS);
		ps4->GetCapabilities(&psCaps);
		ps4->EnumObjects(DIEnumDeviceObjectsCallback, 0, DIDFT_ALL);
	}
}

*/

int main(int argc, char* argv[])
{
	
	ShadyApp* app = ShadyApp::GetInstance();
	app->start();
	
	return 0;
}
