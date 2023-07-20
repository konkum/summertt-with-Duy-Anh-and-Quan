#pragma once
#include "PowerUp.h"

class PowerUpPool
{
private:
	std::vector<PowerUp*> powerups;
public:
	PowerUpPool();
	~PowerUpPool();
	void Init();
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer);
	void TakeRandomPowerUp(Vector2 position);
};

