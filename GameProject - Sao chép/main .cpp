#include "CommonFunction.h"
#include "BaseObj.h"
#include <iostream>
#include "gamemap.h"
#include "PlayerObj.h"
#include "ImpTimer.h"

using namespace std;
BaseObj background;
bool init() {
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) {
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	gwindow = SDL_CreateWindow("Kit&Kat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1760, 960, SDL_WINDOW_SHOWN);
	if (gwindow == NULL) {
		success = false;
	}
	else {
		gscreen = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
		if (gscreen == NULL) {
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(gscreen, 255, 255, 255, 255);
			int imgflags = IMG_INIT_PNG;
			if (!(IMG_Init(imgflags) && imgflags))
				success = false;
		}
	}
	return success;
}
bool LoadBackGround() {
	bool ret = background.LoadImg("assets/background1.png",gscreen);
	return ret;
}
void close() {
	background.Free();
	SDL_DestroyRenderer(gscreen);
	gscreen = NULL;

	SDL_DestroyWindow(gwindow);
	gwindow = NULL;

	IMG_Quit(); 
	SDL_Quit();
}

int main(int arcs, char* argv[]) {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 framestart;
	int frametime;

	ImpTimer fps_timer;

	if (!init()) {
		return -1;
	}
	if (LoadBackGround() == false) {
		return -1;
	}
	GameMap game_map;
	game_map.LoadMap("map1.dat.txt");
	game_map.LoadTiles(gscreen);

	PlayerObj player1;
	player1.LoadImg("assets/player1.png", gscreen);
	player1.setclip();

	PlayerObj player2;
	player2.LoadImg("assets/player2.png", gscreen);
	player2.setclip();

	bool quit = false;
	while (!quit) {
		fps_timer.start();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}

			player1.handleEvent(event, gscreen);
		}
		SDL_SetRenderDrawColor(gscreen, 255, 255, 255, 255);
		SDL_RenderClear(gscreen);

		background.Render(gscreen, NULL);
		game_map.DrawMap(gscreen);
		Map map_data = game_map.getMap();

		player1.DoPlayer(map_data);
		player1.show(gscreen);

		
		
		SDL_RenderPresent(gscreen);

		int real_time = fps_timer.get_tick();
		int time_per_frame = 1000 / FPS;

		if (real_time < time_per_frame) {
			int delay = time_per_frame - real_time;
			if (delay >= 0) {
				SDL_Delay(delay);
			}
		}
	}
	close();
	return 0; 
}