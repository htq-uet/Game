#pragma once
#include "game.h"
#include "ECS.h"
#include "Components.h"
class KeyboardController2 : public Component
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
			case SDLK_UP:
				transform->velocity.y = -1;
				break;
			case SDLK_LEFT:
				transform->velocity.x = -1;
				break;
			case SDLK_DOWN:
				transform->velocity.y = +1;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = +1;
			default:
				break;
			}
		}
		if (Game::e.type == SDL_KEYUP) {
			switch (Game::e.key.keysym.sym)
			{
			case SDLK_UP:
				transform->velocity.y = 0;
				break;
			case SDLK_LEFT:
				transform->velocity.x = 0;
				break;
			case SDLK_DOWN:
				transform->velocity.y = 0;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 0;
			default:
				break;
			}
		}

	}
};

