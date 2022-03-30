#include "CommonFunction.h"
#include "BaseObj.h"
#include <iostream>
#include "gamemap.h"
#include "Player1.h"
#include "ImpTimer.h"
#include "Text.h"

using namespace std;
BaseObj background;
TTF_Font *mainfont;
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
		if (TTF_Init() == -1) {
			success = false;
		}
		mainfont = TTF_OpenFont("fonts/m6x11.ttf", 100);
		if (mainfont == NULL) {
			success = false;
		}
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) <0) {
		success = false;
	}
	background_music = Mix_LoadMUS("sounds/background.wav");
	sound[0] = Mix_LoadWAV("sounds/jump.wav");

	if (background_music==NULL||sound[0] == NULL) {
		cerr << "Sound Error!\n" << Mix_GetError();
		success = false;
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
	TTF_CloseFont(mainfont);
	mainfont = NULL;
	SDL_DestroyWindow(gwindow);
	gwindow = NULL;
	Mix_FreeMusic(background_music);
	background_music = NULL;
	Mix_FreeChunk(sound[0]);
	sound[0] = NULL;
	Mix_CloseAudio();

	TTF_Quit();

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

	Player1 player1;
	player1.LoadImg("assets/player1.png", gscreen);
	player1.setclip();

	Player1 player2;
	player2.LoadImg("assets/player2.png", gscreen);
	player2.setclip();

	Text menu_text;
	menu_text.SetColor(Text::PINK);
	menu_text.SetText("Hello!");
	menu_text.LoadFont(mainfont, gscreen);



	bool quit = false;
	while (!quit) {
		fps_timer.start();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_0:
					if (Mix_PlayingMusic() == 0) {
						Mix_PlayMusic(background_music, -1);
					}
					break;
				}
			}
			player1.handleEvent(event, gscreen,sound);
		}
		SDL_SetRenderDrawColor(gscreen, 255, 255, 255,255);
		SDL_RenderClear(gscreen);

		background.Render(gscreen, NULL);
		
		Map map_data = game_map.getMap();


		player1.DoPlayer(map_data);
		player1.show(gscreen);

		game_map.SetMap(map_data);
		game_map.DrawMap(gscreen);
		
		

		int real_time = fps_timer.get_tick();
		int time_per_frame = 1000 / FPS;

		
		
		menu_text.RenderText(gscreen, 800, 15);


		SDL_RenderPresent(gscreen);
		if (real_time < time_per_frame) {
			int delay = time_per_frame - real_time;
			if (delay >= 0) {
				SDL_Delay(delay);
			}
		}
	}
	close();
	menu_text.Free();
	return 0; 
}