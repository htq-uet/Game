#include "BackGround.h"
#include "TextureManage.h"
BackGround::BackGround() {
	background = TextureManage::loadTexture("assets/background.png");

	src.x = src.y = 0;
	dest.x = dest.y = 0;
	src.w = dest.w = 800;
	src.h = dest.h = 640;
}
void BackGround::DrawBackGround() {
	TextureManage::Draw(background, src, dest);
}