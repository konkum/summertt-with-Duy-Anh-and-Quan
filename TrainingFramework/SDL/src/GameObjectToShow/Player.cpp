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
	currentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 4, 1, 0.2f);
	currentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	currentAnimation->SetSize(40, 50);
	currentAnimation->Set2DPosition(240, 400);

	m_listAnimation.push_back(currentAnimation);

	m_position = currentAnimation->GetPosition();

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
}

void Player::Init() {

}

void Player::Update(float deltatime) {

	if (m_KeyPress & 1) {
		x_input = -1;
	}
	else if (m_KeyPress & 4) {
		x_input = 1;
	}
	else {
		x_input = 0;
	}
	if (m_KeyPress & 2) {
		y_input = 1;
	}
	else if (m_KeyPress & 8) {
		y_input = -1;
	}
	else {
		y_input = 0;
	}

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
	

	
	for (auto it : m_listAnimation)
	{
		it->Update(deltatime);
	}
}

void Player::Draw(SDL_Renderer* renderer) {
	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Draw(renderer);
		}
	}
	
	
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}

void Player::Move(float deltaTime) {
	m_position = currentAnimation->GetPosition();
	Vector2 addPosition = Vector2(x_input * deltaTime * m_Velocity, y_input * deltaTime * m_Velocity);
	currentAnimation->Set2DPosition(std::clamp(m_position.x + addPosition.x, 0.0f, (float)SCREEN_WIDTH - 40), std::clamp(m_position.y + addPosition.y, 0.0f, (float)SCREEN_HEIDHT - 60));
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