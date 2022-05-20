#include "BaseObj.h"
BaseObj::BaseObj() {
	texture = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}
BaseObj::~BaseObj() {
	Free();
}


//Create a new texture from the loaded surface
bool BaseObj::LoadImg(string path, SDL_Renderer* screen) {
	Free();

	SDL_Texture* ntexture = NULL;

	SDL_Surface* loadimg = IMG_Load(path.c_str());
	if (loadimg != NULL) {
		SDL_SetColorKey(loadimg, SDL_TRUE, SDL_MapRGB(loadimg->format, 0, 255, 255));

		ntexture = SDL_CreateTextureFromSurface(screen, loadimg);
		if (ntexture != NULL) {
			rect.w = loadimg->w;
			rect.h = loadimg->h;
		}
		SDL_FreeSurface(loadimg);
	}
	texture = ntexture;

	return texture != NULL;
}

//Render texture to screen
void BaseObj::Render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x,rect.y,rect.w,rect.h };
	SDL_RenderCopy(des, texture, clip, &renderquad);
}

// Free Baseobj
void BaseObj::Free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
  		texture = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}

