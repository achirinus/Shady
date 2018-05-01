#include "Texture.h"
#include <cstdio>
#include "ImageLoader.h"


namespace Shady
{
	
	void Texture::initGlTexture(u8* imageData)
	{
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}

	Texture::Texture(const char* fileName): mWidth(0), mHeight(0), mTexture(0)
	{
		SH_ASSERT(fileName);
		
		//TODO write my own image loader
		Bitmap bmp = ImageLoader::LoadFromFile(fileName);

		if (!bmp.contents)
		{
			//TODO better log
			DEBUG_OUT_ERR("Failed to load texture");
		}
		mWidth = bmp.width;
		mHeight = bmp.height;
		
		initGlTexture((u8*)bmp.contents);

		ImageLoader::FreeImage(&bmp);
	}

	Texture::Texture(Bitmap bmp): mWidth(0), mHeight(0), mTexture(0)
	{
		if (bmp.contents)
		{
			mWidth = bmp.width;
			mHeight = bmp.height;
			initGlTexture((u8*)bmp.contents);
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mTexture);
	}

	void Texture::bind(GLuint unit)
	{
		SH_ASSERT(( 0 >= unit) &&  (unit < 31));

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, mTexture);
	}

	void Texture::unbind(GLuint unit)
	{
		SH_ASSERT(( 0 >= unit) &&  (unit < 31));

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}