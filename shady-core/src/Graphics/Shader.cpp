#include "Shader.h"
#include <FileUtils.h>
#include <iostream>

namespace Shady
{
		
	Shader::Shader(const char* shaderName, u32 shaderFlags)
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
			std::cout << "Vertex Shader failed to compile\n";
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
			std::cout << "Fragment Shader failed to compile\n";
			
			GLint logSize = 0;
			glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &logSize);
			char* log = new char[logSize];
			glGetShaderInfoLog(frag, logSize, &logSize, log);

			//Better log
			std::cout << log << "\n";
			delete[] log;
			glDeleteShader(vert);
			glDeleteShader(frag);
		}

		if ((fragCompiled == GL_TRUE) && (vertCompiled == GL_TRUE))
		{
			mProgram = glCreateProgram();
			glAttachShader(mProgram, vert);
			glAttachShader(mProgram, frag);

			glBindAttribLocation(mProgram, 0, "pos");
			glBindAttribLocation(mProgram, 1, "texCoord");
			glBindAttribLocation(mProgram, 2, "vertColor");
			glLinkProgram(mProgram);
			
			GLint isLinked = 0;
			glGetProgramiv(mProgram, GL_LINK_STATUS, &isLinked);
			
			if (isLinked == GL_FALSE)
			{
				std::cout << "Program failed to link\n";
				GLint logSize = 0;
				glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logSize);
				char* log = new char[logSize];
				glGetProgramInfoLog(mProgram, logSize, &logSize, log);

				//Better log
				std::cout << log << "\n";
				delete[] log;
				glDeleteProgram(mProgram);
				
				glDeleteShader(vert);
				glDeleteShader(frag);
			}

		}
		glValidateProgram(mProgram);
		GLint logSize = 0;
		glGetProgramiv(mProgram, GL_VALIDATE_STATUS, &logSize);
		char* log2 = new char[logSize];
		glGetProgramInfoLog(mProgram, logSize, &logSize, log2);

		//Better log
		std::cout << log2 << "\n";
		delete[] log2;
		glDetachShader(mProgram,vert);
		glDetachShader(mProgram,frag);
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
	void Shader::setUniformMat4(const char* name, const Matrix4f& mat4)
	{
		glUniformMatrix4fv(glGetUniformLocation(mProgram, name), 1, GL_FALSE,  mat4.elem);
	}

	void Shader::setUniformMat4(const char* name, const f32* mat4)
	{
		glUniformMatrix4fv(glGetUniformLocation(mProgram, name), 1, GL_FALSE,  mat4);	
	}

	Shader::~Shader()
	{
		glDeleteProgram(mProgram);
	}

	
} // namespace Shady





