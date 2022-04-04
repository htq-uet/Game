#include "Menu.h"
#include "Text.h"
#include <iostream>
Menu::Menu() {

}
Menu::~Menu() {
	Free();
}bool Menu::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

Text text_menu[2];
bool selected[2] = { 0,0 };

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
	
	

	BuildItemMenu(0, "Play Game", 700, 600, Text::PINK, renderer, font);

	int xm = 0;
	int ym = 0;

	SDL_Event mevent;
	
	while (true) {
		LoadImg("assets/background1.png", renderer);
		SDL_Rect renderQuad = { xpos,ypos,1760,960};
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
		text_menu[0].RenderText(renderer, 700,600);

		while (SDL_PollEvent (& mevent))
		{
			
			switch (mevent.type) {
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEMOTION:
			{
				xm = mevent.motion.x;
				ym = mevent.motion.y;
				for (int i = 0;i < 1;++i) {
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect())) {
						
						if (selected[i] == false)
						{
							selected[i] = true;
							ChangeColor(i, Text::BLACK, renderer, font);
						}
					}
					else {
						if (selected[i] == true)
						{
							selected[i] = false;
							ChangeColor(i, Text::PINK, renderer, font);
						}
					}
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = mevent.button.x;
				ym = mevent.button.y;

				for (int i = 0; i < 1; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
					{
						return i;
					}
				}
			}
			case SDL_KEYDOWN:
				if (mevent.key.keysym.sym == SDLK_ESCAPE)
				{
					return 1;
				}
			default:
				break;
			}
		}
		SDL_RenderPresent(renderer);
	}
		return 1;
}