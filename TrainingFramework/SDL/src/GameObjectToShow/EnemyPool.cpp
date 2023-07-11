#include "EnemyPool.h"

EnemyPool::EnemyPool() {
}

void EnemyPool::Init() {
	for (int i = 0;i < 10;i++) {
		Bullet* bullet = new Bullet("Torpedo.png", Vector2(22, 44), 3);
		bullet->CurrentAnimation->SetRotation(180);
		bullet->MoveDirection = -1;
		bullets.push_back(bullet);
	}

	for (int i = 0;i < 10;i++) {
		Enemy* enemy = new Enemy("Enemies1_1.png", 30, 30, 4);
		enemy->Init();
		enemies.push_back(enemy);
	}
}

Bullet* EnemyPool::SpawnBullet() {
	Bullet* bullet = new Bullet("Torpedo.png", Vector2(22, 44), 3);
	bullet->CurrentAnimation->SetRotation(180);
	bullet->MoveDirection = -1;
	bullets.push_back(bullet);
	return bullet;
}
float currentTime = 0.0f;

void EnemyPool::Shoot(Enemy* enemy,float deltaTime) {
	currentTime += deltaTime;
	if (currentTime > 1.0f) {
		currentTime = 0.0f;
		for (auto bullet : bullets) {
			if (!bullet->IsActive) {
				bullet->IsActive = true;
				bullet->SetSpawnPoint(enemy->CurrentAnimation->Get2DPosition());
				
				goto m_label;
			}
		}

		auto bullet = SpawnBullet();
		bullet->IsActive = true;
		bullet->SetSpawnPoint(enemy->CurrentAnimation->Get2DPosition());
	}

	m_label:

	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Update(deltaTime);

			if (bullet->GetPosition().x < 0 || bullet->GetPosition().x>480) {
				bullet->IsActive = false;
			}
			else if (bullet->GetPosition().y < 0 || bullet->GetPosition().y>800) {
				bullet->IsActive = false;
			}
		}
	}
}



void EnemyPool::Update(float deltaTime) {
	for (auto enemy : enemies) {
		if (enemy->IsActive) {

			enemy->Update(deltaTime);
			Shoot(enemy, deltaTime);

			if (enemy->GetPosition().x < 0 || enemy->GetPosition().x>480) {
				enemy->IsActive = false;
			}
			else if (enemy->GetPosition().y < 0 || enemy->GetPosition().y>800) {
				enemy->IsActive = false;
			}
		}
	}
}

void EnemyPool::Draw(SDL_Renderer* renderer) {
	for (auto enemy : enemies) {
		if (enemy->IsActive) {
			enemy->Draw(renderer);
		}
	}

	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Draw(renderer);
		}
	}
}

void EnemyPool::SetSpawn(Vector2 location, int numberOfSpawn, Vector2 moveDirection, float spawnTime, float deltaTime) {
	if (numberOfSpawn <= 0) {
		printf("The number of spawn is too small");
		return;
	}

	for (auto enemy : enemies) {
		if (!enemy->IsActive) {
			numberOfSpawn--;
			enemy->IsActive = true;
			enemy->CurrentAnimation->Set2DPosition(location.x, location.y);
			enemy->MoveDirection = moveDirection;
			break;
		}
	}
}
		