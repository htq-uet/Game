#include "Mushroom.h"


Mushroom::Mushroom() {
	frame = 0;
	xpos = 900;
	ypos = 640;
	xval = 0;
	yval = 0;
	widthframe = 0;
	heightframe = 0;

}
Mushroom::~Mushroom() {
	Free();
}
bool Mushroom::LoadImg(string path, SDL_Renderer* renderer) {
	bool check = BaseObj::LoadImg(path, renderer);

	if (check == true) {
		widthframe = 48;
		heightframe = 48;
	}
	return check;
}

void Mushroom::getNum(int _n) {
	n = _n;
}


void Mushroom::setclip() {
	if (widthframe > 0 && heightframe > 0) {
		for (int i = 0; i < n; i++) {
			FRAME_CLIP[i].x = widthframe * i;
			FRAME_CLIP[i].y = 0;
			FRAME_CLIP[i].w = widthframe;
			FRAME_CLIP[i].h = heightframe;
		}
	}
}

void Mushroom::show(SDL_Renderer* des) {
	if (frame >= 0) {
		++frame;
	}

	else {
		frame = 0;
	}
	if (frame / n >= n) {
		frame = 0;
	}

	rect.x = xpos;
	rect.y = ypos;

	SDL_Rect* currentclip = &FRAME_CLIP[frame / n];

	SDL_Rect renderQuad = { rect.x,rect.y,widthframe * 3,heightframe * 3 };
	if (currentclip != NULL)
	{
		renderQuad.w = 3 * currentclip->w;
		renderQuad.h = 3 * currentclip->h;
	}


	SDL_RenderCopy(des, texture, currentclip, &renderQuad);
}




