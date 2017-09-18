#ifndef SH_LINE_2D_H
#define SH_LINE_2D_H

#include "Renderable2D.h"
#include "Vec3.h"
#include "Shader.h"

namespace Shady
{
	class Line2D : public Renderable2D
	{
	public:
		Line2D(Vec3f posA, Vec3f posB, Vec4f col = Vec4f(1.0f, 1.0f, 1.0f, 1.0f),
										u32 width = 1,
										Shader* shader = 0);
		~Line2D();
		virtual void draw();
		void move(const Vec3f& vec);
		void setWidth(u32 newWidth);
		Matrix4f getModelMat();

		Vec3f mPosA;
		Vec3f mPosB;
		Vec4f mColor;
		u32 mWidth;


		u32 mVAO;
		u32 mVBO[NUM_BUFFERS];
	};	
}

#endif