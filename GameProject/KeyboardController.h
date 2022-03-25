#pragma once
#include "game.h"
#include "ECS.h"
#include "Components.h"
class KeyboardController: public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

	}
	void update() override {
		if (Game::e.type == SDL_KEYDOWN) {
			switch (Game::e.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y =-1;
				sprite->play("Walk");
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->Flip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = +1;
				sprite->play("Walk");
				break;
			case SDLK_d:
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
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;

			default:
				break;
			}
		}
		
	}
};

