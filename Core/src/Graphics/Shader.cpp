#include "Shader.h"
#include "ShFile.h"
#include "ShaderManager.h"
#define SHADER_BASE_DIR "src\\Shaders\\"

namespace Shady
{
	
	int Shader::CurrentObjects = 0;
	Shader::Shader(const char* name, u32 flags): mAttribIndex(0), mIsLinked{false}, mShaderName{name}, mFlags{flags}
	{
		CurrentObjects++;
		String basePath(SHADER_BASE_DIR);
		basePath += mShaderName;
		mVertFileName = basePath + ".vert";
		mFragFileName = basePath + ".frag";

		if(CanCompile())
		{
			GLuint program = CreateProgram();
			mProgram = program;
			FileChangeObserver* obs = FileChangeObserver::GetInstance();
			if(obs)
			{
				obs->Add(mVertFileName.CStr(), this, FILE_OBS_FUNC(Shader::Recompile));
				obs->Add(mFragFileName.CStr(), this, FILE_OBS_FUNC(Shader::Recompile));
			}
		}
	}

	GLuint Shader::CreateProgram()
	{
		GLuint result = 0;
		GLuint vert, frag;

		vert = glCreateShader(GL_VERTEX_SHADER);
		frag = glCreateShader(GL_FRAGMENT_SHADER);

		b8 vCompileStatus = CompileShader(mVertFileName, vert);
		b8 fCompileStatus = CompileShader(mFragFileName, frag);

		if (vCompileStatus && fCompileStatus)
		{
			result = glCreateProgram();
			glAttachShader(result, vert);
			glAttachShader(result, frag);

			b8 isLinked = LinkProgram(result, vert, frag);

			if(isLinked)
			{
				glDetachShader(result,vert);
				glDetachShader(result,frag);
			}
			else
			{
				glDeleteProgram(result);
				result = 0;
			}
			glDeleteShader(vert);
			glDeleteShader(frag);
		}
		
		
		return result;
	}

	void Shader::Recompile()
	{
		GLuint tempProg = CreateProgram();
		if(tempProg)
		{
			DEBUG_OUT_INFO("Shader: %s - file changed, recompiled!", mShaderName);
			glDeleteProgram(mProgram);
			mProgram = tempProg;
			mIsLinked = true;
		}
	}

	b8 Shader::LinkProgram(GLuint prog, GLuint vert, GLuint frag)
	{
		b8 result = false;
		glLinkProgram(prog);
			
		GLint isLinked = 0;
		glGetProgramiv(prog, GL_LINK_STATUS, &isLinked);
		
		if (isLinked == GL_FALSE)
		{
			GLint logSize = 0;
			glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logSize);
			char* log = new char[logSize];
			glGetProgramInfoLog(prog, logSize, &logSize, log);

			DEBUG_OUT_ERR("Program failed to link\n");
			DEBUG_OUT_INFO(log);
			
			glDeleteProgram(prog);
			delete[] log;
		}
		else
		{
			result = true;
			glValidateProgram(prog);
			GLint logSize = 0;
			glGetProgramiv(prog, GL_VALIDATE_STATUS, &logSize);
			if (logSize > 1)
			{
				char* log2 = new char[logSize];
				glGetProgramInfoLog(prog, logSize, &logSize, log2);

				//Better log
				DEBUG_OUT_INFO(log2);
				delete[] log2;
			}
				
		}
		return result;
	}

	void Shader::BindAttrib(String& name, u32 location)
	{
		glBindAttribLocation(mProgram, location, name.CStr());
	}

	//For now this deletes the shader in case of failure. Maybe caller should do that?
	b8 Shader::CompileShader(String& fileName, GLuint shader)
	{
		b8 result = true;

		String ShaderSource = File::ReadTextFile(fileName);
		
		int ShaderLength = ShaderSource.Size();
		const c8* tempSrc = ShaderSource.CStr();
		glShaderSource(shader, 1, &tempSrc, &ShaderLength);
		glCompileShader(shader);

		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		
		//TODO maybe assert?
		if (compiled == GL_FALSE)
		{
			GLint logSize = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* log = new char[logSize];
			glGetShaderInfoLog(shader, logSize, &logSize, log);
			
			DEBUG_OUT_ERR("Vertex Shader failed to compile\n");
			DEBUG_OUT_ERR(log);
			
			glDeleteShader(shader);
			delete[] log;
			result = false;
		}
		return result;
	}

	b8 Shader::CanCompile()
	{
		b8 vertEnabled = mFlags && SH_VERTEX_SHADER;
		b8 fragEnabled = mFlags && SH_FRAGMENT_SHADER;
		return (vertEnabled && fragEnabled);
	}

	void Shader::Enable()
	{
		glUseProgram(mProgram);
	}
	void Shader::Disable()
	{
		glUseProgram(0);
	}
	void Shader::SetUniform1f(const char* name, float value)
	{
		GLuint loc = glGetUniformLocation(mProgram, name);
		glUniform1f(loc, value);
	}
	void Shader::SetUniform1i(const char* name, int value)
	{
		GLuint loc = glGetUniformLocation(mProgram, name);
		glUniform1i(loc, value);
	}
	void Shader::SetUniform2f(const char* name, const Vec2f& vec2)
	{
		GLuint loc = glGetUniformLocation(mProgram, name);
		glUniform2f(loc, vec2.x, vec2.y);
	}
	void Shader::SetUniform3f(const char* name, const Vec3f& vec3)
	{
		GLuint loc = glGetUniformLocation(mProgram, name);
		glUniform3f(loc, vec3.x, vec3.y, vec3.z);
	}
	void Shader::SetUniform4f(const char* name, const Vec4f& vec4)
	{
		GLuint loc = glGetUniformLocation(mProgram, name);
		glUniform4f(loc, vec4.x, vec4.y, vec4.z, vec4.w);
	}
	void Shader::SetUniformMat4(const char* name, Matrix4f& mat4)
	{
		GLuint loc = glGetUniformLocation(mProgram, name);
		GLboolean transpose = (GLboolean)(!mat4.isColumnMajor());
		glUniformMatrix4fv(loc, 1, transpose,  mat4.elem);
	}

	void Shader::SetUniformMat4(const char* name, f32* mat4, b8 transpose)
	{
		GLuint loc = glGetUniformLocation(mProgram, name);
		glUniformMatrix4fv(loc, 1, (GLboolean)transpose,  mat4);	
	}

	Shader::~Shader()
	{
		CurrentObjects--;
		glDeleteProgram(mProgram);
		FileChangeObserver* obs = FileChangeObserver::GetInstance();
			if(obs)
			{
				obs->Remove(mVertFileName.CStr());
				obs->Remove(mFragFileName.CStr());
			}
	}

	
} // namespace Shady





