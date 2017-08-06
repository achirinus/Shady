#ifndef SH_GAMESTATE_H
#define SH_GAMESTATE_H

#include "Sprite.h"
#include "Camera2D.h"
#include "Renderer2D.h"
#include "ShFont.h"
#include "Line2D.h"


namespace Shady
{
	
	struct GameState
	{
		Sprite* sprite;
		Camera2D* camera2d;
		Renderer2D* renderer2d;
		Font* currentFont;
		Text2D* text;
		Line2D* line;
	};
}

#endif