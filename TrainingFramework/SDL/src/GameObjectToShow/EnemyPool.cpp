#include "EnemyPool.h"

EnemyPool::EnemyPool() {
}

void EnemyPool::Init() {
	for (int i = 0;i < 10;i++) {
		Enemy* enemy = new Enemy("Enemies_AG.png", 30, 30, 6);
		enemy->Init();
		enemies.push_back(enemy);
	}
}

void EnemyPool::Update(float deltaTime) {
	for (auto enemy : enemies) {
		if (enemy->IsActive) {
			enemy->Update(deltaTime);

			if (enemy->GetPosition().x < 0 || enemy->GetPosition().x>480) {
				enemy->IsActive = false;
			}
			else if (enemy->GetPosition().y < 0 || enemy->GetPosition().y>800) {
				enemy->IsActive = false;
			}
		}

		enemy->UpdateBullet(deltaTime);
	}
}

void EnemyPool::Draw(SDL_Renderer* renderer) {
	for (auto enemy : enemies) {
		if (enemy->IsActive) {
			enemy->Draw(renderer);
		}
		enemy->DrawBullet(renderer);
	}
}

void EnemyPool::SetSpawn(Vector2 startPosition, Vector2 moveDirection) {
	for (auto enemy : enemies) {
		if (!enemy->IsActive) {
			enemy->IsActive = true;
			enemy->CurrentAnimation->Set2DPosition(startPosition.x, startPosition.y);
			enemy->MoveDirection = moveDirection;
			break;
		}
	}
}
		