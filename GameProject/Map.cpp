#include "Map.h"
#include "TextureManage.h"
#include "game.h"
#include <fstream>
#include <string>
Map::Map() {
	
}
Map::~Map() {
	
}
void Map::LoadMap(string path, int sizeX, int sizeY) {
	char tile;
	fstream mapFile;
	mapFile.open(path);

	for (int y = 0;y< sizeY;y++) {
		for (int x = 0;x < sizeX;x++) {
			mapFile.get(tile);
			Game::addTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();
		}
	}

	mapFile.close();
}
