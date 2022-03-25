
#include "game.h"
#include "TextureManage.h"
#include "Map.h"
#include "BackGround.h" 
#include "Components.h"
#include "Collision.h"
#include "Vector2D.h"
#include <sstream>
Map* map1;
Manager manager;
BackGround* backgr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::e; 

vector<ColliderComponent*> Game::colliders;

auto& player1(manager.addEntity());
auto& player2(manager.addEntity());
const char* mapfile = "assets/block.png";
Game::Game() {

}
Game::~Game() {

}
void Game::init(const char* title, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems Initialised!..." << endl;
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window) {
			cout << "Window created!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}
		
		isRunning = true;
	}
	
	backgr = new BackGround();
	map1 = new Map();
	Map::LoadMap("assets/map1.map", 55, 30);
	backgr = new BackGround();
	player1.addComponent<TransformComponent>(100,900);
	player1.addComponent<SpriteComponent>("assets/pink.png",true);
	player1.addComponent<KeyboardController>();
	player1.addComponent<ColliderComponent>("player1");
	player1.addGr(grPlayers);

	player2.addComponent<TransformComponent>(800, 100);
	player2.addComponent<SpriteComponent>("assets/dark.png",true);
	player2.addComponent<KeyboardController2>();
	player2.addComponent<ColliderComponent>("player2");
	player2.addGr(grPlayers);


}
auto& tiles(manager.getGroup(Game::grMap));
auto& players(manager.getGroup(Game::grPlayers));
auto& cols(manager.getGroup(Game::grColliders));
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

	SDL_Rect playerCol = player1.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player1.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		if (Collision::isColliding(player1.getComponent<ColliderComponent>(), *cc)) {
			player1.getComponent<TransformComponent>().position=playerPos;
		}

	}
}

void Game::render() {

	SDL_RenderClear(renderer);
	backgr->DrawBackGround();
	for (auto& c : cols) {
		c->draw();
	}
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	
	SDL_RenderPresent(renderer);

}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Closed!";
}
void Game::addTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x,y,32,32,id);
	tile.addComponent<ColliderComponent>("tile");
	tile.addGr(Game::grMap);
}