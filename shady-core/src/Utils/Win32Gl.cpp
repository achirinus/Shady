#include <glew.h>
#include <Windows.h>
#include <Commons.h>
namespace Shady
{

	
	// void Win32LoadFunctions()
	// {
	// 	glClampColor = (_pfshglClampColor)wglGetProcAddress("glClampColor");
	// }

	HGLRC Win32GlInit(HDC dc)
	{
		HGLRC result;
		PIXELFORMATDESCRIPTOR pfd = {};
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		
		//TODO maybe store this on the first run so the next ones are faster
		s32 suggesedFormatIndex = ChoosePixelFormat(dc, &pfd);

		PIXELFORMATDESCRIPTOR suggestedFormat;
		DescribePixelFormat(dc, suggesedFormatIndex, sizeof(PIXELFORMATDESCRIPTOR), &suggestedFormat);
		
		if(SetPixelFormat(dc, suggesedFormatIndex, &pfd) == TRUE)
		{
			result = wglCreateContext(dc);
			if(result)
			{
				wglMakeCurrent(dc, result);
				return result;
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
		return result;
	}

	
	
}