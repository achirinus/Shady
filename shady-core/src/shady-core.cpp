
#include "Graphics/Mesh.cpp"
#include "Graphics/Shader.cpp"
#include "Graphics/Sprite.cpp"
#include "Graphics/Texture.cpp"
#include "Graphics/Camera2D.cpp"
#include "Graphics/Camera3D.cpp"
#include "Graphics/Renderer2D.cpp"
#include "Graphics/Renderer3D.cpp"
#include "Graphics/Graphics.cpp"
#include "Graphics/ShFont.cpp"
#include "Graphics/Glyph.cpp"
#include "Graphics/Text2D.cpp"
#include "Graphics/Primitives/Line2D.cpp"
#include "Graphics/Primitives/Rectangle.cpp"
#include "Graphics/Primitives/Cube.cpp"
#include "Utils/Win32GL.cpp"
#include "Utils/Win32Window.cpp"
#include "Utils/Timer.cpp"
#include "Utils/ModelLoader.cpp"
#include "Utils/ShadyApp.cpp"
#include "Input/ShMouse.cpp"
#include "Input/ShKeyboard.cpp"
#include "Input/InputManager.cpp"
#include "Main.cpp"


/*

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

GUID psGUID;

BOOL DIEnumDevicesCallback(LPCDIDEVICEINSTANCE devInst, LPVOID value)
{
	if(strCompare(devInst->tszProductName, L"Wireless Controller"))
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