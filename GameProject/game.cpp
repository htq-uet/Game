
#include "game.h"
#include "TextureManage.h"

#include "Map.h"
#include "BackGround.h" 
#include "Components.h"


Map* map;
BackGround* backgr;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());
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

	map = new Map();
	backgr = new BackGround();
	player.addComponent<PositionComponent>(0,0);
	player.addComponent<SpriteComponent>("assets/player1.png");
	
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
	manager.refresh();
	manager.update();
	if (player.getComponent<PositionComponent>().x() > 200) {
		player.getComponent<SpriteComponent>().setTex("assets/player2.png");
	}
}
void Game::render() {

	SDL_RenderClear(renderer);
	backgr->DrawBackGround();
	map->DrawMap();
	manager.draw();
	
	SDL_RenderPresent(renderer);

}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	cout << "Game Closed!";
}

