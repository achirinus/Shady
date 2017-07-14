#include "Texture.h"
#include <cstdio>
#include "stb_image.c"

namespace Shady
{
	void Texture::initGlTexture(Bitmap bmp)
	{
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.contents);
	}

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

	Texture::Texture(const char* fileName)
	{
		SH_ASSERT(fileName);
		int width, height, numComponents;
		//TODO write my own image loader
		unsigned char* imageData = stbi_load(fileName, &width, &height, &numComponents, 4);

		if (!imageData)
		{
			//TODO better log
			DEBUG_OUT_ERR("Failed to load texture");
		}
		mWidth = width;
		mHeight = height;
		
		initGlTexture(imageData);

		stbi_image_free(imageData);
	}

	Texture::Texture(Bitmap bmp)
	{
		mWidth = bmp.width;
		mHeight = bmp.height;

		if(bmp.contents)
		{
			initGlTexture(bmp);
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