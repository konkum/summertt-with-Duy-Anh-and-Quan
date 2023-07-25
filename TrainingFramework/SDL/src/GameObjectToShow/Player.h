#include "HealthComponent.h"
#include "Bullet.h"
#include "Option.h"
#include "GameObject/Sfx.h"
#include <vector>

class Player : public Object, virtual public Health
{
private:
	std::shared_ptr<SpriteAnimation> shield_animation;
	Vector2 bulletSpawnPoint;
	float shootTime = 0.3f;
	float currentShieldTimer = 0.0f;
	float currentShootTimer = 0.0f;
	int& skinID = Option::skinID;
	std::string text = "";
	static inline Player* m_instance;
	int bulletCount = 0;
	std::shared_ptr<Sfx>		m_bulletSound;
	std::shared_ptr<Sfx>		m_deadSound;
	Vector2 spawnPosition;
public:
	static Player* GetPlayer() {
		return m_instance;
	}
	bool IsShield = false;
	bool IsDoubleShooting = false;
	int Point = 0;
	int m_KeyPress = 0;
	std::vector<std::shared_ptr<SpriteAnimation>> list_animation;
	std::vector<std::shared_ptr<Bullet>> bullets;
	Player();
	~Player();
	void HandleEvent(SDL_Event& e);
	void HandleKeyEvent(SDL_Event& e);
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltatime) override;
	void Move(float deltaTime) override;
	void Heal();
	void Shoot();
	void TakeDamage(float damage) override;
	void Die() override;
	float HealthCheck();
};

