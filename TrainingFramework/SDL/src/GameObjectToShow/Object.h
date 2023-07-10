#pragma once
#include "SpriteAnimation.h"

class Object : virtual public BaseObject {
protected:
	float m_Velocity = 100.0f;
	
public:
	std::shared_ptr<SpriteAnimation> CurrentAnimation;
	Vector2 MoveDirection;
	SDL_Rect Collider;
	virtual void Move(float deltaTime) = 0;
	void Update(float deltatime) override {
		Collider.x = static_cast<int>(m_position.x);
		Collider.y = static_cast<int>(m_position.y);
		Collider.w = CurrentAnimation->GetWidth();
		Collider.h = CurrentAnimation->GetHeight();
	}
};
