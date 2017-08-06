#include "Line2D.h"

namespace Shady
{
	Line2D::Line2D(Vec3f posA, Vec3f posB, Vec4f col, Shader* shader): Renderable2D()
	{
		mPos = posA;
		mShader = shader;
		mPosA = posA;
		mPosB = posB;
		mColor = col;

		if(!mShader)
		{
			mShader = new Shader("basicLine", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER);
		}
#if 0
		Vec3f vertices[2] = 
		{
			mPosA,
			mPosB
		};
#endif

		Vec3f vertices[3] = 
		{
			{0.0f, 0.0f, 0.0f},
			{100.0f, 0.0f, 0.0f},
			{50.0f, 100.0f, 0.0f}

		};

		Vec4f colors[3] = 
		{
			mColor,
			mColor,
			mColor
		};

		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		glGenBuffers(NUM_BUFFERS, mVBO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO[POS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(POS_BUFFER);
		glVertexAttribPointer(POS_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[COL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(COL_BUFFER);
		glVertexAttribPointer(COL_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		//glLineWidth(30.0f);
	}

	void Line2D::draw()
	{
		mShader->setUniformMat4("modelMat", getModelMat());
		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	void Line2D::move(const Vec3f& vec)
	{
		mMoveAmount +=vec;
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
		delete mShader;
	}
}