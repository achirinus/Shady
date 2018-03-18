#ifndef SHADERMANAGER_H 
#define SHADERMANAGER_H

#include "ShMultiMap.h"
#include "Shader.h"
#include "ShString.h"

namespace Shady
{
	class ShaderManager
	{
	public:
		//Shader files should not be cached any more if i cache the shaders..
		static MultiMap<String, String> sChachedShaderFiles;
		static MultiMap<String, Shader*> sCachedShaders;
		static Shader* CreateShader(const String& filename);
	};
}
#endif
