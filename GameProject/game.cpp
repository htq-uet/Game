
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

Manager manager;
auto& player1(manager.addEntity());
auto& player2(manager.addEntity());
auto& wall(manager.addEntity());

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
	player1.addComponent<TransformComponent>(0,0);
	player1.addComponent<SpriteComponent>("assets/player1.png");
	player1.addComponent<KeyboardController>();
	player1.addComponent<ColliderComponent>("player1");

	player2.addComponent<TransformComponent>(800, 0);
	player2.addComponent<SpriteComponent>("assets/player2.png");
	player2.addComponent<KeyboardController2>();
	player2.addComponent<ColliderComponent>("player2");


	wall.addComponent<TransformComponent>(288.0f, 448.0f, 32, 32, 1);
	wall.addComponent<SpriteComponent>("assets/grass.png");
	wall.addComponent<ColliderComponent>("wall");

	wall.addComponent<TransformComponent>(288.0f, 416.0f, 32, 32, 1);
	wall.addComponent<SpriteComponent>("assets/grass.png");
	wall.addComponent<ColliderComponent>("wall");

	wall.addComponent<TransformComponent>(288.0f, 384.0f, 32, 32, 1);
	wall.addComponent<SpriteComponent>("assets/grass.png");
	wall.addComponent<ColliderComponent>("wall");

	wall.addComponent<TransformComponent>(160.0f, 480.0f, 32, 32, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");

	wall.addComponent<TransformComponent>(128.0f, 480.0f, 32, 32, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");

	wall.addComponent<TransformComponent>(192.0f, 480.0f, 32, 32, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
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

	if (Collision::isColliding(player1.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider)) {
		player1.getComponent<TransformComponent>().scale = 0;
		cout << "Wall Hit!" << endl;
	}
	if (Collision::isColliding(player2.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider)) {
		player2.getComponent<TransformComponent>().scale = 0;
		cout << "Wall Hit!" << endl;
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

