#include "EnemyPool.h"

class EnemyScenario {
protected:
	int mSpawnNumber = 0;
	int mTotalOfSpawn = 5;
	float mCurrentTime = 0.0f;
	float mTimeBetweenSpawn = 1.0f;
	EnemyPool* mEnemyPool;
public:
	std::function<void(void)> OnSpawnComplete;

	EnemyScenario(EnemyPool* enemy, float timeBetweenSpawn = 1.0f, int TotalOfSpawn = 5) {
		mEnemyPool = enemy;
		mTotalOfSpawn = TotalOfSpawn;
		mTimeBetweenSpawn = timeBetweenSpawn;
	}

	virtual void Update(float deltaTime) = 0;
};
