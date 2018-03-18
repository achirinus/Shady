#include "Rectangle.h"
#include "ShaderManager.h"
#define ENABLE_LINES 1

namespace Shady
{
	
	Rectangle::Rectangle(Vec3f pos, f32 width, f32 height, b8 filled, 
						b8 withBorder, Vec4f col, f32 lineWidth, Vec4f lineCol): isFilled(filled), hasBorder(withBorder)
	{
		if(isFilled) //Create the fill sprite
		{
			fillArea = new Sprite({ pos.x, pos.y, pos. z}, width, height, nullptr, col, false);
		}
#if ENABLE_LINES
		if((isFilled && hasBorder) || !isFilled)
		{
			Vec3f topLeft(pos.x, pos.y, pos.z - 1.1f);
			Vec3f topRight(pos.x + width, pos.y, pos.z - 1.1f);
			Vec3f botRight(pos.x + width, pos.y + height, pos.z - 1.1f);
			Vec3f botLeft(pos.x, pos.y + height, pos.z - 0.1f);

			Shader* lineShader = ShaderManager::CreateShader("basicLine");
			
			topEdge = new Line2D(topLeft, topRight, lineCol, lineWidth, lineShader);
			rightEdge = new Line2D(topRight, botRight, lineCol, lineWidth, lineShader);
			botEdge = new Line2D(botLeft, botRight, lineCol, lineWidth, lineShader);
			leftEdge = new Line2D(topLeft, botLeft, lineCol, lineWidth, lineShader);
		}
#endif
	}

	void Rectangle::draw(Renderer2D* renderer)
	{
		if(isFilled)
		{
			fillArea->draw(renderer);
		}
#if ENABLE_LINES
		if((isFilled && hasBorder) || !isFilled)
		{
			topEdge->draw(renderer);
			leftEdge->draw(renderer);
			botEdge->draw(renderer);
			rightEdge->draw(renderer);
		}
#endif
	}

	Rectangle::~Rectangle()
	{
		if(isFilled)
		{
			delete fillArea;
		}
#if ENABLE_LINES
		if((isFilled && hasBorder) || !isFilled)
		{
			delete topEdge;
			delete rightEdge;
			delete botEdge;
			delete leftEdge;
		}
#endif	
	}
}