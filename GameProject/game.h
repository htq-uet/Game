#ifndef game_h
#define game_h
#include "SDL.h"
#include <iostream>
#include <SDL_image.h>
#include <vector>
using namespace std;
class ColliderComponent;

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() {
		return isRunning;
	}

	static void addTile(int srcX, int srcY, int xpos, int ypos);
	
	static SDL_Renderer* renderer;
	static SDL_Event e;
	enum grLabels :size_t {
		grMap,
		grPlayers,
		grColliders
	};
	static std::vector<ColliderComponent*> colliders;
	static void addTile(int id, int x, int y);
private:
	bool isRunning = false;
	SDL_Window* window;
	
};
#endif // !game_h
