#pragma once
#include "Object.h"
#include "Singleton.h"
class CollisionDetection: public CSingleton<CollisionDetection>
{
public:
	std::vector<Object*> Objects;
	bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	bool AABB(const Object& colA, const Object& colB);
};

