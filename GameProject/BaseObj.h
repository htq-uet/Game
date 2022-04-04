#pragma once
#include "CommonFunction.h"

using namespace std;
class BaseObj
{
public:
	BaseObj();
	~BaseObj();
	void SetRect(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect getRect() const {
		return rect;
	}
	SDL_Texture* gettexture() const {
		return texture;
	}

	virtual bool LoadImg(string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
	void setColor(const Uint8& red, const Uint8& green, const Uint8& blue);
	void setAlpha(const Uint8& alpha);
	void setBlendMode(const SDL_BlendMode& blending);

protected:
	SDL_Texture* texture;
	SDL_Rect rect;
	
	
};

