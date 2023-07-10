#include "Player.h"
#include "GameManager/ResourceManagers.h"
#include "Define.h"
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<Bullet*> bulletInitialze;
Pool<Bullet*, 10> bullets;
Vector2 spawnPosition;

Player::Player() {
	auto texture = ResourceManagers::GetInstance()->GetTexture("Actor1_3.tga");
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 4, 1, 0.2f);
	CurrentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	CurrentAnimation->SetSize(40, 50);
	CurrentAnimation->Set2DPosition(240, 400);

	m_position = CurrentAnimation->GetPosition();

	spawnPosition = Vector2(m_position.x, m_position.y - 20);

	for (int i = 0;i < 10;i++) {
		Bullet* bullet = new Bullet();
		bullet->SetSpawnPoint(spawnPosition);
		bulletInitialze.push_back(bullet);
	}

	new(&bullets) Pool<Bullet*, 10>(bulletInitialze.begin(), bulletInitialze.end());
}

Player::~Player() {

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
		MoveDirection.x = -1;
	}
	else if (m_KeyPress & 4) {
		MoveDirection.x = 1;
	}
	else {
		MoveDirection.x = 0;
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

	Move(deltatime);
	spawnPosition = Vector2(m_position.x, m_position.y - 20);

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
	
	CurrentAnimation->Update(deltatime);
}

void Player::Draw(SDL_Renderer* renderer) {
	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Draw(renderer);
		}
	}
	
	CurrentAnimation->Draw(renderer);
}

void Player::Move(float deltaTime) {
	m_position = CurrentAnimation->GetPosition();
	Vector2 addPosition = Vector2(MoveDirection.x * deltaTime * m_Velocity, MoveDirection.y * deltaTime * m_Velocity);
	CurrentAnimation->Set2DPosition(std::clamp(m_position.x + addPosition.x, 0.0f, (float)SCREEN_WIDTH - 40), std::clamp(m_position.y + addPosition.y, 0.0f, (float)SCREEN_HEIDHT - 60));
}

void Player::Shoot() {
	for (auto bullet : bullets) {
		if (!bullet->IsActive) {
			bullet->IsActive = true;
			bullet->SetSpawnPoint(spawnPosition);
			break;
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
}