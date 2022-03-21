#include "ECS.h"

void Entity::addGr(Group mGroup)
{
	grBitset[mGroup] = true;
	manager.addtoGr(this, mGroup);
}