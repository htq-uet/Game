#pragma once
#include "game.h"
#include "ECS.h"
#include "Components.h"
class KeyboardController2 : public Component
{
public:
	SpriteComponent* sprite;
	TransformComponent* transform;
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void update() override {
		if (Game::e.type == SDL_KEYDOWN) {
			switch (Game::e.key.keysym.sym)
			{
			case SDLK_UP:
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;

			case SDLK_LEFT:
				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->Flip = SDL_FLIP_NONE;
				break;
			case SDLK_DOWN:
				transform->velocity.y = +1;
				sprite->play("Walk");
				break;
			case SDLK_RIGHT:
				transform->velocity.x = +1;
				sprite->play("Walk");
				sprite->Flip = SDL_FLIP_HORIZONTAL;
				break;
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
				sprite->play("Idle");
				break;
			case SDLK_DOWN:
				transform->velocity.y = 0;

				break;
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;
			default:
				break;
			}
		}

	}
};

