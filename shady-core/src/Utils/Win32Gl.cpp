#include <glew.h>
#include <Windows.h>
#include <Commons.h>
namespace Shady
{

	
	// void Win32LoadFunctions()
	// {
	// 	glClampColor = (_pfshglClampColor)wglGetProcAddress("glClampColor");
	// }

	void Win32GlInit(HDC dc)
	{
		PIXELFORMATDESCRIPTOR pfd = {};
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		
		s32 suggesedFormatIndex = ChoosePixelFormat(dc, &pfd);

		PIXELFORMATDESCRIPTOR suggestedFormat;
		DescribePixelFormat(dc, suggesedFormatIndex, sizeof(PIXELFORMATDESCRIPTOR), &suggestedFormat);
		
		if(SetPixelFormat(dc, suggesedFormatIndex, &pfd) == TRUE)
		{
			HGLRC glRC = wglCreateContext(dc);
			if(glRC)
			{
				wglMakeCurrent(dc, glRC);
				
			}
			else
			{
				//TODO log error
			}
		}
		else
		{
			//TODO log error
		}
	
	}

	
	
}