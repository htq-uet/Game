#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"
class Tutorial: public BaseObj
{
public:
	Tutorial();
	~Tutorial();

	int loadTutorial(SDL_Renderer* renderer);

private:
	int xpos=0;
	int ypos=0;
};


