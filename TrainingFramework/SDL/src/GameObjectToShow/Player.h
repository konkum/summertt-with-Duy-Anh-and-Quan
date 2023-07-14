
#include "Object.h"
#include "ObjectPool.h"
#include "HealthComponent.h"
#include "Bullet.h"
#include "GSOption.h"
#include <vector>

class Player : public Object, virtual public Health
{
private:
	bool isDead = false;
	Vector2 bulletSpawnPoint;
	float shootTime = 0.3f;
	float currentShootTimer = 0.0f;
	int& skinID = GSOption::skinID;
	std::string text = "";
public:
	int m_KeyPress = 0;
	std::vector<std::shared_ptr<SpriteAnimation>> list_animation;
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

