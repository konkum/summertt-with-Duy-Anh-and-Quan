#include "EnemyScenario.h"

class EnemyScenario1: public virtual EnemyScenario
{
private:
	int randomNumber = rand() % 9;
public:
	using EnemyScenario::EnemyScenario;

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

