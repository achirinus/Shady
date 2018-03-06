#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H


#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "ShString.h"
#include "Windows.h"
namespace Shady
{
	
	struct Vertex
	{
		Vec4f mPosition;
		//Vec3f mNormal;
		//Vec2f mTexCoord;

		Vertex(Vec4f pos/*, Vec3f norm, Vec2f tex*/): mPosition(pos)
													//mNormal(norm),
													//mTexCoord(tex) 
													{};
		Vertex(const Vertex& other) = default;
		Vertex() = default;
		String toString()
		{
			c8 all[128];
			sprintf_s(all, 128, "%f, %f, %f, %f \n", mPosition.x, mPosition.y, mPosition.z, mPosition.w);
			return String(all);
		}
	};
	
}

#endif
