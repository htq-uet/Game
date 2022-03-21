#include "BackGround.h"
#include "TextureManage.h"
BackGround::BackGround() {
	background = TextureManage::loadTexture("assets/background1.png");
	flip = SDL_FLIP_NONE;
	src.x = src.y = 0;
	dest.x = dest.y = 0;
	src.w = dest.w = 1760;
	src.h = dest.h = 960;
}
void BackGround::DrawBackGround() {
	TextureManage::Draw(background, src, dest,flip);
}