#include <ShadyGL.h>

#include <Windows.h>
#include <Commons.h>
#include <ShArray.h>
#include <ShString.h>

namespace Shady
{

	
	Array<String> initGLFunctions();

	
	void GLAPIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
								 GLsizei length, const GLchar* message, const void* userParam)
	{
		DEBUG_OUT_ERR(message);
		//SH_ASSERT(!message);
	}
	

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
		//Use glGetStringi for each extension if this is called in 
		//forward compatible context
		SH_ASSERT(info);
		const uc8* extStr = glGetString(GL_EXTENSIONS);
		const uc8* verStr = glGetString(GL_VERSION);
		const uc8* shaderVerStr = glGetString(GL_SHADING_LANGUAGE_VERSION);

		const c8* glFirstDigit = findFirstDigit((c8*)verStr);
		const c8* shaderFirstDigit = findFirstDigit((c8*)shaderVerStr);
		info->swapControl = findStr((c8*)extStr, "WGL_EXT_swap_control");
		info->arbCompatibility = findStr((c8*)extStr, "GL_ARB_compatibility");
		info->arbDebugOutput = findStr((c8*)extStr, "GL_ARB_debug_output");

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
				Array<String> failedFuncs = initGLFunctions();
				getGlInfo(info);
				
				/*
				if(glewInit() != GLEW_OK)
				{
					DEBUG_OUT_ERR("Glew failed to init!");
				}
				*/
				static const int attributes[] = 
				{

				    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				    WGL_CONTEXT_MINOR_VERSION_ARB, 2,
				    WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,

				    NULL
				};
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

					if(info->majorGlVersion >= 4)
					{
						glEnable(GL_DEBUG_OUTPUT);
						glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
						glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER_ARB, GL_DONT_CARE,
											 0, 0, GL_FALSE);
						glDebugMessageCallback(OpenGLDebugCallback, 0);
					}
					else if(info->arbDebugOutput)
					{
						glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
						glDebugMessageCallbackARB(OpenGLDebugCallback, 0);
					}

					
					glEnable(GL_CULL_FACE);
					glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
					glEnable(GL_BLEND);
					glEnable(GL_LINE_SMOOTH); //Antialiasing				
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				
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



	Array<String> initGLFunctions()
	{
		Array<String> result{};
		HMODULE gldll = LoadLibrary(TEXT("opengl32.dll"));

		
		ShGlGetProcAddress(wglCreateContextAttribsARB, gldll, result);
		ShGlGetProcAddress(wglSwapIntervalEXT, gldll, result);

		ShGlGetProcAddress(glGenVertexArrays, gldll, result);
		ShGlGetProcAddress(glGenBuffers, gldll, result);
		ShGlGetProcAddress(glBindBuffer, gldll, result);
		ShGlGetProcAddress(glBufferData, gldll, result);
		ShGlGetProcAddress(glEnableVertexAttribArray, gldll, result);
		ShGlGetProcAddress(glVertexAttribPointer, gldll, result);
		ShGlGetProcAddress(glDeleteVertexArrays, gldll, result);
		ShGlGetProcAddress(glDrawArrays, gldll, result);
		ShGlGetProcAddress(glDrawElements, gldll, result);
		ShGlGetProcAddress(glBindVertexArray, gldll, result);
		ShGlGetProcAddress(glCreateShader, gldll, result);
		ShGlGetProcAddress(glLinkProgram, gldll, result);
		ShGlGetProcAddress(glShaderSource, gldll, result);
		ShGlGetProcAddress(glUseProgram, gldll, result);
		ShGlGetProcAddress(glCompileShader, gldll, result);
		ShGlGetProcAddress(glGetShaderiv, gldll, result);
		ShGlGetProcAddress(glGetShaderInfoLog, gldll, result);
		ShGlGetProcAddress(glDeleteShader, gldll, result);
		ShGlGetProcAddress(glAttachShader, gldll, result);
		ShGlGetProcAddress(glBindAttribLocation, gldll, result);
		ShGlGetProcAddress(glGetProgramiv, gldll, result);
		ShGlGetProcAddress(glGetProgramInfoLog, gldll, result);
		ShGlGetProcAddress(glValidateProgram, gldll, result);
		ShGlGetProcAddress(glGetUniformLocation, gldll, result);
		ShGlGetProcAddress(glUniform1f, gldll, result);
		ShGlGetProcAddress(glUniform2f, gldll, result);
		ShGlGetProcAddress(glUniform3f, gldll, result);
		ShGlGetProcAddress(glUniform4f, gldll, result);
		ShGlGetProcAddress(glUniform1i, gldll, result);
		ShGlGetProcAddress(glUniformMatrix4fv, gldll, result);
		ShGlGetProcAddress(glBindTexture, gldll, result);
		ShGlGetProcAddress(glDeleteTextures, gldll, result);
		ShGlGetProcAddress(glGenTextures, gldll, result);
		ShGlGetProcAddress(glCreateProgram, gldll, result);
		ShGlGetProcAddress(glDetachShader, gldll, result);
		ShGlGetProcAddress(glDeleteProgram, gldll, result);
		ShGlGetProcAddress(glDeleteBuffers, gldll, result);
		ShGlGetProcAddress(glTexParameteri, gldll, result);
		ShGlGetProcAddress(glTexImage2D, gldll, result);
		ShGlGetProcAddress(glActiveTexture, gldll, result);
		ShGlGetProcAddress(glGetError, gldll, result);
		ShGlGetProcAddress(glGetString, gldll, result);
		ShGlGetProcAddress(glEnable, gldll, result);
		ShGlGetProcAddress(glClear, gldll, result);
		ShGlGetProcAddress(glClearColor, gldll, result);
		ShGlGetProcAddress(glDebugMessageControlARB, gldll, result);
		ShGlGetProcAddress(glDebugMessageInsertARB, gldll, result);
		ShGlGetProcAddress(glDebugMessageCallbackARB, gldll, result);
		ShGlGetProcAddress(glGetDebugMessageLogARB, gldll, result);
		ShGlGetProcAddress(glDebugMessageControl, gldll, result);
		ShGlGetProcAddress(glDebugMessageInsert, gldll, result);
		ShGlGetProcAddress(glDebugMessageCallback, gldll, result);
		ShGlGetProcAddress(glGetDebugMessageLog, gldll, result);
		ShGlGetProcAddress(glBlendFunc, gldll, result);
		ShGlGetProcAddress(glViewport, gldll, result);
		ShGlGetProcAddress(glTexParameterf, gldll, result);
		

		FreeLibrary(gldll);
		return result;
	}
	
	
}