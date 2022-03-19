#pragma once
#include "game.h"
#include "ECS.h"
#include "Components.h"
class KeyboardController: public Component
{
public:
	TransformComponent* transform;
	void init() override {
		transform = &entity->getComponent<TransformComponent>();

	}
	void update() override {
		if (Game::e.type == SDL_KEYDOWN) {
			switch (Game::e.key.keysym.sym)
			{
			case SDLK_w: 
				transform->velocity.y = -1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;
			case SDLK_s:
				transform->velocity.y = +1;
				break;
			case SDLK_d:
				transform->velocity.x = +1;
			default:
				break;
			}
		}
		if (Game::e.type == SDL_KEYUP) {
			switch (Game::e.key.keysym.sym)
			{ 
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
			default:
				break;
			}
		}
		
	}
};

