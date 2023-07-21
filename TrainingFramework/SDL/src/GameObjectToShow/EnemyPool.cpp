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

void EnemyPool::Init() {
	Enemy::CreatePath();
	powerUp = new PowerUpPool();
	powerUp->Init();

	for (int i = 0;i < 10;i++) {
		Enemy* enemy = new Enemy(rand()%9);
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

void EnemyPool::SetSpawn(int path) {
	for (auto enemy : enemies) {
		if (!enemy->IsActive) {
			enemy->IsActive = true;
			enemy->ChangePath(path);
			enemy->Reset();
			return;
		}
	}

	Enemy* enemy = new Enemy(path);
	enemy->Init();
	enemy->onEnemyDeath = [=]() mutable {
		float result = RandomFloat(0.0f, 100.0f);
		if (result < 10.0f) {
			powerUp->TakeRandomPowerUp(Vector2(enemy->GetPosition().x, enemy->GetPosition().y));
		}
	};
	enemies.push_back(enemy);
	enemy->IsActive = true;
	enemy->Reset();
}
		