#ifndef SH_RENDERABLE_3D_H
#define SH_RENDERABLE_3D_H

#include "Vec3.h"
#include "Shader.h"
#include "ShArray.h"
#include <Commons.h>

namespace Shady
{
	class Renderable3D
	{
	public:

		enum
		{
			POS_BUFFER = 0,
			TEX_BUFFER,
			COL_BUFFER,
			IND_BUFFER,
			NUM_BUFFERS
		};

		Vec3f mPos;
		Vec3f mRot;
		Array<Vec3f> mVerts;
		Array<u32> mIndices;
		Shader* mShader;
		
		Renderable3D(): mPos{}, mRot{}, mShader{nullptr}, mVerts{} {}	
		Renderable3D(Vec3f pos, Vec3f rot, Shader* shader): mPos{pos}, mRot{rot}, mShader{shader},
															mVerts{}, mIndices{}  {}	
		virtual void draw() = 0;
		virtual ~Renderable3D() { if(mShader) delete mShader;}
	};

}

#endif