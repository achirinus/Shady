#include "Texture.h"
#include <cstdio>
#include "stb_image.c"

namespace Shady
{
	namespace Graphics
	{
		Texture::Texture(const char* fileName)
		{
			int width, height, numComponents;
			//TODO write my own image loader
			unsigned char* imageData = stbi_load(fileName, &width, &height, &numComponents, 4);

			if (!imageData)
			{
				//TODO better log
				printf("Failed to load texture");
			}

			glGenTextures(1, &mTexture);
			glBindTexture(GL_TEXTURE_2D, mTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

			stbi_image_free(imageData);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &mTexture);
		}

		void Texture::bind(GLuint unit)
		{
			//TODO assert 0 > unit < 31
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, mTexture);
		}
	}
}