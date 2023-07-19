#include "PowerUp.h"

PowerUp::PowerUp(const char* textureName)
{
	Object::Init();
	auto texture = ResourceManagers::GetInstance()->GetTexture(textureName);
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 4, 1, 0.2f);
	CurrentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	CurrentAnimation->SetSize(50,50);
}

PowerUp::~PowerUp()
{
}

void PowerUp::Init()
{
}

void PowerUp::Draw(SDL_Renderer* renderer)
{
	if (!IsActive) {
		return;
	}

	CurrentAnimation->Draw(renderer);
}

void PowerUp::Update(float deltatime)
{
	if (!IsActive) {
		return;
	}
}

void PowerUp::Move(float deltaTime)
{
}

void PowerUp::SetSpawnPoint(Vector2 spawnPoint)
{
}
