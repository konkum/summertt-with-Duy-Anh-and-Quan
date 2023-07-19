#include "EnemyPool.h"

EnemyPool::EnemyPool() {
}

EnemyPool::~EnemyPool()
{
	for (int i = 0;i < enemies.size();i++) {
		delete enemies[i];
		enemies[i] = NULL;
	}
}

void EnemyPool::Init() {
	Enemy::CreatePath();

	for (int i = 0;i < 10;i++) {
		//Enemy* enemy = new Enemy("Enemies_AG.png", 30, 30, 6);
		Enemy* enemy = new Enemy(0);
		enemy->Init();
		enemies.push_back(enemy);
	}
}

void EnemyPool::Update(float deltaTime) {
	for (auto enemy : enemies) {
		enemy->Update(deltaTime);

		enemy->UpdateBullet(deltaTime);
	}
}

void EnemyPool::Draw(SDL_Renderer* renderer) {
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
		