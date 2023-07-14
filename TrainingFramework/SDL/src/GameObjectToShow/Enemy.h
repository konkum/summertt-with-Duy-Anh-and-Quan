#include "Object.h"
#include "ObjectPool.h"
#include "HealthComponent.h"
#include "Bullet.h"
#include <vector>

class Enemy : public Object, virtual public Health
{
private:
	//Testing

	static std::vector<std::vector<Vector2>> sPaths;

	enum STATES
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
	float currentTime = 0.0f;
	Vector2 bulletSpawnPoint;
	float shootTime = 1.0f;
	float currentShootTimer = 0.0f;
public:
	//Testing
	static void CreatePath();

	Enemy(int path);
	virtual void HandleFlyInState(float deltaTime);
	virtual void HandleFormationState();
	virtual void HandleDiveState();
	virtual void HandleDeadState();

	void HandleStates(float deltaTime);

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
};


