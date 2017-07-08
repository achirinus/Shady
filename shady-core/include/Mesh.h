#ifndef MESH_H
#define MESH_H

#include "Vec3.h"

#include <glew.h>
namespace Shady
{
	namespace Graphics
	{

		class Vertex
		{
		
		public:
			Vec3f mPos;
			Vec2f mTexCoord;

			Vertex(const Vec3f& pos,const Vec2f texCoord)
			{
				mPos = pos;
				mTexCoord = texCoord;
			}
		};

		class Mesh
		{
		public:
			Mesh(Vertex* vertices, unsigned int numVertices);

			void draw();
			void bind();
			void unbind();
			~Mesh();
		private:

			enum
			{
				POSITION_VB = 0,
				TEXCOORD_VB,
				NUM_BUFFERS
			};
			GLuint mVAO;
			GLuint mVBO[NUM_BUFFERS];
			unsigned int mDrawCount;
		};
	}
}

#endif