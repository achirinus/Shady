#include "Mesh.h"
#include <vector>

namespace Shady
{ 
	
	Mesh::Mesh(Array<Vertex> verts): mVertices(verts) 
	{ 

		glGenVertexArrays(1, &mVAO);
		bind();
		// float verts2[] = 
		// {
		// 	0.0f, 0.0f, 0.2f, 1.0f,
		// 	0.3f, 0.3f, 0.2f, 1.0f,
		// 	0.5f, 0.0f, 0.2f, 1.0f
		// };
		glGenBuffers(NUM_BUFFERS, mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vec4f), &mVertices[0], GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(POSITION_VB);
		glVertexAttribPointer(POSITION_VB, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
#if 0
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vec3f), &verts[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(NORMAL_VB);
		glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 
							 (sizeof(Vec2f) + sizeof(Vec4f)),
							 (GLvoid*)(0 + sizeof(Vec4f)));
#endif	
		unbind();

	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &mVAO);
	}
	void Mesh::draw()
	{
		bind();
		
		glDrawArrays(GL_LINES, 0, mVertices.size());

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