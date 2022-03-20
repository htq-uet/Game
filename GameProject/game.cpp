
#include "game.h"
#include "TextureManage.h"

#include "Map.h"
#include "BackGround.h" 
#include "Components.h"
#include "Collision.h"
#include "Vector2D.h"
Map* map;
BackGround* backgr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::e; 

vector<ColliderComponent*>Game::colliders;

Manager manager;
auto& player1(manager.addEntity());
auto& player2(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());
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

	tile0.addComponent<TileComponent>(232, 200, 32, 32, 1);
	tile1.addComponent<TileComponent>(232, 232, 32, 32, 1);
	tile1.addComponent<ColliderComponent>("water");
	tile2.addComponent<TileComponent>(232, 264, 32, 32, 1);
	tile2.addComponent<ColliderComponent>("water");

	player1.addComponent<TransformComponent>(100,100);
	player1.addComponent<SpriteComponent>("assets/player1.png",4,100);
	player1.addComponent<KeyboardController>();
	player1.addComponent<ColliderComponent>("player1");

	player2.addComponent<TransformComponent>(800, 100);
	player2.addComponent<SpriteComponent>("assets/player2.png",4,100);
	player2.addComponent<KeyboardController2>();
	player2.addComponent<ColliderComponent>("player2");


};
void Game::handleEvents() {

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
	for(auto cc: colliders){
	if (Collision::isColliding(player1.getComponent<ColliderComponent>(),*cc)) {
		player1.getComponent<TransformComponent>().velocity * 1;
		cout << "Wall Hit!" << endl;
		break;
	}
	else
	if (Collision::isColliding(player2.getComponent<ColliderComponent>(),*cc)) {
		player2.getComponent<TransformComponent>().velocity * -0.2;
		player2.getComponent<TransformComponent>().velocity * 1;
		cout << "Wall Hit!" << endl;
		break;
	}
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

