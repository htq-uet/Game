#include "OtherObj.h"

OtherObj::OtherObj() {
    frame = 0;
	widthframe = 0;
	heightframe = 0;
}

OtherObj::~OtherObj() {
	Free();
}

//set the object's position value
void OtherObj::setPos(float x, float y)
{
    xpos = x;
    ypos = y;
}

//get frame's size
void OtherObj::getFrame(int _f)
{
    frameSize = _f;
}

//Load image at specified path
bool OtherObj::LoadImg(string path, SDL_Renderer* renderer, int frameSize) {
	bool check = BaseObj::LoadImg(path, renderer);

	if (check == true) {
		widthframe = frameSize;
		heightframe = frameSize;
	}
	return check;
}


//get number of frames showing the character's state
void OtherObj::getNum(int _n){
	n=_n;
}

//Set clip of an object's state
void OtherObj::setclip() {
	if (widthframe > 0 && heightframe > 0) {
		for(int i=0;i<n;i++){
		FRAME_CLIP[i].x = widthframe*i;
		FRAME_CLIP[i].y = 0;
		FRAME_CLIP[i].w = widthframe;
		FRAME_CLIP[i].h = heightframe;
		}
	}
}

//Get an object's starting position
float OtherObj::Get_ObjPosx()
{
    return xpos;
}

float OtherObj::Get_ObjPosy()
{
    return ypos;
}

//Show the object
void OtherObj::show(SDL_Renderer* des) {
if (frame >= 0) {
			++frame;
		}

	else {
		frame = 0;
	}
	 if (frame / n >= n) {
		frame=0;
	}

	rect.x = xpos;
	rect.y = ypos;

	SDL_Rect* currentclip = &FRAME_CLIP[frame/n];

	SDL_Rect renderQuad = { rect.x,rect.y,widthframe * 3,heightframe * 3 };
	if (currentclip != NULL)
	{
		renderQuad.w = 3*currentclip->w;
		renderQuad.h = 3*currentclip->h;
	}

	SDL_RenderCopy(des, texture, currentclip, &renderQuad);
}




