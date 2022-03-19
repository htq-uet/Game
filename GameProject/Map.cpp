#include "Map.h"
#include "TextureManage.h"

int lv1[20][25]={
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
Map::Map() {
	dirt = TextureManage::loadTexture("assets/dirt.png");
	grass= TextureManage::loadTexture("assets/grass.png");
	water= TextureManage::loadTexture("assets/water.png");

	LoadMap(lv1);
	src.x = src.y = 0;
	dest.x = dest.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;
}
Map::~Map() {
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(dirt);
}
void Map::LoadMap(int arr[20][25]) {
	for (int row = 0;row < 20;row++) {
		for (int column = 0;column < 25;column++) {
			map[row][column] = arr[row][column];
		}
	}
}
void Map::DrawMap() {
	int type = 0;
	for (int row = 0;row < 20;row++) {
		for (int column = 0;column < 25;column++) {
			type = map[row][column];
			dest.x = column * 32;
			dest.y = row * 32;
			switch (type)
			{
			default:
				break;
			case 0:
				TextureManage::Draw(water, src, dest);
				break;
			case 1:
				TextureManage::Draw(grass, src, dest);
				break;
			case 2:
				TextureManage::Draw(dirt, src, dest);
				break;
			}
		}
	}
}