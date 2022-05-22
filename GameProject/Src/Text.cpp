#include "Text.h"

Text::Text() {
	textcolor.r = 255;
	textcolor.g = 255;
	textcolor.b = 255;
	texture = NULL; 
}
Text::~Text() {

}
bool Text::LoadFont(TTF_Font* font, SDL_Renderer* renderer) {
	SDL_Surface* text_sur = TTF_RenderText_Solid(font, str.c_str(), textcolor);
	if (text_sur!=NULL) {
		texture = SDL_CreateTextureFromSurface(renderer, text_sur);
		wtext = text_sur->w;
		htext = text_sur->h;

		SDL_FreeSurface(text_sur); 
	}
	return texture != NULL;
}

void Text::Free() {
	if (texture!=NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}
void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
	textcolor.r = red;
	textcolor.g = green;
	textcolor.b = blue;
}

void Text::SetColor(int color) {
	if (color == WHITE) {
		SDL_Color c = { 255,255,255 };
		textcolor = c;  
	}
	else if (color == BLACK) {
		SDL_Color c = { 0,0,0 };
		textcolor = c;
	}
	else if (color == PINK) {
		SDL_Color c = { 255,195,236 };
		textcolor = c;
	}

}
void Text::SetRect(const int& xp,const int& yp) {
	rec.x = xp;
	rec.y = yp;
	rec.w = wtext;
	rec.h = htext;
}
SDL_Rect Text::GetRect() const {
	return rec;
}
void Text::RenderText(SDL_Renderer* renderer, int xpos, int ypos, SDL_Rect* clip , double angle , SDL_Point* center, SDL_RendererFlip flip ) {
	SDL_Rect renderQuad = { xpos,ypos,wtext,htext };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}
