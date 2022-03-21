#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"

class TileComponent : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Rect tileRect;
	int tileID;
	const char* path;
	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 1:
			path = "assets/block1.png";
			break;
		case 0:
			path = "assets/water.png";
			break;
		case 2:
			path = "assets/block2.png";
			break;
		case 3:
			path = "assets/block3.png";
			break;
		case 4:
			path = "assets/poison.png";
			break;
		default:
			break;
		}
	}
	void init() override {
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();
		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();

	}
};