#include "Cube.h"

#define INDEXED 1

namespace Shady
{

	Cube::Cube(f32 size, Vec3f pos, Shader* shader):
		Renderable3D(pos, {}, shader), mSize{size}
	{
		
		#if INDEXED
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //1
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //2
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //3
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //4
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //5
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //6
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //7
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //8
		#else
		//Front
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //1
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //2
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //4
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //4
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //2
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //3

		//Right
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //4
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //3
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //8
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //8
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //3
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //7

		//Back
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //8
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //7
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //5
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //5
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //7
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //6

		//Left
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //5
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //6
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //1
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //1
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //6
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //2
		
		//Top
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //5
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //1
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //8
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z - mSize/2}); //8
		mVerts.add({pos.x - mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //1
		mVerts.add({pos.x + mSize/2, pos.y - mSize/2, pos.z + mSize/2}); //4

		//Bot
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //2
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //6
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //3
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z + mSize/2}); //3
		mVerts.add({pos.x - mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //6
		mVerts.add({pos.x + mSize/2, pos.y + mSize/2, pos.z - mSize/2}); //7
		#endif

		Vec4f colors[] = 
		{
			{1.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 0.0f, 1.0f},
			{1.0f, 0.0f, 1.0f, 1.0f},
			{0.0f, 0.0f, 1.0f, 1.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
			{0.5f, 0.5f, 1.0f, 1.0f},
		};

		
		mIndices.add({
					0,1,3,
					3,1,2,
					3,2,7,
					7,2,6,
					7,6,4,
					4,6,5,
					4,5,0,
					0,5,1,
					4,0,7,
					7,0,3,
					1,5,2,
					2,5,6});
		mShader = new Shader("cube", SH_VERTEX_SHADER | SH_FRAGMENT_SHADER);

		glGenVertexArrays(1, &mVAO);
		
		glBindVertexArray(mVAO);
		
		glGenBuffers(NUM_BUFFERS, mVBO);
		
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[POS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, mVerts.size() * sizeof(Vec3f), mVerts.getPointer(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(POS_BUFFER);
		glVertexAttribPointer(POS_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[TEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(TEX_BUFFER);
		glVertexAttribPointer(TEX_BUFFER, 4, GL_FLOAT, GL_TRUE, 0, 0);
		

		#if INDEXED
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[IND_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(u32), mIndices.getPointer(), GL_STATIC_DRAW);
		#endif
		
		glBindVertexArray(0);	
		
	}

	Cube::~Cube()
	{
		glDeleteBuffers(NUM_BUFFERS, mVBO);
		glDeleteVertexArrays(1, &mVAO);
	}

	void Cube::draw()
	{
		mShader->SetUniformMat4("modelMat", getModelMat());
		glBindVertexArray(mVAO);
		
		#if INDEXED
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		#else
		glDrawArrays(GL_TRIANGLES, 0, mVerts.size());
		#endif
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