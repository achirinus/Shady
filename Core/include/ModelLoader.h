#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "Mesh.h"
#include "ShFile.h"
namespace Shady
{
	class ModelLoader
	{
	public:
		Mesh* loadObj(const char* fileName);
	private:

	};
}

#endif