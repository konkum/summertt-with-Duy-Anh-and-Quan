#include "Object.h"
#include "ObjectPool.h"
#include "HealthComponent.h"
#include "Bullet.h"
#include <list>
#include <functional>

class Enemy : public Object, virtual public Health
{
private:
	Vector2 bulletSpawnPoint;
	float shootTime = 1.0f;
	float currentShootTimer = 0.0f;
public:
	bool IsActive = false;
	void TakeDamage(float damage) override;
	void Die() override;
	Enemy(const char* texture, int sizeW,int sizeH,int animFrame);
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	virtual void Update(float deltatime) override;
	void Move(float deltaTime) override;
};


