#include "Object.h"

class Bullet:public Object
{
private:
public:
	bool IsActive = false;
	Bullet();
	~Bullet();
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltatime) override;
	void Move(float deltaTime) override;
	void SetSpawnPoint(Vector2 spawnPoint);
};

