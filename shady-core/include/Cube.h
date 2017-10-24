#ifndef SH_CUBE_H
#define SH_CUBE_H 

#include "Renderable3D.h"
#include <ShadyGL.h>


namespace Shady
{
	class Cube : public Renderable3D
	{
		GLuint mVBO[NUM_BUFFERS];
		GLuint mVAO;
		f32 mSize;
	public:
		Cube() = default;
		Cube(f32 size, Vec3f pos = {}, Shader* shader = nullptr);
		~Cube();
		
		Matrix4f getModelMat();
		void update(f32 dt);
		void draw();
	};
}

#endif