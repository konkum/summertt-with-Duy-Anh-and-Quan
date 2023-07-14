#include "Enemy.h"
#include "ResourceManagers.h"
#include "BezierPath.h"
#include "Define.h"

Enemy::Enemy(const char* texture, int sizeW, int sizeH,int animFrame) {
	Object::Init();
	auto tex = ResourceManagers::GetInstance()->GetTexture(texture);

	CurrentAnimation = std::make_shared<SpriteAnimation>(tex, 1, animFrame, 1, 0.2f);
	CurrentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	CurrentAnimation->SetSize(sizeW, sizeH);

	m_position = CurrentAnimation->GetPosition();

	for (int i = 0;i < 20;i++) {
		Bullet* bullet = new Bullet("Projectile_Enemy.png", Vector2(30, 30), 3);
		bullet->MoveDirection = -1;
		bullet->Tag = "EnemyBullet";
		bullets.push_back(bullet);
	}
	Tag = "Enemy";
}

void Enemy::Init() {
}


void Enemy::Update(float deltatime) {
	if (!IsActive) {
		return;
	}

	Object::Update(deltatime);
	m_position = CurrentAnimation->GetPosition();


	HandleStates(deltatime);
	//Move(deltatime);
	currentTime += deltatime;
	if (currentTime > 1.0f) {
		currentTime = 0;
		ShootBullet();
	}
	
}

void Enemy::UpdateBullet(float deltaTime) {
	for (auto bullet : bullets) {
		bullet->Update(deltaTime);

		if (bullet->IsActive) {
			if (bullet->GetPosition().x < 0 || bullet->GetPosition().x>480) {
				bullet->IsActive = false;
			}
			else if (bullet->GetPosition().y < 0 || bullet->GetPosition().y>800) {
				bullet->IsActive = false;
			}
		}
	}
}

void Enemy::Move(float deltaTime) {
	
	CurrentAnimation->Set2DPosition(m_position.x + MoveDirection.x, m_position.y + MoveDirection.y);
}


void Enemy::Draw(SDL_Renderer* renderer) {
	if (!IsActive) {
		return;
	}

	CurrentAnimation->Draw(renderer);

	for (int i = 0;i < sPaths[mCurrentPath].size() - 1;i++) {
		Renderer::GetInstance()->DrawLine(sPaths[mCurrentPath][i].x, sPaths[mCurrentPath][i].y, sPaths[mCurrentPath][i + 1].x, sPaths[mCurrentPath][i + 1].y);
	}
}

void Enemy::DrawBullet(SDL_Renderer* renderer) {
	for (auto bullet : bullets) {
		bullet->Draw(renderer);
	}
}

void Enemy::TakeDamage(float damage) {
	currentHealth -= damage;

	if (currentHealth <= 0) {
		currentHealth = 0;
		Die();
	}
}

void Enemy::Die() {
	if (IsActive) {
		IsActive = false;
	}
}

void Enemy::ShootBullet() {
	for (auto bullet : bullets) {
		if (!bullet->IsActive) {
			bullet->IsActive = true;
			bullet->SetSpawnPoint(CurrentAnimation->Get2DPosition());
			break;
		}
	}
}

//Testing

std::vector<std::vector<Vector2>> Enemy::sPaths;

void Enemy::CreatePath() {

	int screenMidPoint = SCREEN_WIDTH * 0.4f;

	int currentPath = 0;
	BezierPath* path = new BezierPath();
	
	path->AddCurve({ Vector2(screenMidPoint + 50.0f,-10.0f),Vector2(screenMidPoint + 50.0f,-20.0f) ,Vector2(screenMidPoint + 50.0f,30.0f) ,Vector2(screenMidPoint + 50.0f,20.0f) }, 1);
	path->AddCurve({ Vector2(screenMidPoint + 50.0f,20.0f),Vector2(screenMidPoint + 50.0f, 100.0f) ,Vector2(75.0f ,325.0f) ,Vector2(75.0f,425.0f) }, 25);
	path->AddCurve({ Vector2(75.0f ,425.0f),Vector2(75.0f, 650.0f) ,Vector2(325.0f ,650.0f) ,Vector2(325.0f,425.0f) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
}

Enemy::Enemy(int path) {

	mCurrentPath = path;
	Object::Init();
	auto tex = ResourceManagers::GetInstance()->GetTexture("Enemies_AG.png");

	CurrentAnimation = std::make_shared<SpriteAnimation>(tex, 1, 6, 1, 0.2f);
	CurrentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	CurrentAnimation->SetSize(30, 30);
	CurrentAnimation->Set2DPosition(Vector2(480 * 0.4f, 800 * 0.5f));

	mCurrentStates = flyIn;

	mCurrentWayPoint = 0;
	CurrentAnimation->Set2DPosition(sPaths[mCurrentPath][mCurrentWayPoint]);

	m_position = CurrentAnimation->GetPosition();
}

void Enemy::HandleStates(float deltaTime) {
	switch (mCurrentStates)
	{
	case Enemy::flyIn:
		HandleFlyInState(deltaTime);
		break;	
	case Enemy::formation:
		HandleFormationState();
		break;
	case Enemy::dive:
		HandleDiveState();
		break;
	case Enemy::dead:
		HandleDeadState();
		break;
	default:
		break;
	}
}

void Enemy::HandleFlyInState(float deltaTime) {
	if ((sPaths[mCurrentPath][mCurrentWayPoint] - CurrentAnimation->Get2DPosition()).MagnitudeSqr() < EPSILON) {
		mCurrentWayPoint++;
	}

	if (mCurrentWayPoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWayPoint] - CurrentAnimation->Get2DPosition();

		CurrentAnimation->Set2DPosition(CurrentAnimation->Get2DPosition() + dist.Normalize() * deltaTime * m_Velocity);
	}
	else {
		mCurrentStates = formation;
	}
}

void Enemy::HandleDiveState() {

}

void Enemy::HandleFormationState() {

}

void Enemy::HandleDeadState() {

}