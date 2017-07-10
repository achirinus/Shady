#ifndef SHADER_H
#define SHADER_H

#include "glew.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4f.h"


namespace Shady
{

	class Shader
	{
	private:
		GLuint mProgram;

	public:
		Shader(const char* vertFileName, const char* fragFileName);
		~Shader();
		void enable();
		void disable();
		void setUniform1f(const char* name, float value);
		void setUniform1i(const char* name, int value);
		void setUniform2f(const char* name, const Vec2f& vec2);
		void setUniform3f(const char* name, const Vec3f& vec3);
		void setUniform4f(const char* name, const Vec4f& vec4);
		void setUniformMat4(const char* name, const Matrix4f& mat4);

		void setUniformMat4(const char* name, const f32* mat4);
	};

}

#endif