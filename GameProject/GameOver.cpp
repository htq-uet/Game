#include "GameOver.h"
#include "Text.h"
#include <iostream>
GameOver::GameOver() {

}
GameOver::~GameOver() {
	Free();
}

bool GameOver::CheckFocusWithRectGO(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

Text text_go[100];
bool selectedGO[1]={0};

void BuildItemGO(const int& index, const string& text, const int& x, const int& y, const int& color, SDL_Renderer* renderer, TTF_Font* font) {
	text_go[index].SetColor(color);
	text_go[index].SetText(text);
	text_go[index].LoadFont(font, renderer);
	text_go[index].SetRect(x, y);
}

void ChangeColorGO(const int& index, const int& color, SDL_Renderer* renderer, TTF_Font* font) {
	text_go[index].SetColor(color);
	text_go[index].LoadFont(font, renderer);
}

void GameOver::loadGameOver(SDL_Renderer* renderer, TTF_Font* font) {



	BuildItemGO(0, "- Play Again -", 750, 600, Text::PINK, renderer, font);

	int xG = 0;
	int yG = 0;

	SDL_Event GOevent;

    while(true){
		LoadImg("assets/gameover.png", renderer);
		SDL_Rect renderQuad = { xp,yp,1760,960};
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
		text_go[0].RenderText(renderer, 750,600);
		while (SDL_PollEvent (& GOevent))
		{

			switch (GOevent.type) {
			case SDL_QUIT:
				quit_ = true;
			case SDL_MOUSEMOTION:
			{
				xG = GOevent.motion.x;
				yG = GOevent.motion.y;
				for (int i = 0;i < 1;++i) {
					if (CheckFocusWithRectGO(xG, yG, text_go[i].GetRect())) {

						if (selectedGO[i] == false)
						{
							selectedGO[i] = true;
							ChangeColorGO(i, Text::BLACK, renderer, font);
						}
					}
					else {
						if (selectedGO[i] == true)
						{
							selectedGO[i] = false;
							ChangeColorGO(i, Text::PINK, renderer, font);
						}
					}
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				xG = GOevent.button.x;
				yG = GOevent.button.y;

				if (CheckFocusWithRectGO(xG, yG, text_go[0].GetRect()))
					{
						check = 0;
					}
			}
			case SDL_KEYDOWN:
				if (GOevent.key.keysym.sym == SDLK_ESCAPE)
				{
					quit_ = true;
				}
			default:
				break;
			}
		}
		SDL_RenderPresent(renderer);
    }
		quit_ = true;
}


