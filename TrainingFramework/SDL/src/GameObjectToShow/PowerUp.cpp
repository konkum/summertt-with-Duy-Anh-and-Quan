#include "PowerUp.h"
#include "CollisionDetection.h"

PowerUp::PowerUp()
{
	Object::Init();
	auto texture = ResourceManagers::GetInstance()->GetTexture("Item_Booster.png");
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 3, 1, 0.2f);
	CurrentAnimation->SetSize(50,50);

	Tag = "PowerUp";
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

	Object::Update(deltatime);
	m_position = CurrentAnimation->GetPosition();
	CurrentAnimation->Set2DPosition(m_position.x, m_position.y + m_Velocity * deltatime);
	CurrentAnimation->Update(deltatime);

	if (m_position.y > SCREEN_HEIDHT) {
		IsActive = false;
	}
	
	for (auto obj : object) {
		if (obj->IsActive && obj->Tag == "Player") {
			if (CollisionDetection::AABB(this->Collider, obj->Collider)) {
				IsActive = false;
				ChangePlayerAttribute();
			}
		}
	}
}

void PowerUp::Move(float deltaTime)
{
}

void PowerUp::SetSpawnPoint(Vector2 spawnPoint,int power)
{
	CurrentAnimation->Set2DPosition(spawnPoint);
	m_position = CurrentAnimation->GetPosition();
	if (power < 2) {
		Power = static_cast<POWERUP>(power);
	}

	std::shared_ptr<TextureManager> texture;

	switch (Power)
	{
	case POWERUP::Shield:
		texture = ResourceManagers::GetInstance()->GetTexture("Item_Bullet.png");
		CurrentAnimation->SetTexture(texture);
		break;
	case POWERUP::Damage:
		texture = ResourceManagers::GetInstance()->GetTexture("Item_Booster.png");
		CurrentAnimation->SetTexture(texture);
		break;
	default:
		break;
	}
	
}

void PowerUp::ChangePlayerAttribute()
{
	switch (Power)
	{
	case POWERUP::Shield:
		Player::GetPlayer()->IsShield = true;
		break;
	case POWERUP::Damage:
		Player::GetPlayer()->IsDoubleShooting = true;
		break;
	default:
		break;
	}
}
