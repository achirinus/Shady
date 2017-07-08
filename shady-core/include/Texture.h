#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew.h>

namespace Shady
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture(const char* fileName);
			~Texture();

			void bind(GLuint unit);

		private:
			GLuint mTexture;
		};
	}
}


#endif