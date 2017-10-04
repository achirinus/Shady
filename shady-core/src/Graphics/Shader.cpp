#include "Shader.h"
#include <FileUtils.h>
#include <iostream>

namespace Shady
{
		
	Shader::Shader(const char* shaderName, u32 shaderFlags): mAttribIndex(0), mIsLinked{false}
	{
		init(shaderName, shaderFlags);
	}

	void Shader::init(const char* shaderName, u32 shaderFlags)
	{
		String basePath(SHADER_BASE_DIR);
		basePath +=shaderName;
		String vertFileName;
		String fragFileName;
		if(shaderFlags && SH_VERTEX_SHADER)
		{
			vertFileName = basePath + ".vert";
		}
		
		if(shaderFlags && SH_FRAGMENT_SHADER)
		{
			fragFileName = basePath + ".frag";
		}

		String vertSource = File::win32ReadTextFile(vertFileName);
		int vertLen = vertSource.size();
		String fragSource = File::win32ReadTextFile(fragFileName);
		int fragLen = fragSource.size();

		//TODO check if ARB version of functions are better
		GLuint vert, frag;
		vert = glCreateShader(GL_VERTEX_SHADER);
		frag = glCreateShader(GL_FRAGMENT_SHADER);
		const c8* tempVS = vertSource.cStr();
		const c8* tempFS = fragSource.cStr();
		glShaderSource(vert, 1, &tempVS, &vertLen);
		glShaderSource(frag, 1, &tempFS, &fragLen);

		glCompileShader(vert);
		glCompileShader(frag);

		GLint vertCompiled = 0;
		glGetShaderiv(vert, GL_COMPILE_STATUS, &vertCompiled);
		
		//TODO maybe assert?
		if (vertCompiled == GL_FALSE)
		{
			DEBUG_OUT_ERR("Vertex Shader failed to compile\n");
			GLint logSize = 0;
			glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &logSize);
			char* log = new char[logSize];
			glGetShaderInfoLog(vert, logSize, &logSize, log);

			//Better log
			std::cout << log << "\n";
			delete[] log;
			glDeleteShader(vert);
		}
		GLint fragCompiled = 0;
		glGetShaderiv(frag, GL_COMPILE_STATUS, &fragCompiled);

		//TODO maybe assert?
		if (fragCompiled == GL_FALSE)
		{
			DEBUG_OUT_ERR("Fragment Shader failed to compile\n");
			
			GLint logSize = 0;
			glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &logSize);
			char* log = new char[logSize];
			glGetShaderInfoLog(frag, logSize, &logSize, log);

			//Better log
			DEBUG_OUT_INFO(log);
			delete[] log;
			glDeleteShader(vert);
			glDeleteShader(frag);
		}

		if ((fragCompiled == GL_TRUE) && (vertCompiled == GL_TRUE))
		{
			mProgram = glCreateProgram();
			glAttachShader(mProgram, vert);
			glAttachShader(mProgram, frag);

			mIsLinked = linkProgram(vert, frag);
		}
		
		glDetachShader(mProgram,vert);
		glDetachShader(mProgram,frag);
	}

	b8 Shader::linkProgram(GLuint vert, GLuint frag)
	{
		b8 result = false;
		glLinkProgram(mProgram);
			
		GLint isLinked = 0;
		glGetProgramiv(mProgram, GL_LINK_STATUS, &isLinked);
		
		if (isLinked == GL_FALSE)
		{
			DEBUG_OUT_ERR("Program failed to link\n");
			GLint logSize = 0;
			glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logSize);
			char* log = new char[logSize];
			glGetProgramInfoLog(mProgram, logSize, &logSize, log);

			//Better log
			DEBUG_OUT_INFO(log);
			delete[] log;
			glDeleteProgram(mProgram);
			
			glDeleteShader(vert);
			glDeleteShader(frag);
		}
		else
		{
			result = true;
			glValidateProgram(mProgram);
			GLint logSize = 0;
			glGetProgramiv(mProgram, GL_VALIDATE_STATUS, &logSize);
			char* log2 = new char[logSize];
			glGetProgramInfoLog(mProgram, logSize, &logSize, log2);

			//Better log
			DEBUG_OUT_INFO(log2);
			delete[] log2;
		}
		return result;
	}

	void Shader::bindAttribs(String& vs)
	{

		glBindAttribLocation(mProgram, 0, "pos");
		glBindAttribLocation(mProgram, 1, "texCoord");
		glBindAttribLocation(mProgram, 2, "vertColor");
	}

	void Shader::enable()
	{
		glUseProgram(mProgram);
	}
	void Shader::disable()
	{
		glUseProgram(0);
	}
	void Shader::setUniform1f(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(mProgram, name), value);
	}
	void Shader::setUniform1i(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(mProgram, name), value);
	}
	void Shader::setUniform2f(const char* name, const Vec2f& vec2)
	{
		glUniform2f(glGetUniformLocation(mProgram, name), vec2.x, vec2.y);
	}
	void Shader::setUniform3f(const char* name, const Vec3f& vec3)
	{
		glUniform3f(glGetUniformLocation(mProgram, name), vec3.x, vec3.y, vec3.z);
	}
	void Shader::setUniform4f(const char* name, const Vec4f& vec4)
	{
		glUniform4f(glGetUniformLocation(mProgram, name), vec4.x, vec4.y, vec4.z, vec4.w);
	}
	void Shader::setUniformMat4(const char* name, Matrix4f& mat4)
	{
		GLboolean transpose = (GLboolean)(!mat4.isColumnMajor());
		glUniformMatrix4fv(glGetUniformLocation(mProgram, name), 1, transpose,  mat4.elem);
	}

	void Shader::setUniformMat4(const char* name, f32* mat4, b8 transpose)
	{
		glUniformMatrix4fv(glGetUniformLocation(mProgram, name), 1, (GLboolean)transpose,  mat4);	
	}

	Shader::~Shader()
	{
		glDeleteProgram(mProgram);
	}

	
} // namespace Shady





