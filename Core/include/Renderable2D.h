#ifndef SH_RENDERABLE_2D_H
#define SH_RENDERABLE_2D_H

#include "Vec3.h"
#include "Matrix4f.h"
#include "Commons.h"
#include "ShArray.h"
#include "Shader.h"

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
		Array<Shader*> mShaders;
		f32 mLifeTime; //seconds
		b8 mOwnShader;
		Renderable2D(): mPos(),mModelMat(1), mMoveAmount(), mWidth(0),
						mHeight(0), mShaders(), mLifeTime(0.0f), mOwnShader(false){}
		virtual void draw() = 0;
		virtual void update() {}
		virtual ~Renderable2D() {};

	};
}

#endif