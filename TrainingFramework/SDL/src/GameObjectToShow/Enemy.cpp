#include "Enemy.h"
#include "ResourceManagers.h"

Enemy::Enemy(const char* texture, int sizeW, int sizeH,int animFrame) {
	Object::Init();
	auto tex = ResourceManagers::GetInstance()->GetTexture(texture);

	CurrentAnimation = std::make_shared<SpriteAnimation>(tex, 1, animFrame, 1, 0.2f);
	CurrentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	CurrentAnimation->SetSize(sizeW, sizeH);

	m_position = CurrentAnimation->GetPosition();

	for (int i = 0;i < 20;i++) {
		Bullet* bullet = new Bullet("Projectile_Enemy.png", Vector2(30, 30), 3);
		bullet->MoveDirection = -1;
		bullet->Tag = "EnemyBullet";
		bullets.push_back(bullet);
	}
	Tag = "Enemy";
}

void Enemy::Init() {
}


void Enemy::Update(float deltatime) {
	Object::Update(deltatime);
	Move(deltatime);
	currentTime += deltatime;
	if (currentTime > 1.0f) {
		currentTime = 0;
		ShootBullet();
	}
	
}

void Enemy::UpdateBullet(float deltaTime) {
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

void Enemy::Move(float deltaTime) {
	m_position = CurrentAnimation->GetPosition();
	CurrentAnimation->Set2DPosition(m_position.x + MoveDirection.x, m_position.y + MoveDirection.y);
}


void Enemy::Draw(SDL_Renderer* renderer) {
	CurrentAnimation->Draw(renderer);
}

void Enemy::DrawBullet(SDL_Renderer* renderer) {
	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Draw(renderer);
		}
	}
}

void Enemy::TakeDamage(float damage) {
	currentHealth -= damage;

	if (currentHealth <= 0) {
		currentHealth = 0;
		Die();
	}
}

void Enemy::Die() {
	if (IsActive) {
		IsActive = false;
	}
}

void Enemy::ShootBullet() {
	for (auto bullet : bullets) {
		if (!bullet->IsActive) {
			bullet->IsActive = true;
			bullet->SetSpawnPoint(CurrentAnimation->Get2DPosition());
			break;
		}
	}
}