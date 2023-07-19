#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include <algorithm>
#include "GameObjectToShow/Player.h"
#include "GameObjectToShow/EnemyPool.h"
#include <string>

std::unique_ptr<Player> player;
EnemyPool* enemyPool = NULL;

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
	delete enemyPool;
	enemyPool = NULL;
}


void GSPlay::Init()
{
	enemyPool = new EnemyPool();
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_play.png");


	// background
	
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   //Player
	player = std::make_unique<Player>();
	player->Init();

	enemyPool->Init();
	//enemyPool->SetSpawn(Vector2(200, 300), Vector2(1, 0.5f));

	//game music
	m_Sound = std::make_shared<Sound>("Data/Sounds/Operation_Blade.mp3");
	m_Sound->Volume(60);
	if (m_Sound->isPlaying) {
		m_Sound->PlaySound();
	}
	else {
		m_Sound->PauseSound();
	}

	//health bar
	texture = ResourceManagers::GetInstance()->GetTexture("Credit.tga");
	m_healthBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_healthBar->SetSize(150, 50);
	m_healthBar->Set2DPosition(10, 10);

	texture = ResourceManagers::GetInstance()->GetTexture("Health.png");
	m_health = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_health->SetSize(player->HealthCheck()*1.2, 27);
	m_health->Set2DPosition(25, 20);

	SDL_Color m_textColor = { 255,255,255 };

	m_textLine = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textLine->SetSize(25, 50);
	m_textLine->Set2DPosition((SCREEN_WIDTH - m_textLine->GetWidth()), SCREEN_HEIDHT/2 - 50);
	m_textLine->LoadFromRenderText("0");

	player->onPlayerPointUpdate = [=]() mutable {
		player->Point += 1;
		if (player->Point < 10) {
			m_textLine->Set2DPosition((SCREEN_WIDTH - m_textLine->GetWidth()), SCREEN_HEIDHT / 2 - 50);
			m_textLine->SetSize(25, 50);
		}
		else if (player->Point < 100 && player->Point >=10)
		{
			m_textLine->Set2DPosition((SCREEN_WIDTH - m_textLine->GetWidth()), SCREEN_HEIDHT / 2 - 50);
			m_textLine->SetSize(50, 50);
		}

		m_textLine->LoadFromRenderText(std::to_string(player->Point));
	};
}


void GSPlay::Exit()
{
	
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	player->HandleKeyEvent(e);
	
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

float currentTime = 0.0f;

void PlayScenario(float deltaTime) {
	currentTime += deltaTime;
	if (currentTime > 1.0f) {
		enemyPool->SetSpawn(Vector2(200, 300), Vector2(1, 0.5f));
		currentTime = 0.0f;
	}
}

void GSPlay::Update(float deltaTime)
{
	player->Update(deltaTime);
	PlayScenario(deltaTime);
	enemyPool->Update(deltaTime);
	
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	scrolling_offset++;
	if (scrolling_offset > m_background->GetHeight()) {
		scrolling_offset = 0;
	}

	//m_health->Update(deltaTime);
	m_health->SetSize(player->HealthCheck() * 1.2, 27);
	


	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Set2DPosition(0, scrolling_offset);
	m_background->Draw(renderer);
	m_background->Set2DPosition(0, scrolling_offset - m_background->GetHeight());
	m_background->Draw(renderer);

	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}


	player->Draw(renderer);
	enemyPool->Draw(renderer);

	m_healthBar->Draw(renderer);
	m_health->Draw(renderer);
	m_textLine->Draw(renderer);
}