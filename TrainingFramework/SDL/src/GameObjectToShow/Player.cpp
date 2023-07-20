#include "Player.h"
#include "GameManager/ResourceManagers.h"
#include "Define.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "CollisionDetection.h"

//std::vector<std::shared_ptr<SpriteAnimation>> Player::list_animation;
std::vector<Bullet*> bullets;
Vector2 spawnPosition;

Player::Player() {
	Object::Init();
	text = "Player" + std::to_string(skinID) + "_Idle.png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(text);
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	CurrentAnimation->SetSize(32, 45);
	CurrentAnimation->Set2DPosition(240, 400);

	list_animation.push_back(CurrentAnimation);

	text = "Player" + std::to_string(skinID) + "_Left.png";
	texture = ResourceManagers::GetInstance()->GetTexture(text);
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	CurrentAnimation->SetSize(32, 45);
	CurrentAnimation->Set2DPosition(240, 400);

	list_animation.push_back(CurrentAnimation);

	text = "Player" + std::to_string(skinID) + "_Right.png";
	texture = ResourceManagers::GetInstance()->GetTexture(text);
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	CurrentAnimation->SetSize(32, 45);
	CurrentAnimation->Set2DPosition(240, 400);

	texture = ResourceManagers::GetInstance()->GetTexture("Shield.png");
	shield_animation = std::make_shared<SpriteAnimation>(texture, 1, 10, 1, 0.2f);
	shield_animation->SetSize(45, 45);

	list_animation.push_back(CurrentAnimation);

	CurrentAnimation = list_animation[0];
	m_position = CurrentAnimation->GetPosition();

	spawnPosition = Vector2(m_position.x, m_position.y - 20);

	for (int i = 0;i < 20;i++) {
		Bullet* bullet = new Bullet("Projectile_Player.png", Vector2(16, 30), 4);
		bullet->SetSpawnPoint(spawnPosition);
		bullet->Tag = "PlayerBullet";
		bullet->SetVelocity(500.0f);
		bullets.push_back(bullet);
	}

	IsActive = true;
	Tag = "Player";
	m_instance = this;
}

Player::~Player() {
	Object::~Object();
}

void Player::HandleEvent(SDL_Event &e) {

}

void Player::HandleKeyEvent(SDL_Event& e) {
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		if (e.key.keysym.sym == SDLK_UP) {
			m_KeyPress |= 1 << 3;
		}
		else if (e.key.keysym.sym == SDLK_DOWN) {
			m_KeyPress |= 1 << 1;
		}

		if (e.key.keysym.sym == SDLK_RIGHT) {
			m_KeyPress |= 1 << 2;
		}
		else if (e.key.keysym.sym == SDLK_LEFT) {
			m_KeyPress |= 1;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}

	if (m_KeyPress & 1) {
		CurrentAnimation = list_animation[2];
		MoveDirection.x = -1;
	}
	else if (m_KeyPress & 4) {
		CurrentAnimation = list_animation[1];
		MoveDirection.x = 1;
	}
	else {
		MoveDirection.x = 0;
		CurrentAnimation = list_animation[0];
	}
	if (m_KeyPress & 2) {
		MoveDirection.y = 1;
	}
	else if (m_KeyPress & 8) {
		MoveDirection.y = -1;
	}
	else {
		MoveDirection.y = 0;
	}
}

void Player::Init() {

}

void Player::Update(float deltatime) {
	Object::Update(deltatime);
	if (!IsActive) {
		return;
	}

	Move(deltatime);
	spawnPosition = Vector2(m_position.x + 5, m_position.y - 20);

	currentShootTimer += deltatime;
	if (currentShootTimer >= shootTime) {
		Shoot();
		currentShootTimer = 0.0f;
	}

	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Update(deltatime);
			if (bullet->GetPosition().y < 0) {
				bullet->IsActive = false;
			}
		}
	}
	
	for (auto anim : list_animation) {
		anim->Update(deltatime);
	}

	if (IsShield) {
		currentShieldTimer += deltatime;
		shield_animation->Set2DPosition(m_position.x - 5, m_position.y);
		shield_animation->Update(deltatime);

		if (currentShieldTimer > 10.0f) {
			IsShield = false;
			currentShieldTimer = 0.0f;
		}
		return;
	}

	for (auto obj : object) {
		if (obj->Tag == "EnemyBullet" && obj->IsActive) {
			if (CollisionDetection::AABB(this->Collider, obj->Collider)) {
				obj->IsActive = false;
				TakeDamage(1);
			}
		}
	}
}

void Player::Draw(SDL_Renderer* renderer) {
	if (!IsActive) {
		return;
	}

	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Draw(renderer);
		}
	}

	CurrentAnimation->Draw(renderer);

	if (IsShield) {
		shield_animation->Draw(renderer);
	}
}

void Player::Move(float deltaTime) {
	for (auto anim : list_animation) {
		m_position = anim->GetPosition();
		Vector2 addPosition = Vector2(MoveDirection.x * deltaTime * m_Velocity, MoveDirection.y * deltaTime * m_Velocity);
		anim->Set2DPosition(std::clamp(m_position.x + addPosition.x, 0.0f, (float)SCREEN_WIDTH - 40), std::clamp(m_position.y + addPosition.y, 0.0f, (float)SCREEN_HEIDHT - 60));
	}
}

void Player::Shoot() {
	for (auto bullet : bullets) {
		if (!bullet->IsActive) {
			if (IsDoubleShooting){
				if (bulletCount < 2) {
					bullet->IsActive = true;
					bullet->SetSpawnPoint(spawnPosition + Vector2(bulletCount * 10 - 5.0f, 0));
					bulletCount++;
				}
				else {
					bulletCount = 0;
					break;
				}
			}
			else {
				bullet->IsActive = true;
				bullet->SetSpawnPoint(spawnPosition);
				break;
			}
		}
	}
}

void Player::TakeDamage(float damage) {
	currentHealth -= damage;

	if (currentHealth <= 0) {
		currentHealth = 0;
		Die();
	}
}

void Player::Die() {
	IsActive = false;
}

void Player::Heal() {
	currentHealth = maxHealth;
}

float Player::HealthCheck() {
	return currentHealth;
}