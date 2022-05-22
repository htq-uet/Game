#include "Menu.h"
#include "Text.h"
#include <iostream>
Menu::Menu() {

}
Menu::~Menu() {
	Free();
}

bool Menu::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

Text text_menu[100];
bool selected[1]={0};

void BuildItemMenu(const int& index, const string& text, const int& x, const int& y, const int& color, SDL_Renderer* renderer, TTF_Font* font) {
	text_menu[index].SetColor(color);
	text_menu[index].SetText(text);
	text_menu[index].LoadFont(font, renderer);
	text_menu[index].SetRect(x, y);
}

void ChangeColor(const int& index, const int& color, SDL_Renderer* renderer, TTF_Font* font) {
	text_menu[index].SetColor(color);
	text_menu[index].LoadFont(font, renderer);
}

int Menu::loadMenu(SDL_Renderer* renderer, TTF_Font* font) {

	BuildItemMenu(0, "- Click here to play game -", 597, 720, Text::BLACK, renderer, font);
    BuildItemMenu(1, "- Continue- ", 730, 790, Text::BLACK, renderer, font);
	int xm = 0;
	int ym = 0;

	SDL_Event mevent;

	while (true) {
		LoadImg("assets/menu.png", renderer);
		SDL_Rect renderQuad = { xpos,ypos,1760,960};
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
		text_menu[0].RenderText(renderer, 597, 720);
		text_menu[1].RenderText(renderer, 730, 790);
		while (SDL_PollEvent (& mevent))
		{

			switch (mevent.type) {
			case SDL_QUIT:
				return 2;
			case SDL_MOUSEMOTION:
			{
				xm = mevent.motion.x;
				ym = mevent.motion.y;
				for (int i = 0;i < 2;++i) {
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect())) {

						if (selected[i] == false)
						{
							selected[i] = true;
							ChangeColor(i, Text::PINK, renderer, font);
						}
					}
					else {
						if (selected[i] == true)
						{
							selected[i] = false;
							ChangeColor(i, Text::BLACK, renderer, font);
						}
					}
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = mevent.button.x;
				ym = mevent.button.y;

				if (CheckFocusWithRect(xm, ym, text_menu[0].GetRect()))
					{
						return 0;
					}
                if (CheckFocusWithRect(xm, ym, text_menu[1].GetRect()))
					{
						return 3;
					}
			}
			case SDL_KEYDOWN:
				if (mevent.key.keysym.sym == SDLK_ESCAPE)
				{
					return QUIT;
				}
			default:
				break;
			}
		}
		SDL_RenderPresent(renderer);
	}
		return QUIT;
}

int Menu::loadTutorial(SDL_Renderer* renderer) {

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

int Menu::loadWinScreen(SDL_Renderer* renderer)
{
    SDL_Event mevent;

	while (true) {
		LoadImg("assets/win.png", renderer);
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
			default:
				break;
			}
		}
		SDL_RenderPresent(renderer);
	}
		return QUIT;
}
