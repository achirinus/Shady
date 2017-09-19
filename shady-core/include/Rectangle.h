#ifndef SH_RECTANGLE_H
#define SH_RECTANGLE_H

#include "Line2D.h"
namespace Shady
{
	class Rectangle : public Renderable2D
	{
		private:
		Line2D* top;
		Line2D* right;
		Line2D* bot;
		Line2D* left;
		public:

		Rectangle(f32 x, f32 y, f32 width, f32 height, Vec4f col = Vec4f(1.0f, 1.0f, 1.0f, 1.0f),
				f32 lineWidth = 2);
		virtual ~Rectangle();
		virtual void draw();


	};
}

#endif