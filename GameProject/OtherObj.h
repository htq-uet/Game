#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"


class OtherObj : public BaseObj
{
public:
	OtherObj();
	~OtherObj();
	bool LoadImg(string path, SDL_Renderer* renderer, int frameSize);
	void show(SDL_Renderer* des);
	void getNum(int _n);
	void getFrame(int _f);
	void setclip();
	void set_renderquad();
	void setPos(float x, float y);
	float Get_ObjPosx();
	float Get_ObjPosy();

private:
	float xpos;
	float ypos;
	int widthframe;
	int heightframe;
	int n;
	SDL_Rect FRAME_CLIP[15];
	int frame;

	int frameSize;

};
