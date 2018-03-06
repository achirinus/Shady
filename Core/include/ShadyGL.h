#ifndef SHADY_GL_H
#define SHADY_GL_H

#define GL_FUNCS_AS_MACROS
#include "ShTypes.h"
#include <stddef.h>
#if defined (_WIN32)
#include <Windows.h>

#ifndef GLAPIENTRY
	#define GLAPIENTRY APIENTRY
#endif

#ifndef GLAPI
	#define GLAPI WINGDIAPI
#endif 

#endif //WIN32



#ifndef GLAPIENTRY
	#define GLAPIENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLboolean;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;
typedef unsigned char GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef signed long long GLint64EXT;
typedef unsigned long long GLuint64EXT;
typedef GLint64EXT GLint64;
typedef GLuint64EXT GLuint64;
typedef struct __GLsync *GLsync;
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x0002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002


#define GL_FALSE                          0
#define GL_TRUE                           1

#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_TRIANGLES                      0x0004

#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308

#define GL_DONT_CARE                      0x1100

#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_EXTENSIONS                     0x1F03

#define GL_CULL_FACE                      0x0B44
#define GL_BLEND                          0x0BE2
#define GL_LINE_SMOOTH                    0x0B20

#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_INVALID_OPERATION              0x0502
#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

#define GL_TEXTURE_2D                     0x0DE1

#define GL_RGBA                           0x1908

#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_REPEAT                         0x2901

#define GL_CLAMP_TO_EDGE                  0x812F

#define GL_DEBUG_SOURCE_API_ARB           0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB 0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB   0x8249
#define GL_DEBUG_SOURCE_APPLICATION_ARB   0x824A
#define GL_DEBUG_SOURCE_OTHER_ARB         0x824B
#define GL_DEBUG_TYPE_ERROR_ARB           0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB 0x824E
#define GL_DEBUG_TYPE_PORTABILITY_ARB     0x824F
#define GL_DEBUG_TYPE_PERFORMANCE_ARB     0x8250
#define GL_DEBUG_TYPE_OTHER_ARB           0x8251

#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#define GL_DEBUG_OUTPUT                   0x92E0

#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF

#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_STATIC_DRAW                    0x88E4
#define GL_STREAM_DRAW                    0x88E0

#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31

#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84


#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406

