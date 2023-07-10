#include "Bullet.h"
#include "ResourceManagers.h"

Bullet::Bullet() {
	auto texture = ResourceManagers::GetInstance()->GetTexture("Torpedo.png");
	currentAnimation = new SpriteAnimation(texture, 1, 3, 1, 0.2f);
	currentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	currentAnimation->SetSize(33, 66);
}

Bullet::~Bullet() {

}

void Bullet::Update(float deltatime) {
	m_position = currentAnimation->GetPosition();
	currentAnimation->Set2DPosition(m_position.x, m_position.y - deltatime * velocity);
	currentAnimation->Update(deltatime);
}

void Bullet::Init() {
}

void Bullet::Draw(SDL_Renderer* renderer) {
	currentAnimation->Draw(renderer);
}

void Bullet::SetSpawnPoint(Vector2 spawnPoint) {
	currentAnimation->Set2DPosition(spawnPoint.x, spawnPoint.y);
}