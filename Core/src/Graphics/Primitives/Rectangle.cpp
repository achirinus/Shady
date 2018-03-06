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
			mShaders.Add(new Shader("basic", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER));
			fillArea = new Sprite({x, y, 0.0f}, width, height, nullptr, col, false, mShaders[0]);
		}

		if((isFilled && hasBorder) || !isFilled)
		{
			mShaders.Add(new Shader("basicLine", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER));
			Shader* tempShader = 0;
			if(isFilled) 
			{
				tempShader = mShaders[1];
			}
			else
			{
				tempShader = mShaders[0];
			}
			topEdge = new Line2D(topLeft, topRight, col, lineWidth, tempShader);
			rightEdge = new Line2D(topRight, botRight, col, lineWidth, tempShader);
			botEdge = new Line2D(botLeft, botRight, col, lineWidth, tempShader);
			leftEdge = new Line2D(topLeft, botLeft, col, lineWidth, tempShader);
		}
	}

	void Rectangle::draw()
	{
		if(isFilled)
		{
			fillArea->draw();
		}
		if((isFilled && hasBorder) || !isFilled)
		{
			topEdge->draw();
			leftEdge->draw();
			botEdge->draw();
			rightEdge->draw();
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
			delete topEdge;
			delete rightEdge;
			delete botEdge;
			delete leftEdge;
		}
	}
}