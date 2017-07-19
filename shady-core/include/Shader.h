#ifndef SHADER_H
#define SHADER_H

#include "glew.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4f.h"
#include "ShString.h"

namespace Shady
{
	#define SHADER_BASE_DIR "..\\src\\Shaders\\"
	enum
	{
		SH_VERTEX_SHADER = 0x01,
		SH_FRAGMENT_SHADER = 0x02,
		SH_TESSELATION_SHADER = 0x04,
		SH_GEOMETRY_SHADER = 0x08
	};
	class Shader
	{
	private:
		GLuint mProgram;


	public:
		Shader(const char* shaderName, u32 shaderFlags);
		Shader() = default; 
		~Shader();

		void init(const char* shaderName, u32 shaderFlags);
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