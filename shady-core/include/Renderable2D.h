#ifndef SH_RENDERABLE_2D_H
#define SH_RENDERABLE_2D_H

#include "Vec3.h"
#include "Matrix4f.h"
#include "Commons.h"

namespace Shady
{
	class Renderable2D
	{
		
	public:
		enum
		{
			POS_BUFFER = 0,
			TEX_BUFFER,
			COL_BUFFER,
			NUM_BUFFERS
		};

		Vec3f mPos;
		Matrix4f mModelMat;
		Vec3f mMoveAmount;
		u32 mWidth;
		u32 mHeight;
		Shader* mShader;
		f32 mLifeTime; //seconds

		Renderable2D(): mPos(),mModelMat(1), mMoveAmount(), mWidth(0),
						mHeight(0), mShader(0), mLifeTime(0.0f){}
		virtual void draw() = 0;
		virtual void update() {}
		virtual ~Renderable2D() {};

	};
}

#endif