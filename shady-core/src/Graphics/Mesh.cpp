#include "Mesh.h"
#include <vector>

namespace Shady
{ 
	namespace Graphics
	{
		//comment
		/* another
			comment
		*/
		/* dadad */
		Mesh::Mesh(Vertex* vertices, unsigned int numVertices) 
		{ 
			mDrawCount = numVertices;
			glGenVertexArrays(1, &mVAO);
			bind();

			std::vector<Vec3f> positions;
			std::vector<Vec2f> texCoords;
			positions.reserve(numVertices);
			texCoords.reserve(numVertices);

			for (unsigned int i = 0; i < numVertices; i++)
			{
				positions.push_back(vertices[i].mPos);
				texCoords.push_back(vertices[i].mTexCoord);
			}

			glGenBuffers(NUM_BUFFERS, mVBO);
			glBindBuffer(GL_ARRAY_BUFFER, mVBO[POSITION_VB]);
			glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vec3f), &positions[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(POSITION_VB);
			glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
		

			glBindBuffer(GL_ARRAY_BUFFER, mVBO[TEXCOORD_VB]);
			glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vec3f), &texCoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORD_VB);
			glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);
			

			unbind();
		}

		Mesh::~Mesh()
		{
			glDeleteVertexArrays(1, &mVAO);
		}
		void Mesh::draw()
		{
			bind();

			
			glDrawArrays(GL_TRIANGLES, 0, mDrawCount);

			unbind();
		}

		void Mesh::bind()
		{
			glBindVertexArray(mVAO);
		}

		void Mesh::unbind()
		{
			glBindVertexArray(0);
		}
		
	}
}