#include "GameObject/Sfx.h"
#include "Object.h"
#include "ObjectPool.h"
#include "HealthComponent.h"
#include "Bullet.h"
#include "Define.h"
#include <vector>

class Enemy : public Object, virtual public Health
{
private:
	//Testing

	static std::vector<std::vector<Vector2>> sPaths;

	enum class STATES
	{
		flyIn,
		formation,
		dive,
		dead
	};

	STATES mCurrentStates;
	int mCurrentPath;
	int mCurrentWayPoint;
	const float EPSILON = 5.0f;


	//Working
	static const inline float CENTER_X = SCREEN_WIDTH / 2;
	static const inline float CENTER_Y = SCREEN_HEIDHT / 2;
	float angle;
	float radius;
	float currentTime = 0.0f;
	Vector2 bulletSpawnPoint;
	float shootTime = 1.0f;
	float currentShootTimer = 0.0f;
	std::shared_ptr<Sfx>		m_bulletSound;
	std::shared_ptr<Sfx>		m_deadSound;
public:
	//Testing
	std::function<void(void)> onEnemyDeath;
	static void CreatePath();

	Enemy(int path);
	virtual void HandleFlyInState(float deltaTime);
	virtual void HandleFormationState(float deltaTime);

	void HandleStates(float deltaTime);
	void Reset();

	//Working

	std::vector<Bullet*> bullets;
	void TakeDamage(float damage) override;
	void Die() override;
	Enemy(const char* texture, int sizeW,int sizeH,int animFrame);
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	virtual void Update(float deltatime) override;
	void Move(float deltaTime) override;
	void ShootBullet();
	void UpdateBullet(float deltaTime);
	void DrawBullet(SDL_Renderer* renderer);
	void ChangePath(int path);
};


