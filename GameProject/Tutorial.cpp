#include "Tutorial.h"
#include "Text.h"
#include <iostream>
Tutorial::Tutorial() {

}
Tutorial::~Tutorial() {
	Free();
}



int Tutorial::loadTutorial(SDL_Renderer* renderer) {

	SDL_Event mevent;

	while (true) {
		LoadImg("assets/tutorial.png", renderer);
		SDL_Rect renderQuad = { xpos,ypos,1760,960};
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);

		while (SDL_PollEvent (& mevent))
		{

			switch (mevent.type) {
			case SDL_QUIT:
				return QUIT;


			case SDL_KEYDOWN:
				if (mevent.key.keysym.sym == SDLK_ESCAPE)
				{
					return QUIT;
				}
				else if (mevent.key.keysym.sym == SDLK_SPACE)
                {
                    return SPACE;
                }
			default:
				break;
			}
		}
		SDL_RenderPresent(renderer);
	}
		return QUIT;
}


