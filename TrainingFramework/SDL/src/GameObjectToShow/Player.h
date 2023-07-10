
#include "Object.h"
#include "ObjectPool.h"
#include "HealthComponent.h"
#include "Bullet.h"
#include <list>

class Player : public Object, virtual public Health
{
private:
	Vector2 bulletSpawnPoint;
	float shootTime = 1.0f;
	float currentShootTimer = 0.0f;
public:
	int m_KeyPress = 0;
	Player();
	~Player();
	void HandleEvent(SDL_Event& e);
	void HandleKeyEvent(SDL_Event& e);
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltatime) override;
	void Move(float deltaTime) override;
	void Shoot();
	void TakeDamage(float damage) override;
	void Die() override;
};

