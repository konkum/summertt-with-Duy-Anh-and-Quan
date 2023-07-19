#include "PowerUpPool.h"


PowerUpPool::PowerUpPool()
{
}

PowerUpPool::~PowerUpPool()
{
	for (int i = 0;i < powerups.size();i++) {
		delete powerups[i];
		powerups[i] = NULL;
	}
}

void PowerUpPool::Init()
{
	for (int i = 0;i < 10;i++) {
		PowerUp* pu = new PowerUp();
		pu->Init();
		powerups.push_back(pu);
	}
}

void PowerUpPool::Update(float deltaTime)
{
	for (auto power : powerups) {
		power->Update(deltaTime);
	}
}

void PowerUpPool::TakeRandomPowerUp(Vector2 position) {
	for (auto power : powerups) {
		if (!power->IsActive) {
			power->SetSpawnPoint(position, rand() % 2);
			power->IsActive = true;
			break;
		}
	}
}

void PowerUpPool::Draw(SDL_Renderer* renderer)
{
	for (auto power : powerups) {
		power->Draw(renderer);
	}
}
