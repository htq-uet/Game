#pragma once
#ifndef GAMEMAP_H_
#define GAMEMAP_H_
#include "CommonFunction.h"
#include "BaseObj.h"
class TileMap: public BaseObj
{
public:
	TileMap() {
		;
	}
	~TileMap() {
		;
	}

};
class GameMap
{
public:
	GameMap();
	~GameMap();

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void SetMap(const Map& gMap) {
		gamemap = gMap;
	}
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const {
		return gamemap;
	}

private:
	Map gamemap;
	TileMap tilemap[20];
};

#endif //!GAMEMAP_H