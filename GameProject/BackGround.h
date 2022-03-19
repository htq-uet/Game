#pragma once
#include "game.h"
class BackGround
{
public:
	BackGround();
	~BackGround();
	void DrawBackGround();
private:
	SDL_Rect src, dest;

	SDL_Texture* background;


};

