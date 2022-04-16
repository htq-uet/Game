#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"



class Mushroom : public BaseObj
{
public:
	Mushroom();
	~Mushroom();
	bool LoadImg(string path, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void getNum(int _n);
	void setclip();
	void set_renderquad();
	SDL_Rect get_rect();

private:
	float xval;
	float yval;
	float xpos;
	float ypos;
	int widthframe;
	int heightframe;
	SDL_Rect FRAME_CLIP[5];
	SDL_Rect render_Quad;
	int frame;
	int n;

};



