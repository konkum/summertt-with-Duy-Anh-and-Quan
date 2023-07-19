#include "PowerUp.h"
#include "CollisionDetection.h"

PowerUp::PowerUp()
{
	Object::Init();
	auto texture = ResourceManagers::GetInstance()->GetTexture("textureName");
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

	m_position = CurrentAnimation->GetPosition();
	CurrentAnimation->Set2DPosition(m_position.x, m_position.y + m_Velocity * deltatime);
	CurrentAnimation->Update(deltatime);

	if (m_position.y > SCREEN_HEIDHT) {
		IsActive = false;
	}
	
	for (auto obj : object) {
		if (CollisionDetection::AABB(obj->Collider, this->Collider)) {
			if (obj->IsActive && obj->Tag=="Player") {
				IsActive = false;
				ChangePlayerAttribute(&(Player&)obj);
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
	if (power < 2) {
		Power = static_cast<POWERUP>(power);
	}
	else {
		Power = POWERUP::Shield;
	}
	std::shared_ptr<TextureManager> texture;

	switch (Power)
	{
	case POWERUP::Shield:
		texture = ResourceManagers::GetInstance()->GetTexture("Shield.png");
		CurrentAnimation->SetTexture(texture);
		break;
	case POWERUP::Damage:
		texture = ResourceManagers::GetInstance()->GetTexture("Damage.png");
		CurrentAnimation->SetTexture(texture);
		break;
	default:
		break;
	}
	
}

void PowerUp::ChangePlayerAttribute(Player* player)
{
	switch (Power)
	{
	case POWERUP::Shield:
		player->IsShield = true;
		break;
	case POWERUP::Damage:
		break;
	default:
		break;
	}
}
