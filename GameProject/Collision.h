#pragma once
#include "SDL.h"
class Collision {
public:
	static bool isColliding(const SDL_Rect& recA, const SDL_Rect& recB);
};