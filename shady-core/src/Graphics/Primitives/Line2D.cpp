#include "Line2D.h"

namespace Shady
{
	Line2D::Line2D(Vec3f posA, Vec3f posB, Vec4f col, u32 width, Shader* shader): Renderable2D()
	{
		mPos = posA;
		mPosA = posA;
		mPosB = posB;
		mColor = col;
		mWidth = width;
		
		if(shader)
		{
			mShaders.add(shader);
		}
		else
		{
			mShaders.add(new Shader("basicLine", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER));
		}
		
		Vec3f vertices[2] = 
		{
			mPosA,
			mPosB
		};

/*
		Vec3f vertices[2] = 
		{
			{0.0f, 0.0f, 0.0f},
			{100.0f, 0.0f, 0.0f}

		};
*/
		Vec4f colors[2] = 
		{
			mColor,
			mColor
		};

		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		glGenBuffers(NUM_BUFFERS, mVBO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO[POS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vec3f), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(POS_BUFFER);
		glVertexAttribPointer(POS_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[COL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vec4f), colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(COL_BUFFER);
		glVertexAttribPointer(COL_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glBindVertexArray(0);
		
	}

	void Line2D::draw()
	{
		//mShader->setUniformMat4("modelMat", getModelMat());
		glBindVertexArray(mVAO);
		glLineWidth(mWidth);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);
	}

	void Line2D::move(const Vec3f& vec)
	{
		mMoveAmount +=vec;
	}

	void Line2D::setWidth(u32 newWidth)
	{
		mWidth = newWidth;
	}

	Matrix4f Line2D::getModelMat()
	{
		Matrix4f result{1};
		
		result *= Matrix4f::translation(mMoveAmount);

		return result;
	}


	Line2D::~Line2D()
	{
		glDeleteBuffers(NUM_BUFFERS, mVBO);
		glDeleteVertexArrays(1, &mVAO);
		for(s32 index = 0; index < mShaders.size(); index++)
		{
			delete mShaders[index];
		}
	}
}