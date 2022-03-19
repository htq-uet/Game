#ifndef game_h
#define game_h
#include "SDL.h"
#include <iostream>
#include <SDL_image.h>

using namespace std;
class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() {
		return isRunning;
	}
	static SDL_Renderer* renderer;
	static SDL_Event e;
private:
	bool isRunning;
	SDL_Window* window;
	
};
#endif // !game_h
