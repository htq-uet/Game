
#include "game.h"
#include "TextureManage.h"
#include "GameObject.h"
#include "Map.h"
GameObject* characture1;
GameObject* backGround;
Map* map;
SDL_Renderer* Game::renderer = nullptr; 
Game::Game() {

}
Game::~Game() {

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems Initialised!..." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			cout << "Window created!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			cout << "Renderer created!" << endl;
		}
		isRunning = true;
	}
	characture1 = new GameObject("assets/Player1.png", 0,0);
	backGround = new GameObject("assets/background.png", 0, 0);
	map = new Map();
};
void Game::handleEvents() {
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type) {
	default:
		break;
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}
void Game::update() {
	characture1->Update();
	
}
void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	characture1->Render();
	SDL_RenderPresent(renderer);

}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Closed!";
}

