#include "SpriteAnimation.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include <list>

class Player : public BaseObject
{
private:
	float m_Velocity=100.0f;
	Vector2 bulletSpawnPoint;
	float shootTime = 1.0f;
	float currentShootTimer = 0.0f;
public:
	std::shared_ptr<SpriteAnimation> currentAnimation;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	int m_KeyPress;
	float x_input = 0.0f;
	float y_input = 0.0f;
	Player();
	~Player();
	void HandleEvent(SDL_Event& e);
	void HandleKeyEvent(SDL_Event& e);
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	virtual void Update(float deltatime) override;
	void Move(float deltaTime);
	void Shoot();
};

