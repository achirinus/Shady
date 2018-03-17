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
			
		Rectangle(Vec3f pos, f32 width, f32 height, b8 filled = false, b8 withBorder = false, 
					Vec4f col = Vec4f(1.0f, 1.0f, 1.0f, 1.0f), f32 lineWidth = 2, Vec4f lineCol = Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
		virtual ~Rectangle();
		virtual void draw(Renderer2D* renderer);


	};
}

#endif