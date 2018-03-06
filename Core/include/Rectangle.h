#ifndef SH_RECTANGLE_H
#define SH_RECTANGLE_H

#include "Line2D.h"
#include "Sprite.h"
namespace Shady
{
	class Rectangle : public Renderable2D
	{
		private:
		Line2D* topEdge;
		Line2D* rightEdge;
		Line2D* botEdge;
		Line2D* leftEdge;
		Sprite* fillArea;
		b8 isFilled;
		b8 hasBorder;
		public:

		Rectangle(f32 x, f32 y, f32 width, f32 height, b8 filled = false, b8 withBorder = false, 
					Vec4f col = Vec4f(1.0f, 1.0f, 1.0f, 1.0f), f32 lineWidth = 2);
		virtual ~Rectangle();
		virtual void draw();


	};
}

#endif