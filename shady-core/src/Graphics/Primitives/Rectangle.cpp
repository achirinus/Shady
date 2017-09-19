#include "Rectangle.h"


namespace Shady
{
	Rectangle::Rectangle(f32 x, f32 y, f32 width, f32 height, Vec4f col, f32 lineWidth):
		Renderable2D()
	{
		if(!mShader)
		{
			mShader = new Shader("basicLine", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER);
		}
		Vec3f topLeft(x, y, 0.0f);
		Vec3f topRight(x + width, y, 0.0f);
		Vec3f botRight(x + width, y + height, 0.0f);
		Vec3f botLeft(x, y + height, 0.0f);
		top = new Line2D(topLeft, topRight, col, lineWidth, mShader);
		right = new Line2D(topRight, botRight, col, lineWidth, mShader);
		bot = new Line2D(botLeft, botRight, col, lineWidth, mShader);
		left = new Line2D(topLeft, botLeft, col, lineWidth, mShader);
	}

	void Rectangle::draw()
	{
		top->draw();
		left->draw();
		bot->draw();
		right->draw();
	}

	Rectangle::~Rectangle()
	{
		delete top;
		delete right;
		delete bot;
		delete left;
	}
}