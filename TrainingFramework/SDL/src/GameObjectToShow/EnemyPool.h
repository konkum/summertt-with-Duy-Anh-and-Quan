#pragma once
#include <vector>
#include "Enemy.h"

class EnemyPool
{
private:
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	Bullet* SpawnBullet();
public:
	EnemyPool();
	~EnemyPool();
	void Update(float deltaTime);
	void Init();
	void Draw(SDL_Renderer* renderer);
	void Shoot(Enemy* enemy, float deltaTime);
	void SetSpawn(Vector2 location, int numberOfSpawn, Vector2 moveDirection,float spawnTime,float deltaTime=0.01f);
};

