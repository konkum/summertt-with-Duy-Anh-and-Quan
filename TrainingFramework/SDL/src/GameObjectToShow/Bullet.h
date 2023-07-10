#include "SpriteAnimation.h"

class Bullet:public BaseObject
{
private:
	SpriteAnimation* currentAnimation;
	float velocity = 100.0f;
public:
	bool IsActive = false;
	Bullet();
	~Bullet();
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	virtual void Update(float deltatime) override;
	void SetSpawnPoint(Vector2 spawnPoint);
};

