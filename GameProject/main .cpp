
#include "game.h"
Game* gem = nullptr;
int main(int args, char* argv[]) {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	gem = new Game();
	gem->init("Game", 1760, 960, false);
	while (gem->running()) {
		frameStart = SDL_GetTicks();
		gem->handleEvents();
		gem->update();
		gem->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	gem->clean();
	return 0;
}