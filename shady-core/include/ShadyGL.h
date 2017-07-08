#ifndef SHADY_GL_H
#define SHADY_GL_H

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
/* ----------------------------- GL_VERSION_1_1 ---------------------------- */	
#ifndef GL_VERSION_1_1
#define GL_VERSION_1_1 1

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

#endif

typedef void (*_pfshglClampColor) (GLenum target, GLenum clamp);
_pfshglClampColor glClampColor;
#ifdef __cplusplus
}
#endif
namespace Shady
{
	void initGl();
	#ifdef _WIN32
	void Win32GlInit(HDC dc);
	#endif
}

#endif