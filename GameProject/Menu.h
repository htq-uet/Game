#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"
class Menu: public BaseObj
{
public:
	Menu();
	~Menu();
	
	int loadMenu(SDL_Renderer* renderer, TTF_Font* font);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);

private:
	int xpos=0;
	int ypos=0;
};

