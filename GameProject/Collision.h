#pragma once
#include "SDL.h"

class ColliderComponent;
class Collision {
public:
	static bool isColliding(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool isColliding(const ColliderComponent& colA, const ColliderComponent& colB);
};