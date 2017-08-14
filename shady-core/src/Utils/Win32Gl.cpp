#include <glew.h>
#include <wglew.h>
#include <Windows.h>
#include <Commons.h>
namespace Shady
{

	
	// void Win32LoadFunctions()
	// {
	// 	glClampColor = (_pfshglClampColor)wglGetProcAddress("glClampColor");
	// }
	OpenglInfo getGlInfo()
	{
		OpenglInfo result = {};
		getGlInfo(&result);
		return result;
	}
	void getGlInfo(OpenglInfo* info)
	{
		SH_ASSERT(info);
		const uc8* extStr = glGetString(GL_EXTENSIONS);
		const uc8* verStr = glGetString(GL_VERSION);
		const uc8* shaderVerStr = glGetString(GL_SHADING_LANGUAGE_VERSION);

		const c8* glFirstDigit = findFirstDigit((c8*)verStr);
		const c8* shaderFirstDigit = findFirstDigit((c8*)shaderVerStr);
		info->swapControl = findStr((c8*)extStr, "WGL_EXT_swap_control");

		info->majorGlVersion = charToDigit(glFirstDigit[0]);
		info->minorGlVersion = charToDigit(glFirstDigit[2]);

		info->majorShaderVersion = charToDigit(shaderFirstDigit[0]);
		info->minorShaderVersion = charToDigit(shaderFirstDigit[2]);
	}

	HGLRC Win32GlInit(HDC dc, OpenglInfo* info)
	{
		HGLRC result;

		PIXELFORMATDESCRIPTOR pfd = {};
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cRedBits = 8;
		pfd.cGreenBits = 8;
		pfd.cBlueBits = 8;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		

		//TODO maybe store this on the first run so the next ones are faster
		s32 suggesedFormatIndex = ChoosePixelFormat(dc, &pfd);
		//TODO check if DescribePixelFormat is really needed

		PIXELFORMATDESCRIPTOR suggestedFormat;
		DescribePixelFormat(dc, suggesedFormatIndex, sizeof(PIXELFORMATDESCRIPTOR), &suggestedFormat);
		HGLRC tempRc;
		if(SetPixelFormat(dc, suggesedFormatIndex, &pfd) == TRUE)
		{
			HGLRC tempRc = wglCreateContext(dc);
			if(tempRc)
			{
				wglMakeCurrent(dc, tempRc);
				getGlInfo(info);
				static const int attributes[] = 
				{

				    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				    WGL_CONTEXT_MINOR_VERSION_ARB, 0,
				    WGL_CONTEXT_PROFILE_MASK_ARB,
				    WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 
				    NULL
				};
				glewInit();
				result = wglCreateContextAttribsARB(dc, 0, attributes);
				if(result) 
				{
					wglMakeCurrent(NULL, NULL);
					wglDeleteContext(tempRc);
					wglMakeCurrent(dc, result);
					return result;
				}
				else
				{
					result = tempRc;
					DEBUG_OUT_ERR("OpenGl context creation failed!");
				}
			}
			else
			{
				DEBUG_OUT_ERR("OpenGl context creation failed!");
			}
		}
		else
		{
			DEBUG_OUT_ERR("SetPixelFormat failed!");
		}
		return result;
	}

	
	
}