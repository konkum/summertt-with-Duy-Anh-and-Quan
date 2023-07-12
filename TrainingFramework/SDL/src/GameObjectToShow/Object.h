#pragma once
#include "SpriteAnimation.h"
#include <vector>

class Object : virtual public BaseObject {
protected:
	float m_Velocity = 100.0f;
	
public:
	static inline std::vector<Object*> object;
	std::shared_ptr<SpriteAnimation> CurrentAnimation;
	Vector2 MoveDirection;
	SDL_Rect Collider;
	bool IsActive = false;
	const char* Tag;
	void Init() override {
		object.push_back(this);
	}
	virtual void Move(float deltaTime) = 0;
	void Update(float deltatime) override {
		Collider.x = static_cast<int>(m_position.x);
		Collider.y = static_cast<int>(m_position.y);
		Collider.w = CurrentAnimation->GetWidth();
		Collider.h = CurrentAnimation->GetHeight();
	}

	void SetVelocity(float velocity) {
		m_Velocity = velocity;
	}
};
