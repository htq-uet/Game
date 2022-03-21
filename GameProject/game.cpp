
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
bool Game::isRunning = false;

Manager manager;
auto& player1(manager.addEntity());
auto& player2(manager.addEntity());
auto& wall(manager.addEntity());

enum grLabels :size_t {
	grMap,
	grPlayers,
	grColliders
};
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

	
	
	Map::LoadMap("assets/map1.map", 55, 30);
	backgr = new BackGround();
	player1.addComponent<TransformComponent>(100,100);
	player1.addComponent<SpriteComponent>("assets/pink.png",true);
	player1.addComponent<KeyboardController>();
	player1.addComponent<ColliderComponent>("player1");
	player1.addGr(grPlayers);

	//player2.addComponent<TransformComponent>(800, 100);
	//player2.addComponent<SpriteComponent>("assets/player2.png",4,100);
	//player2.addComponent<KeyboardController2>();
	//player2.addComponent<ColliderComponent>("player2");
	//player2.addGr(grPlayers);


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
auto& tile(manager.getGroup(grMap));
auto& players(manager.getGroup(grPlayers));
void Game::render() {

	SDL_RenderClear(renderer);
	backgr->DrawBackGround();
	
	for (auto& t : tile) {
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
	IMG_Quit();
	cout << "Game Closed!";
}

void Game::addTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGr(grMap);
}
