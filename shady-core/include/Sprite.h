#ifndef SH_SPRITE_H
#define SH_SPRITE_H

#include "Vec3.h"
#include "Matrix4f.h"
#include "Commons.h"
#include "String.h"
#include "ShKeyboard.h"
#include "Texture.h"

namespace Shady
{
	class Sprite
	{
		enum
		{
			POS_BUFFER = 0,
			TEX_BUFFER,
			COL_BUFFER,
			NUM_BUFFERS
		};
	public:
		Vec3f mPos;
		Vec4f mColor;
		Vec3f mMoveAmount;
		u32 mWidth;
		u32 mHeight;
		f32 mScale;
		f32 mPitch;
		f32 mYaw;
		f32 mRoll;
		GLuint mVBO[NUM_BUFFERS];
		GLuint mVAO;

		Texture* mTexture;

		
		Sprite(const Vec3f& pos, u32 width, u32 height, Texture* texture = nullptr,  
											const Vec4f& color = {1.0f, 1.0f, 1.0f, 1.0f});
																		 
		~Sprite();

		Matrix4f getModelMat();
		void update();
		void setColor(const Vec4f& color);
		bool hasTexture() {return (bool)mTexture;}
		void move(const Vec3f& vec);
		void rotate(f32 pitch, f32 yaw, f32 roll);
		void scale(f32 scale);
		void draw();
	};
}

#endif