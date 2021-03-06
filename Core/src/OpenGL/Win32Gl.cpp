#include <ShadyGL.h>

#include <Windows.h>
#include <Commons.h>
#include <ShArray.h>
#include <ShString.h>


OpenGlGlobalFuncEx(wglCreateContextAttribsARB);
OpenGlGlobalFuncEx(wglSwapIntervalEXT);
OpenGlGlobalFuncEx(glGenVertexArrays);
OpenGlGlobalFuncEx(glGenBuffers);
OpenGlGlobalFuncEx(glBindBuffer);
OpenGlGlobalFuncEx(glBufferData);
OpenGlGlobalFuncEx(glEnableVertexAttribArray);
OpenGlGlobalFuncEx(glVertexAttribPointer);
OpenGlGlobalFuncEx(glDeleteVertexArrays);
OpenGlGlobalFuncEx(glDrawArrays);
OpenGlGlobalFuncEx(glDrawElements);
OpenGlGlobalFuncEx(glBindVertexArray);
OpenGlGlobalFuncEx(glCreateShader);
OpenGlGlobalFuncEx(glLinkProgram);
OpenGlGlobalFuncEx(glShaderSource);
OpenGlGlobalFuncEx(glUseProgram);
OpenGlGlobalFuncEx(glCompileShader);
OpenGlGlobalFuncEx(glGetShaderiv);
OpenGlGlobalFuncEx(glGetShaderInfoLog);
OpenGlGlobalFuncEx(glDeleteShader);
OpenGlGlobalFuncEx(glAttachShader);
OpenGlGlobalFuncEx(glBindAttribLocation);
OpenGlGlobalFuncEx(glGetProgramiv);
OpenGlGlobalFuncEx(glGetProgramInfoLog);
OpenGlGlobalFuncEx(glValidateProgram);
OpenGlGlobalFuncEx(glGetUniformLocation);
OpenGlGlobalFuncEx(glUniform1f);
OpenGlGlobalFuncEx(glUniform2f);
OpenGlGlobalFuncEx(glUniform3f);
OpenGlGlobalFuncEx(glUniform4f);
OpenGlGlobalFuncEx(glUniform1i);
OpenGlGlobalFuncEx(glUniformMatrix4fv);
OpenGlGlobalFuncEx(glBindTexture);
OpenGlGlobalFuncEx(glDeleteTextures);
OpenGlGlobalFuncEx(glGenTextures);
OpenGlGlobalFuncEx(glCreateProgram);
OpenGlGlobalFuncEx(glDetachShader);
OpenGlGlobalFuncEx(glDeleteProgram);
OpenGlGlobalFuncEx(glDeleteBuffers);
OpenGlGlobalFuncEx(glTexParameteri);
OpenGlGlobalFuncEx(glTexImage2D);
OpenGlGlobalFuncEx(glActiveTexture);
OpenGlGlobalFuncEx(glGetError);
OpenGlGlobalFuncEx(glGetString);
OpenGlGlobalFuncEx(glEnable);
OpenGlGlobalFuncEx(glClear);
OpenGlGlobalFuncEx(glClearColor);
OpenGlGlobalFuncEx(glDebugMessageControlARB);
OpenGlGlobalFuncEx(glDebugMessageInsertARB);
OpenGlGlobalFuncEx(glDebugMessageCallbackARB);
OpenGlGlobalFuncEx(glGetDebugMessageLogARB);
OpenGlGlobalFuncEx(glDebugMessageControl);
OpenGlGlobalFuncEx(glDebugMessageInsert);
OpenGlGlobalFuncEx(glDebugMessageCallback);
OpenGlGlobalFuncEx(glGetDebugMessageLog);
OpenGlGlobalFuncEx(glBlendFunc);
OpenGlGlobalFuncEx(glViewport);
OpenGlGlobalFuncEx(glTexParameterf);
OpenGlGlobalFuncEx(glDepthFunc);
OpenGlGlobalFuncEx(glDepthMask);
OpenGlGlobalFuncEx(glPixelStorei);
OpenGlGlobalFuncEx(glMapBuffer);
OpenGlGlobalFuncEx(glUnmapBuffer);
OpenGlGlobalFuncEx(glScissor);

namespace Shady
{

	Array<String> Win32InitGLFunctions();

	void GLAPIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, const GLchar* message, const void* userParam)
	{
		DEBUG_OUT_ERR(message);
		SH_ASSERT(!message);
	}

	static void DisplayFailedFuncs(Array<String>& funcs)
	{
		for (auto& name : funcs)
		{
			DEBUG_OUT_ERR("Failed to load GL function: %s", name.CStr());
		}
	}

	HGLRC Win32GetGLContext(HDC dc)
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

				Array<String> failedFuncs = Win32InitGLFunctions();

				DisplayFailedFuncs(failedFuncs);
				Opengl* info = GetGlInfo();
				
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
					glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
					glEnable(GL_BLEND);
					glEnable(GL_LINE_SMOOTH); //Antialiasing				
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glEnable(GL_DEPTH_TEST);
					glDepthFunc(GL_LESS);
					//glEnable(GL_MULTISAMPLE);
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



	Array<String> Win32InitGLFunctions()
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
		ShGlGetProcAddress(glDepthFunc, gldll, result);
		ShGlGetProcAddress(glDepthMask, gldll, result);
		ShGlGetProcAddress(glPixelStorei, gldll, result);
		ShGlGetProcAddress(glMapBuffer, gldll, result);
		ShGlGetProcAddress(glUnmapBuffer, gldll, result);
		ShGlGetProcAddress(glScissor, gldll, result);

		FreeLibrary(gldll);
		return result;
	}
	
	
}