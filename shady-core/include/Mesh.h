#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "ShArray.h"
#include <ShadyGL.h>

namespace Shady
{
	
	class Mesh
	{
	public:
		
		Mesh(Array<Vertex> verts);
		Mesh() = default;

		void draw();
		void bind();
		void unbind();
		Array<Vertex> mVertices;
		~Mesh();
	private:

		enum
		{
			POSITION_VB = 0,
			//NORMAL_VB,				
			//TEXCOORD_VB,

			NUM_BUFFERS
		};

		
		GLuint mVAO;
		GLuint mVBO[NUM_BUFFERS];
		
	};

}

#endif