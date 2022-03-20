#include "Collision.h"
#include "ColliderComponent.h"
bool Collision::isColliding(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (recA.x + recA.w >= recB.x && recB.x + recB.w >= recA.x && recA.y + recA.h >= recB.y && recB.y && recB.y + recB.h >= recA.y) {
		return true;
	}
	else return false;
}
bool Collision:: isColliding(const ColliderComponent& colA, const ColliderComponent& colB) {
	if (isColliding(colA.collider, colB.collider)) {
		cout << colA.tag << " hit: " << colB.tag << endl;
		return true;
	}
	else return false;
}
