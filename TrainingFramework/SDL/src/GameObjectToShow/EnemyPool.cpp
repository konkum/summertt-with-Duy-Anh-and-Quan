#include "EnemyPool.h"
#include "PowerUpPool.h";

PowerUpPool* powerUp;

EnemyPool::EnemyPool() {
}

EnemyPool::~EnemyPool()
{
	delete powerUp;
	powerUp = NULL;

	for (int i = 0;i < enemies.size();i++) {
		delete enemies[i];
		enemies[i] = NULL;
	}
}

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void EnemyPool::Init() {
	Enemy::CreatePath();
	powerUp = new PowerUpPool();
	powerUp->Init();

	for (int i = 0;i < 10;i++) {
		//Enemy* enemy = new Enemy("Enemies_AG.png", 30, 30, 6); 
		Enemy* enemy = new Enemy(rand()%9);
		/*if (i < 9) {
			enemy = new Enemy(i);
		}
		else {
			enemy = new Enemy(1);
		}*/
		enemy->Init();
		enemy->onEnemyDeath = [=]() mutable {
			float result = RandomFloat(0.0f, 100.0f);
			if (result < 10.0f) {
				powerUp->TakeRandomPowerUp(Vector2(enemy->GetPosition().x, enemy->GetPosition().y));
			}
		};
		enemies.push_back(enemy);
	}
}

void EnemyPool::Update(float deltaTime) {
	powerUp->Update(deltaTime);
	for (auto enemy : enemies) {
		enemy->Update(deltaTime);

		enemy->UpdateBullet(deltaTime);
	}
}

void EnemyPool::Draw(SDL_Renderer* renderer) {
	powerUp->Draw(renderer);
	for (auto enemy : enemies) {
		enemy->Draw(renderer);
		enemy->DrawBullet(renderer);
	}
}

void EnemyPool::SetSpawn(Vector2 startPosition, Vector2 moveDirection) {
	for (auto enemy : enemies) {
		if (!enemy->IsActive) {
			enemy->IsActive = true;
			enemy->Reset();
			//enemy->CurrentAnimation->Set2DPosition(startPosition.x, startPosition.y);
			//enemy->MoveDirection = moveDirection;
			break;
		}
	}
}
		