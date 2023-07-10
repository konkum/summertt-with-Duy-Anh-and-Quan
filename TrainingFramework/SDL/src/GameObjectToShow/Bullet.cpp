#include "Bullet.h"
#include "ResourceManagers.h"

Bullet::Bullet() {
	auto texture = ResourceManagers::GetInstance()->GetTexture("Torpedo.png");
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 3, 1, 0.2f);
	CurrentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	CurrentAnimation->SetSize(33, 66);
}

Bullet::~Bullet() {

}

void Bullet::Update(float deltatime) {
	Object::Update(deltatime);
	Move(deltatime);
}

void Bullet::Move(float deltaTime) {
	m_position = CurrentAnimation->GetPosition();
	CurrentAnimation->Set2DPosition(m_position.x, m_position.y - deltaTime * m_Velocity);
	CurrentAnimation->Update(deltaTime);
}

void Bullet::Init() {
}

void Bullet::Draw(SDL_Renderer* renderer) {
	CurrentAnimation->Draw(renderer);
}

void Bullet::SetSpawnPoint(Vector2 spawnPoint) {
	CurrentAnimation->Set2DPosition(spawnPoint.x, spawnPoint.y);
}