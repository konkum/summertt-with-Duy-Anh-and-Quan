#pragma once
#include <vector>
#include "Enemy.h"

class EnemyPool
{
private:
	std::vector<Enemy*> enemies;
	Bullet* SpawnBullet();
public:
	EnemyPool();
	~EnemyPool();
	void Update(float deltaTime);
	void Init();
	void Draw(SDL_Renderer* renderer);
	void Shoot(Enemy* enemy, float deltaTime);
	void SetSpawn(Vector2 location, Vector2 moveDirection);
};

