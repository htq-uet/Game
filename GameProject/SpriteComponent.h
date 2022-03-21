#pragma once
#include "TextureManage.h"
#include "Components.h"
#include "SDL.h"
#include "Animation.h"
#include <map>
using namespace std;  
class SpriteComponent :public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animation;

	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}

	SpriteComponent(const char* path,bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0, 2, 100);
		Animation walk = Animation(1, 4, 100);

		animation.emplace("Idle", idle);
		animation.emplace("Walk", walk);

		play("Idle");
		play("Walk");
		setTex(path);
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	void setTex(const char* path) {
		texture = TextureManage::loadTexture(path);
	}
	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}
	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

		}
		srcRect.y = animIndex * transform->height;
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

	}
	void play(const char* animName) {
		frames = animation[animName].frames;
		animIndex = animation[animName].index;
		speed = animation[animName].speed;
	}
	void draw() override {
		TextureManage::Draw(texture, srcRect, destRect,Flip);
	}
};