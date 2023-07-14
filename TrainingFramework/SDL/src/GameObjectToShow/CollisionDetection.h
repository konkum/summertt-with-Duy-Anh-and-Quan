#pragma once
#include "Object.h"
class CollisionDetection
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const Object& colA, const Object& colB);
};

