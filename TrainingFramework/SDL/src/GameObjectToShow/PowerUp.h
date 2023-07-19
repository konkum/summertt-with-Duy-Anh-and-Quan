#pragma once
#include "Player.h"

class PowerUp : public virtual Object
{
private:
public:
	virtual void ChangePlayerAttribute(Player* player) = 0;
	PowerUp(const char* textureName);
	~PowerUp();
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltatime) override;
	void Move(float deltaTime) override;
	void SetSpawnPoint(Vector2 spawnPoint);
};

