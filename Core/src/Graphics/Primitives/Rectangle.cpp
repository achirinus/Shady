#include "Rectangle.h"


namespace Shady
{
	Rectangle::Rectangle(Vec3f pos, f32 width, f32 height, b8 filled, 
						b8 withBorder, Vec4f col, f32 lineWidth, Vec4f lineCol):
		Renderable2D(), isFilled(filled), hasBorder(withBorder)
	{
		
		Vec3f topLeft(pos.x, pos.y, pos.z);
		Vec3f topRight(pos.x + width, pos.y, pos.z);
		Vec3f botRight(pos.x + width, pos.y + height, pos.z);
		Vec3f botLeft(pos.x, pos.y + height, pos.z);

		if(isFilled) //Create the fill sprite
		{
			fillArea = new Sprite({ pos.x, pos.y, pos. z}, width, height, nullptr, col, false);
		}

		if((isFilled && hasBorder) || !isFilled)
		{
			Shader* lineShader = new Shader("basicLine", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER);
			
			topEdge = new Line2D(topLeft, topRight, lineCol, lineWidth, lineShader);
			rightEdge = new Line2D(topRight, botRight, lineCol, lineWidth, lineShader);
			botEdge = new Line2D(botLeft, botRight, lineCol, lineWidth, lineShader);
			leftEdge = new Line2D(topLeft, botLeft, lineCol, lineWidth, lineShader);
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