typedef void (APIENTRY  *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (APIENTRY  *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);

//WGL
typedef HGLRC APIENTRY sh_wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL APIENTRY sh_wglSwapIntervalEXT(int interval);

typedef void APIENTRY sh_glGenVertexArrays (GLsizei n, GLuint *arrays);
typedef void APIENTRY sh_glGenBuffers (GLsizei n, GLuint *buffers);
typedef void APIENTRY sh_glBindBuffer (GLenum target, GLuint buffer);
typedef void APIENTRY sh_glBufferData (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void APIENTRY sh_glEnableVertexAttribArray (GLuint index);
typedef void APIENTRY sh_glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void APIENTRY sh_glDeleteVertexArrays (GLsizei n, const GLuint *arrays);
typedef void APIENTRY sh_glDrawArrays (GLenum mode, GLint first, GLsizei count);
typedef void APIENTRY sh_glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices);
typedef void APIENTRY sh_glBindVertexArray (GLuint array);
typedef GLuint APIENTRY sh_glCreateShader (GLenum type);
typedef void APIENTRY sh_glLinkProgram (GLuint program);
typedef void APIENTRY sh_glShaderSource (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void APIENTRY sh_glUseProgram (GLuint program);
typedef void APIENTRY sh_glCompileShader (GLuint shader);
typedef void APIENTRY sh_glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
typedef void APIENTRY sh_glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void APIENTRY sh_glDeleteShader (GLuint shader);
typedef void APIENTRY sh_glAttachShader (GLuint program, GLuint shader);
typedef void APIENTRY sh_glBindAttribLocation (GLuint program, GLuint index, const GLchar *name);
typedef void APIENTRY sh_glGetProgramiv (GLuint program, GLenum pname, GLint *params);
typedef void APIENTRY sh_glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void APIENTRY sh_glValidateProgram (GLuint program);
typedef GLint APIENTRY sh_glGetUniformLocation (GLuint program, const GLchar *name);
typedef void APIENTRY sh_glUniform1f (GLint location, GLfloat v0);
typedef void APIENTRY sh_glUniform2f (GLint location, GLfloat v0, GLfloat v1);
typedef void APIENTRY sh_glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void APIENTRY sh_glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void APIENTRY sh_glUniform1i (GLint location, GLint v0);
typedef void APIENTRY sh_glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void APIENTRY sh_glBindTexture (GLenum target, GLuint texture);
typedef void APIENTRY sh_glDeleteTextures (GLsizei n, const GLuint *textures);
typedef void APIENTRY sh_glGenTextures (GLsizei n, GLuint *textures);
typedef GLuint APIENTRY sh_glCreateProgram (void);
typedef void APIENTRY sh_glDetachShader (GLuint program, GLuint shader);
typedef void APIENTRY sh_glDeleteProgram (GLuint program);
typedef void APIENTRY sh_glDeleteBuffers (GLsizei n, const GLuint *buffers);
typedef void APIENTRY sh_glTexParameteri (GLenum target, GLenum pname, GLint param);
typedef void APIENTRY sh_glTexParameterf (GLenum target, GLenum pname, GLfloat param);
typedef void APIENTRY sh_glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void APIENTRY sh_glActiveTexture (GLenum texture);
typedef GLenum APIENTRY sh_glGetError (void);
typedef const GLubyte* APIENTRY sh_glGetString (GLenum name);
typedef void APIENTRY sh_glEnable (GLenum cap);
typedef void APIENTRY sh_glClear (GLbitfield mask);
typedef void APIENTRY sh_glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void APIENTRY sh_glDebugMessageControlARB (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void APIENTRY sh_glDebugMessageInsertARB (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void APIENTRY sh_glDebugMessageCallbackARB (GLDEBUGPROCARB callback, const void *userParam);
typedef GLuint APIENTRY sh_glGetDebugMessageLogARB (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void APIENTRY sh_glDebugMessageControl (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void APIENTRY sh_glDebugMessageInsert (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void APIENTRY sh_glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam);
typedef GLuint APIENTRY sh_glGetDebugMessageLog (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void APIENTRY sh_glBlendFunc (GLenum sfactor, GLenum dfactor);
typedef void APIENTRY sh_glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void APIENTRY sh_glTexParameterf (GLenum target, GLenum pname, GLfloat param);

#define OpenGlGlobalFuncEx(Name) sh_##Name* Name##_

#ifdef GL_FUNCS_AS_MACROS

	#define IsGlValidFunc(Name) ((Name##_) != nullptr)
	#define OpenGlGlobalFunc(Name) extern sh_##Name* Name##_
	
	#ifdef SHADY_DEBUG
		#define GLFunctionWrap(Func, ...) 	Func##_(__VA_ARGS__); \
											CheckGlError(#Func, __FILE__, __LINE__)
	#else
		#define GLFunctionWrap(Func, ...) Func##_(__VA_ARGS__)
	#endif

	OpenGlGlobalFunc(wglCreateContextAttribsARB);
	#define wglCreateContextAttribsARB(...) GLFunctionWrap(wglCreateContextAttribsARB, __VA_ARGS__)

	OpenGlGlobalFunc(wglSwapIntervalEXT);
	#define wglSwapIntervalEXT(...) GLFunctionWrap(wglSwapIntervalEXT, __VA_ARGS__)

	OpenGlGlobalFunc(glGenVertexArrays);
	#define glGenVertexArrays(...) GLFunctionWrap(glGenVertexArrays, __VA_ARGS__)

	OpenGlGlobalFunc(glGenBuffers);
	#define glGenBuffers(...) GLFunctionWrap(glGenBuffers, __VA_ARGS__)

	OpenGlGlobalFunc(glBindBuffer);
	#define glBindBuffer(...) GLFunctionWrap(glBindBuffer, __VA_ARGS__)

	OpenGlGlobalFunc(glBufferData);
	#define glBufferData(...) GLFunctionWrap(glBufferData, __VA_ARGS__)

	OpenGlGlobalFunc(glEnableVertexAttribArray);
	#define glEnableVertexAttribArray(...) GLFunctionWrap(glEnableVertexAttribArray, __VA_ARGS__)

	OpenGlGlobalFunc(glVertexAttribPointer);
	#define glVertexAttribPointer(...) GLFunctionWrap(glVertexAttribPointer, __VA_ARGS__)

	OpenGlGlobalFunc(glDeleteVertexArrays);
	#define glDeleteVertexArrays(...) GLFunctionWrap(glDeleteVertexArrays, __VA_ARGS__)

	OpenGlGlobalFunc(glDrawArrays);
	#define glDrawArrays(...) GLFunctionWrap(glDrawArrays, __VA_ARGS__)

	OpenGlGlobalFunc(glDrawElements);
	#define glDrawElements(...) GLFunctionWrap(glDrawElements, __VA_ARGS__)

	OpenGlGlobalFunc(glBindVertexArray);
	#define glBindVertexArray(...) GLFunctionWrap(glBindVertexArray, __VA_ARGS__)

	OpenGlGlobalFunc(glCreateShader);
	#define glCreateShader(...) GLFunctionWrap(glCreateShader, __VA_ARGS__)

	OpenGlGlobalFunc(glLinkProgram);
	#define glLinkProgram(...) GLFunctionWrap(glLinkProgram, __VA_ARGS__)

	OpenGlGlobalFunc(glShaderSource);
	#define glShaderSource(...) GLFunctionWrap(glShaderSource, __VA_ARGS__)

	OpenGlGlobalFunc(glUseProgram);
	#define glUseProgram(...) GLFunctionWrap(glUseProgram, __VA_ARGS__)

	OpenGlGlobalFunc(glCompileShader);
	#define glCompileShader(...) GLFunctionWrap(glCompileShader, __VA_ARGS__)

	OpenGlGlobalFunc(glGetShaderiv);
	#define glGetShaderiv(...) GLFunctionWrap(glGetShaderiv, __VA_ARGS__)

	OpenGlGlobalFunc(glGetShaderInfoLog);
	#define glGetShaderInfoLog(...) GLFunctionWrap(glGetShaderInfoLog, __VA_ARGS__)

	OpenGlGlobalFunc(glDeleteShader);
	#define glDeleteShader(...) GLFunctionWrap(glDeleteShader, __VA_ARGS__)

	OpenGlGlobalFunc(glAttachShader);
	#define glAttachShader(...) GLFunctionWrap(glAttachShader, __VA_ARGS__)

	OpenGlGlobalFunc(glBindAttribLocation);
	#define glBindAttribLocation(...) GLFunctionWrap(glBindAttribLocation, __VA_ARGS__)

	OpenGlGlobalFunc(glGetProgramiv);
	#define glGetProgramiv(...) GLFunctionWrap(glGetProgramiv, __VA_ARGS__)

	OpenGlGlobalFunc(glGetProgramInfoLog);
	#define glGetProgramInfoLog(...) GLFunctionWrap(glGetProgramInfoLog, __VA_ARGS__)

	OpenGlGlobalFunc(glValidateProgram);
	#define glValidateProgram(...) GLFunctionWrap(glValidateProgram, __VA_ARGS__)

	OpenGlGlobalFunc(glGetUniformLocation);
	#define glGetUniformLocation(...) GLFunctionWrap(glGetUniformLocation, __VA_ARGS__)

	OpenGlGlobalFunc(glUniform1f);
	#define glUniform1f(...) GLFunctionWrap(glUniform1f, __VA_ARGS__)

	OpenGlGlobalFunc(glUniform2f);
	#define glUniform2f(...) GLFunctionWrap(glUniform2f, __VA_ARGS__)

	OpenGlGlobalFunc(glUniform3f);
	#define glUniform3f(...) GLFunctionWrap(glUniform3f, __VA_ARGS__)

	OpenGlGlobalFunc(glUniform4f);
	#define glUniform4f(...) GLFunctionWrap(glUniform4f, __VA_ARGS__)

	OpenGlGlobalFunc(glUniform1i);
	#define glUniform1i(...) GLFunctionWrap(glUniform1i, __VA_ARGS__)

	OpenGlGlobalFunc(glUniformMatrix4fv);
	#define glUniformMatrix4fv(...) GLFunctionWrap(glUniformMatrix4fv, __VA_ARGS__)

	OpenGlGlobalFunc(glBindTexture);
	#define glBindTexture(...) GLFunctionWrap(glBindTexture, __VA_ARGS__)

	OpenGlGlobalFunc(glDeleteTextures);
	#define glDeleteTextures(...) GLFunctionWrap(glDeleteTextures, __VA_ARGS__)

	OpenGlGlobalFunc(glGenTextures);
	#define glGenTextures(...) GLFunctionWrap(glGenTextures, __VA_ARGS__)

	OpenGlGlobalFunc(glCreateProgram);
	#define glCreateProgram(...) GLFunctionWrap(glCreateProgram, __VA_ARGS__)

	OpenGlGlobalFunc(glDetachShader);
	#define glDetachShader(...) GLFunctionWrap(glDetachShader, __VA_ARGS__)

	OpenGlGlobalFunc(glDeleteProgram);
	#define glDeleteProgram(...) GLFunctionWrap(glDeleteProgram, __VA_ARGS__)

	OpenGlGlobalFunc(glDeleteBuffers);
	#define glDeleteBuffers(...) GLFunctionWrap(glDeleteBuffers, __VA_ARGS__)

	OpenGlGlobalFunc(glTexParameteri);
	#define glTexParameteri(...) GLFunctionWrap(glTexParameteri, __VA_ARGS__)

	OpenGlGlobalFunc(glTexImage2D);
	#define glTexImage2D(...) GLFunctionWrap(glTexImage2D, __VA_ARGS__)

	OpenGlGlobalFunc(glActiveTexture);
	#define glActiveTexture(...) GLFunctionWrap(glActiveTexture, __VA_ARGS__)

	OpenGlGlobalFunc(glGetError);
	#define glGetError(...) GLFunctionWrap(glGetError, __VA_ARGS__)

	OpenGlGlobalFunc(glGetString);
	#define glGetString(...) GLFunctionWrap(glGetString, __VA_ARGS__)

	OpenGlGlobalFunc(glEnable);
	#define glEnable(...) GLFunctionWrap(glEnable, __VA_ARGS__)

	OpenGlGlobalFunc(glClear);
	#define glClear(...) GLFunctionWrap(glClear, __VA_ARGS__)

	OpenGlGlobalFunc(glClearColor);
	#define glClearColor(...) GLFunctionWrap(glClearColor, __VA_ARGS__)

	OpenGlGlobalFunc(glDebugMessageControlARB);
	#define glDebugMessageControlARB(...) GLFunctionWrap(glDebugMessageControlARB, __VA_ARGS__)

	OpenGlGlobalFunc(glDebugMessageInsertARB);
	#define glDebugMessageInsertARB(...) GLFunctionWrap(glDebugMessageInsertARB, __VA_ARGS__)

	OpenGlGlobalFunc(glDebugMessageCallbackARB);
	#define glDebugMessageCallbackARB(...) GLFunctionWrap(glDebugMessageCallbackARB, __VA_ARGS__)

	OpenGlGlobalFunc(glGetDebugMessageLogARB);
	#define glGetDebugMessageLogARB(...) GLFunctionWrap(glGetDebugMessageLogARB, __VA_ARGS__)

	OpenGlGlobalFunc(glDebugMessageControl);
	#define glDebugMessageControl(...) GLFunctionWrap(glDebugMessageControl, __VA_ARGS__)

	OpenGlGlobalFunc(glDebugMessageInsert);
	#define glDebugMessageInsert(...) GLFunctionWrap(glDebugMessageInsert, __VA_ARGS__)

	OpenGlGlobalFunc(glDebugMessageCallback);
	#define glDebugMessageCallback(...) GLFunctionWrap(glDebugMessageCallback, __VA_ARGS__)

	OpenGlGlobalFunc(glGetDebugMessageLog);
	#define glGetDebugMessageLog(...) GLFunctionWrap(glGetDebugMessageLog, __VA_ARGS__)

	OpenGlGlobalFunc(glBlendFunc);
	#define glBlendFunc(...) GLFunctionWrap(glBlendFunc, __VA_ARGS__)

	OpenGlGlobalFunc(glViewport);
	#define glViewport(...) GLFunctionWrap(glViewport, __VA_ARGS__)

	OpenGlGlobalFunc(glTexParameterf);
	#define glTexParameterf(...) GLFunctionWrap(glTexParameterf, __VA_ARGS__)



	#define ShGlGetProcAddress(Name, FallbackModule, Arr)	\
	 	Name##_ = (sh_##Name*)wglGetProcAddress(#Name); \
		if(!Name##_) {Name##_ = (sh_##Name*)GetProcAddress(FallbackModule,#Name);} \
		if(!Name##_) {Arr.Add(#Name);}

#else //IFDEF GL_FUNCS_AS_MACROS
	#define IsGlValidFunc(Name) ((Name) != nullptr)
	#define OpenGlGlobalFunc(Name) static sh_##Name* Name

	OpenGlGlobalFunc(wglCreateContextAttribsARB);
	OpenGlGlobalFunc(wglSwapIntervalEXT);

	OpenGlGlobalFunc(glGenVertexArrays);
	OpenGlGlobalFunc(glGenBuffers);
	OpenGlGlobalFunc(glBindBuffer);
	OpenGlGlobalFunc(glBufferData);
	OpenGlGlobalFunc(glEnableVertexAttribArray);
	OpenGlGlobalFunc(glVertexAttribPointer);
	OpenGlGlobalFunc(glDeleteVertexArrays);
	OpenGlGlobalFunc(glDrawArrays);
	OpenGlGlobalFunc(glDrawElements);
	OpenGlGlobalFunc(glBindVertexArray);
	OpenGlGlobalFunc(glCreateShader);
	OpenGlGlobalFunc(glLinkProgram);
	OpenGlGlobalFunc(glShaderSource);
	OpenGlGlobalFunc(glUseProgram);
	OpenGlGlobalFunc(glCompileShader);
	OpenGlGlobalFunc(glGetShaderiv);
	OpenGlGlobalFunc(glGetShaderInfoLog);
	OpenGlGlobalFunc(glDeleteShader);
	OpenGlGlobalFunc(glAttachShader);
	OpenGlGlobalFunc(glBindAttribLocation);
	OpenGlGlobalFunc(glGetProgramiv);
	OpenGlGlobalFunc(glGetProgramInfoLog);
	OpenGlGlobalFunc(glValidateProgram);
	OpenGlGlobalFunc(glGetUniformLocation);
	OpenGlGlobalFunc(glUniform1f);
	OpenGlGlobalFunc(glUniform2f);
	OpenGlGlobalFunc(glUniform3f);
	OpenGlGlobalFunc(glUniform4f);
	OpenGlGlobalFunc(glUniform1i);
	OpenGlGlobalFunc(glUniformMatrix4fv);
	OpenGlGlobalFunc(glBindTexture);
	OpenGlGlobalFunc(glDeleteTextures);
	OpenGlGlobalFunc(glGenTextures);
	OpenGlGlobalFunc(glCreateProgram);
	OpenGlGlobalFunc(glDetachShader);
	OpenGlGlobalFunc(glDeleteProgram);
	OpenGlGlobalFunc(glDeleteBuffers);
	OpenGlGlobalFunc(glTexParameteri);
	OpenGlGlobalFunc(glTexImage2D);
	OpenGlGlobalFunc(glActiveTexture);
	OpenGlGlobalFunc(glGetError);
	OpenGlGlobalFunc(glGetString);
	OpenGlGlobalFunc(glEnable);
	OpenGlGlobalFunc(glClear);
	OpenGlGlobalFunc(glClearColor);
	OpenGlGlobalFunc(glDebugMessageControlARB);
	OpenGlGlobalFunc(glDebugMessageInsertARB);
	OpenGlGlobalFunc(glDebugMessageCallbackARB);
	OpenGlGlobalFunc(glGetDebugMessageLogARB);
	OpenGlGlobalFunc(glDebugMessageControl);
	OpenGlGlobalFunc(glDebugMessageInsert);
	OpenGlGlobalFunc(glDebugMessageCallback);
	OpenGlGlobalFunc(glGetDebugMessageLog);
	OpenGlGlobalFunc(glBlendFunc);
	OpenGlGlobalFunc(glViewport);
	OpenGlGlobalFunc(glTexParameterf);



	#define ShGlGetProcAddress(Name, FallbackModule, Arr)	\
	 	Name = (sh_##Name*)wglGetProcAddress(#Name); \
		if(!Name) {Name = (sh_##Name*)GetProcAddress(FallbackModule,#Name);} \
		if(!Name) {Arr.Add(#Name);}

#endif//IFDEF GL_FUNCS_AS_MACROS

#ifdef __cplusplus
}
#endif
namespace Shady
{
	void initGl();
	struct OpenglInfo
	{
		u32 majorGlVersion;
		u32 minorGlVersion;
		u32 majorShaderVersion;
		u32 minorShaderVersion;
		b8 swapControl; //WGL_EXT_swap_control
		b8 arbCompatibility; //GL_ARB_compatibility
		b8 arbDebugOutput; //GL_ARB_debug_output
	};

	#ifdef _WIN32
		HGLRC Win32GlInit(HDC dc, OpenglInfo* info = 0);
	#endif

	
	void GetGlInfo(OpenglInfo* info);
	OpenglInfo GetGlInfo();
	void CheckGlError(const char* func, const char* file, int line);
	void ClearGlErrors();

}

#endif