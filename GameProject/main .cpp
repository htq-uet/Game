#include "CommonFunction.h"
#include "BaseObj.h"
#include <iostream>
#include "gamemap.h"
#include "Player.h"
#include "ImpTimer.h"
#include "Text.h"
#include "Menu.h"
#include "OtherObj.h"
#include "MapFiles.h"
#include "GameOver.h"

#include <iostream>
#include <string>

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
		mainfont = TTF_OpenFont("fonts/m6x11.ttf", 50);
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
	Map_LinkedList* mllist = new Map_LinkedList();

	mllist->insertAtTail("map/map1.txt");
	mllist->insertAtTail("map/map2.txt");

	MapFiles* tmp = mllist->getHead();

	GameMap game_map;
	int k = 1;
	string s = mllist->getHead()->mapfile;
	const char* c = s.c_str();
	game_map.LoadMap(c);
	game_map.LoadTiles(gscreen);

	Player player1;
	player1.LoadImg("assets/player1.png", gscreen);
	player1.setclip();

	Player player2;
	player2.LoadImg("assets/player2.png", gscreen);
	player2.setclip();

	OtherObj cutemus;
	cutemus.getPos(1400,640);
    cutemus.LoadImg("assets/mushroom.png", gscreen, 48);
	cutemus.getNum(4);
	cutemus.setclip();

	OtherObj gate;
	gate.getPos(480,550);
	gate.LoadImg("assets/gate.png",gscreen, 32);
	gate.getNum(14);
	gate.setclip();



	Text menu_text;
	menu_text.SetColor(Text::PINK);
	menu_text.SetText("Level " + to_string(k));
	menu_text.LoadFont(mainfont, gscreen);

	Menu menu;
	bool quit = false;
	int state=0;
	enum STATE {
		isPlaying = 1,
		isGameover = 2,
		isToturial = 3,
	};
	
	if (menu.loadMenu(gscreen, mainfont) == 0) {
		Mix_PlayMusic(background_music, -1);
		state = isPlaying;
	}
	if (menu.loadMenu(gscreen, mainfont) == QUIT) {
		quit = true;
	}
	GameOver _gameover;
	while (!quit) {
		if (state==isGameover)
		{	
			cout << "GAMEOVER";
			
			if (_gameover.loadGameOver(gscreen, mainfont)==0) {
				
				player1.setPos(332, 662);
				player2.setPos(332, 662);
				player1.changeState();
				player2.changeState();

				state = isPlaying;

			}
			else if (_gameover.loadGameOver(gscreen, mainfont) == QUIT) {
				quit = true;
			}
			else if (_gameover.isQuit()) quit = true;
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		else if (state==isToturial)
		{

		}

		else if (state==isPlaying)
		{
			fps_timer.start();
		
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				else if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
					case SDLK_0:
						if (Mix_PlayingMusic() == 0) {
						}
						break;
					}
				}
				player1.changeState();
				player2.changeState();
				player1.handleEvent1(event, gscreen, sound);
				player2.handleEvent2(event, gscreen, sound);
			}
			SDL_SetRenderDrawColor(gscreen, 255, 255, 255, 255);
			SDL_RenderClear(gscreen);

			background.Render(gscreen, NULL);

			Map map_data = game_map.getMap();


			player1.DoPlayer1(map_data, 0);
			player1.show1(gscreen);

			player2.DoPlayer2(map_data, 1);
			player2.show2(gscreen);


			cutemus.show(gscreen);

			gate.show(gscreen);

			game_map.SetMap(map_data);
			game_map.DrawMap(gscreen);

			if (player1.checkNextLevelP1() == true && player2.checkNextLevelP2() == true) {
				cout << "NEXT!" << endl;

				string s = tmp->nextlevel->mapfile;
				const char* v = s.c_str();
				game_map.LoadMap(v);
				game_map.LoadTiles(gscreen);
			}
			if (player1.GameOver1()==1||player2.GameOver2()==1){                
				state = isGameover;

			}

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
	}
	close();
	menu_text.Free();
	return 0;
}
