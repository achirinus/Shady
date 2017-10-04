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
	#define SHADER_BASE_DIR "shady-core\\src\\Shaders\\"
	enum
	{
		SH_VERTEX_SHADER = 0x01,
		SH_FRAGMENT_SHADER = 0x02,
		SH_TESSELATION_SHADER = 0x04,
		SH_GEOMETRY_SHADER = 0x08
	};
	class Shader
	{
	protected:
		GLuint mProgram;
		b8 mIsLinked;
		u32 mAttribIndex;
		virtual void bindAttribs(String& vs);

	public:
		Shader(const char* shaderName, u32 shaderFlags);
		Shader() = default; 
		virtual ~Shader();

		virtual void init(const char* shaderName, u32 shaderFlags);
		virtual b8 linkProgram(GLuint vert, GLuint frag);
		virtual void enable();
		virtual void disable();
		virtual void setUniform1f(const char* name, float value);
		virtual void setUniform1i(const char* name, int value);
		virtual void setUniform2f(const char* name, const Vec2f& vec2);
		virtual void setUniform3f(const char* name, const Vec3f& vec3);
		virtual void setUniform4f(const char* name, const Vec4f& vec4);
		virtual void setUniformMat4(const char* name, Matrix4f& mat4);
		virtual void setUniformMat4(const char* name, f32* mat4, b8 transpose);
	};

}

#endif