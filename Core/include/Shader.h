#ifndef SHADER_H
#define SHADER_H

#include "ShadyGL.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4f.h"
#include "ShString.h"
#include "FileChangeObserver.h"
#include "ShMultiMap.h"

namespace Shady
{
	
	enum
	{
		SH_VERTEX_SHADER = 0x01,
		SH_FRAGMENT_SHADER = 0x02,
		SH_TESSELATION_SHADER = 0x04,
		SH_GEOMETRY_SHADER = 0x08
	};

	
	class Shader : public Object
	{
	protected:
		GLuint mProgram;
		String mShaderName;
		String mVertFileName;
		String mFragFileName;
		b8 mIsLinked;
		u32 mFlags;
		u32 mAttribIndex;

		static MultiMap<String, String> sChachedShaderFiles;

		void BindAttrib(String& name, u32 location);
		b8 CompileShader(String& fileName, GLuint shader);
		b8 LinkProgram(GLuint prog, GLuint vert, GLuint frag);
	public:
		Shader(const char* name, u32 flags);
		Shader() = default; 
		~Shader();
		void Recompile();
		GLuint CreateProgram();
		b8 CanCompile();
		void Enable();
		void Disable();
		void SetUniform1f(const char* name, float value);
		void SetUniform1i(const char* name, int value);
		void SetUniform2f(const char* name, const Vec2f& vec2);
		void SetUniform3f(const char* name, const Vec3f& vec3);
		void SetUniform4f(const char* name, const Vec4f& vec4);
		void SetUniformMat4(const char* name, Matrix4f& mat4);
		void SetUniformMat4(const char* name, f32* mat4, b8 transpose);

		static int CurrentObjects;
	};

}

#endif