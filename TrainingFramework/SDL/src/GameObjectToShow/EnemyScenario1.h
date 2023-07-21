#include "EnemyScenario.h"

class EnemyScenario1: public EnemyScenario
{
private:
	int randomNumber = rand() % 9;
public:
	EnemyScenario1(EnemyPool* enemy, float timeBetweenSpawn = 1.0f, int TotalOfSpawn = 5) : EnemyScenario(enemy, timeBetweenSpawn, TotalOfSpawn) {

	}

	 void Update(float deltaTime) {
		mCurrentTime += deltaTime;
		if (mSpawnNumber < mTotalOfSpawn) {
			if (mCurrentTime > mTimeBetweenSpawn) {
				mSpawnNumber++;
				mEnemyPool->SetSpawn(randomNumber);
				mCurrentTime = 0;
			}
			return;
		}

		OnSpawnComplete();
	}
};

