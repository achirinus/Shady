#ifndef SH_SPRITE_H
#define SH_SPRITE_H


#include "String.h"
#include "ShKeyboard.h"
#include "Texture.h"
#include "ShMath.h"
#include "Renderable2D.h"

namespace Shady
{
	class Sprite : public Renderable2D
	{
		
	public:
		
		Vec4f mColor;
		f32 mScale;
		f32 mPitch;
		f32 mYaw;
		f32 mRoll;
		GLuint mVBO[NUM_BUFFERS];
		GLuint mVAO;
		Texture* mTexture;
		b8 mIsTransparent;
		
		Sprite(const Vec3f& pos, u32 width, u32 height, Texture* texture = nullptr,  
				const Vec4f& color = {1.0f, 1.0f, 1.0f, 1.0f}, b8 posInCenter = true, Shader* shader = 0);
		Sprite(const Vec3f& pos, Texture* texture, b8 posInCenter = true, Shader* shader = 0);									 
		virtual ~Sprite();

		virtual void SetTransparency(b8 transparent);
		virtual Matrix4f getModelMat();
		virtual void initGlBuffers(const Vec3f& pos, const Vec4f& color, b8 posInCenter);
		virtual void update();
		virtual Vec3f getCurrentPos() {return mPos + mMoveAmount;}
		virtual void setColor(const Vec4f& color);
		virtual void setTexture(Texture* tex);
		virtual bool hasTexture() {return (bool)mTexture;}
		virtual void move(const Vec3f& vec);
		virtual void rotate(f32 pitch, f32 yaw, f32 roll);
		virtual void scale(f32 scale);
		virtual f32 getScale() {return mScale;}
		virtual void draw(Renderer2D* renderer);
	};
}

#endif