#include "ShadyGL.h"
#include "StringUtils.h"
#include "Commons.h"
#include "ShArray.h"
#include "ShString.h"

namespace Shady
{
#ifdef _WIN32
	Array<String> Win32InitGLFunctions();
#endif

	Opengl OpenglInfo;

	Opengl* GetGlInfo()
	{
		GetGlInfo(&OpenglInfo);
		return &OpenglInfo;
	}

	void CheckGlError(const char* func, const char* file, int line)
	{
		GLenum err = 0;
		do
		{
#ifdef GL_FUNCS_AS_MACROS
			err = glGetError_();
#else
			err = glGetError();
#endif

			switch (err)
			{
			case GL_INVALID_ENUM:
			{
				DEBUG_OUT_ERR("%s:OpenGl invalid enum argument error!\n File:%s  Line:%d", func, file, line);
			}break;
			case GL_INVALID_VALUE:
			{
				DEBUG_OUT_ERR("%s:OpenGl invalid value argument error!\n File:%s  Line:%d", func, file, line);
			}break;
			case GL_INVALID_OPERATION:
			{
				DEBUG_OUT_ERR("%s:OpenGl invalid operation error!\n File:%s  Line:%d", func, file, line);
			}break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
			{
				DEBUG_OUT_ERR("%s:OpenGl invalid framebufer operation error!\n File:%s  Line:%d", func, file, line);
			}break;
			case GL_OUT_OF_MEMORY:
			{
				DEBUG_OUT_ERR("%s:OpenGl out of memory error!\n File:%s  Line:%d", func, file, line);
			}break;
			case GL_STACK_UNDERFLOW:
			{
				DEBUG_OUT_ERR("%s:OpenGl stack underflow error!\n File:%s  Line:%d", func, file, line);
			}break;
			case GL_STACK_OVERFLOW:
			{
				DEBUG_OUT_ERR("%s:OpenGl stack overflow error!\n File:%s  Line:%d", func, file, line);

			}break;
			}
		} while (err != GL_NO_ERROR);
	}

	
	void GetGlInfo(Opengl* info)
	{
		//Use glGetStringi for each extension if this is called in 
		//forward compatible context
		if (info)
		{
			if (info->ValidInfo) return;
			const uc8* extStr = glGetString(GL_EXTENSIONS);
			const uc8* verStr = glGetString(GL_VERSION);
			const uc8* shaderVerStr = glGetString(GL_SHADING_LANGUAGE_VERSION);

			const c8* glFirstDigit = FindFirstDigit((c8*)verStr);
			const c8* shaderFirstDigit = FindFirstDigit((c8*)shaderVerStr);
			info->swapControl = FindStr((c8*)extStr, "WGL_EXT_swap_control");
			info->arbCompatibility = FindStr((c8*)extStr, "GL_ARB_compatibility");
			info->arbDebugOutput = FindStr((c8*)extStr, "GL_ARB_debug_output");

			info->majorGlVersion = CharToDigit(glFirstDigit[0]);
			info->minorGlVersion = CharToDigit(glFirstDigit[2]);

			info->majorShaderVersion = CharToDigit(shaderFirstDigit[0]);
			info->minorShaderVersion = CharToDigit(shaderFirstDigit[2]);
			info->ValidInfo = true;
		}
	}

	void ClearGlErrors()
	{
#ifdef GL_FUNCS_AS_MACROS
		while (!glGetError_()) {}
#else
		while (!glGetError()) {}
#endif
	}
}
