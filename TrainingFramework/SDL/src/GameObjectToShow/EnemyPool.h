#pragma once
#include <vector>
#include "Enemy.h"

class EnemyPool
{
private:
	std::vector<Enemy*> enemies;

	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
public:
	EnemyPool();
	~EnemyPool();
	void Update(float deltaTime);
	void Init();
	void Draw(SDL_Renderer* renderer);
	void SetSpawn(int path);
};

