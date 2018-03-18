#include "ShaderManager.h"

namespace Shady
{
	MultiMap<String, String> ShaderManager::sChachedShaderFiles;
	MultiMap<String, Shader*> ShaderManager::sCachedShaders;

	Shader* ShaderManager::CreateShader(const String& filename)
	{
		Shader* result = nullptr;
		if (sCachedShaders.HasKey(filename))
		{
			result = sCachedShaders[filename];
		}
		else
		{
			result = new Shader(*filename, SH_VERTEX_SHADER | SH_FRAGMENT_SHADER);
			sCachedShaders.Add(filename, result);
		}
		return result;
	}
}
