#include "EnemyPool.h"

EnemyPool::EnemyPool() {
}

EnemyPool::~EnemyPool()
{
	enemies.clear();
}

void EnemyPool::Init() {
	Enemy::CreatePath();
	powerUp = std::make_shared<PowerUpPool>();
	powerUp->Init();

	for (int i = 0;i < 10;i++) {
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(rand()%9);
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
			enemy->ChangeHealth(Health);
			enemy->ChangeEnemy(rand() % 2);
			enemy->Reset();
			return;
		}
	}

	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(path);
	enemy->Init();
	enemy->onEnemyDeath = [=]() mutable {
		float result = RandomFloat(0.0f, 100.0f);
		if (result < 10.0f) {
			powerUp->TakeRandomPowerUp(Vector2(enemy->GetPosition().x, enemy->GetPosition().y));
		}
	};
	enemies.push_back(enemy);
	enemy->IsActive = true;
	enemy->ChangeHealth(Health);
	enemy->ChangeEnemy(rand() % 2);
	enemy->Reset();
}


		