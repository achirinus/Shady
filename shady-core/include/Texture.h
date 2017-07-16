#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew.h>
#include "Commons.h"
#include "Graphics.h"


namespace Shady
{

	class Texture
	{
	public:
		Texture(const char* fileName);
		Texture(Bitmap bmp);
		Texture(const Texture& other) = default;
		~Texture();

		void bind(GLuint unit);
		void unbind(GLuint unit);

		u32 getWidth() {return mWidth;}
		u32 getHeight() {return mHeight;}
	private:

		void initGlTexture(Bitmap bmp);
		void initGlTexture(u8* imageData);

		GLuint mTexture;
		u32 mWidth;
		u32 mHeight;
	};

}


#endif