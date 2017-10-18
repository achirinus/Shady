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

	void checkGlError()
	{
		GLenum err = glGetError();
		switch(err)
		{
			case GL_INVALID_ENUM:
			{
				DEBUG_OUT_ERR("OpenGl invalid enum argument error this frame!");
			}break;
			case GL_INVALID_VALUE:
			{
				DEBUG_OUT_ERR("OpenGl invalid value argument error this frame!");
			}break;
			case GL_INVALID_OPERATION:
			{
				DEBUG_OUT_ERR("OpenGl invalid operation error this frame!");
			}break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
			{
				DEBUG_OUT_ERR("OpenGl invalid framebuffer operation error this frame!");
			}break;
			case GL_OUT_OF_MEMORY:
			{
				DEBUG_OUT_ERR("OpenGl out of memory error this frame!");
			}break;
			case GL_STACK_UNDERFLOW:
			{
				DEBUG_OUT_ERR("OpenGl stack underflow error this frame!");
			}break;
			case GL_STACK_OVERFLOW:
			{
				DEBUG_OUT_ERR("OpenGl stack overflow error this frame!");
				
			}break;
		}
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
		info->arbCompatibility = findStr((c8*)extStr, "GL_ARB_compatibility");

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
				    WGL_CONTEXT_MINOR_VERSION_ARB, 2,
				    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,

				    NULL
				};
				if(glewInit() != GLEW_OK)
				{
					DEBUG_OUT_ERR("Glew failed to init!");
				}
				result = wglCreateContextAttribsARB(dc, tempRc, attributes);
				if(result) 
				{
					if(wglMakeCurrent(dc, NULL) == FALSE)
					{
						DEBUG_OUT_ERR("Remove OpenGl temp context Failed!");
					}
					wglDeleteContext(tempRc);

					if(wglMakeCurrent(dc, result) == FALSE)
					{
						DEBUG_OUT_ERR("New OpenGl context set failed!");
					}
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