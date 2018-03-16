#include "Rectangle.h"


namespace Shady
{
	Rectangle::Rectangle(f32 x, f32 y, f32 width, f32 height, b8 filled, 
						b8 withBorder, Vec4f col, f32 lineWidth):
		Renderable2D(), isFilled(filled), hasBorder(withBorder)
	{
		
		Vec3f topLeft(x, y, 0.0f);
		Vec3f topRight(x + width, y, 0.0f);
		Vec3f botRight(x + width, y + height, 0.0f);
		Vec3f botLeft(x, y + height, 0.0f);

		if(isFilled) //Create the fill sprite
		{
			fillArea = new Sprite({x, y, 0.0f}, width, height, nullptr, col, false);
		}

		if((isFilled && hasBorder) || !isFilled)
		{
			Shader* lineShader = new Shader("basicLine", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER);
			
			topEdge = new Line2D(topLeft, topRight, col, lineWidth, lineShader);
			rightEdge = new Line2D(topRight, botRight, col, lineWidth, lineShader);
			botEdge = new Line2D(botLeft, botRight, col, lineWidth, lineShader);
			leftEdge = new Line2D(topLeft, botLeft, col, lineWidth, lineShader);
		}
	}

	void Rectangle::draw(Renderer2D* renderer)
	{
		if(isFilled)
		{
			fillArea->draw(renderer);
		}
		if((isFilled && hasBorder) || !isFilled)
		{
			topEdge->draw(renderer);
			leftEdge->draw(renderer);
			botEdge->draw(renderer);
			rightEdge->draw(renderer);
			
		}

	}

	Rectangle::~Rectangle()
	{
		if(isFilled)
		{
			delete fillArea;
		}
		if((isFilled && hasBorder) || !isFilled)
		{
			Shader* lineShader = topEdge->mShader;
			delete topEdge;
			delete rightEdge;
			delete botEdge;
			delete leftEdge;

			
			delete lineShader;
		}
		
	}
}