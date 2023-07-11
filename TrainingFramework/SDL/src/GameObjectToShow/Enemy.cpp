#include "Enemy.h"
#include "ResourceManagers.h"

Enemy::Enemy(const char* texture, int sizeW, int sizeH,int animFrame) {
	auto tex = ResourceManagers::GetInstance()->GetTexture(texture);

	CurrentAnimation = std::make_shared<SpriteAnimation>(tex, 1, animFrame, 1, 0.2f);
	CurrentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	CurrentAnimation->SetSize(sizeW, sizeH);
	CurrentAnimation->Set2DPosition(240, 300);

	m_position = CurrentAnimation->GetPosition();

}

void Enemy::Init() {
}

void Enemy::Update(float deltatime) {
	Object::Update(deltatime);
	Move(deltatime);
}

void Enemy::Move(float deltaTime) {
	m_position = CurrentAnimation->GetPosition();
	CurrentAnimation->Set2DPosition(m_position.x + MoveDirection.x, m_position.y + MoveDirection.y);
}


void Enemy::Draw(SDL_Renderer* renderer) {
	CurrentAnimation->Draw(renderer);
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