#include "Cube.h"

namespace Shady
{

	Cube::Cube(f32 size, Vec3f pos, Shader* shader):
		Renderable3D(pos, {}, shader), mSize{size}
	{
		if(mSize <= 0.0f) mSize = 1.0f;
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z + mSize/2}); 
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z + mSize/2});
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z + mSize/2});
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z + mSize/2});
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z - mSize/2});
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z - mSize/2});
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z - mSize/2});
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z - mSize/2});

		u32 verts[] = 
		{
			1,2,4,
			4,2,3,
			3,8,4,
			8,3,7,
			8,7,5,
			5,7,6,
			6,1,5,
			6,2,1,
			1,8,5,
			1,4,8,
			2,6,3,
			3,6,7
		};

		mShader = new Shader("cube", SH_VERTEX_SHADER | SH_FRAGMENT_SHADER);

		glGenVertexArrays(1, &mVAO);
		
		glBindVertexArray(mVAO);
		
		glGenBuffers(NUM_BUFFERS, mVBO);
		
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[POS_BUFFER]);
		
		glBufferData(GL_ARRAY_BUFFER, mVerts.size() * sizeof(Vec3f), mVerts.getPointer(), GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(POS_BUFFER);
		
		glVertexAttribPointer(POS_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[IND_BUFFER]);
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		
		u32 abc = sizeof(verts);
		glBindVertexArray(0);	
		
	}

	Cube::~Cube()
	{
		glDeleteBuffers(NUM_BUFFERS, mVBO);
		glDeleteVertexArrays(1, &mVAO);
	}

	void Cube::draw()
	{
		mShader->setUniformMat4("modelMat", getModelMat());
		glBindVertexArray(mVAO);
		
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);
	}

	void update(f32 dt)
	{

	}

	Matrix4f Cube::getModelMat()
	{
		Matrix4f result = Matrix4f::translation(mPos);
		return result;
	}



} // namespace Shady