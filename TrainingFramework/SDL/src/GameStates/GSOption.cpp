#include "GSOption.h"

GSOption::GSOption() : GameStateBase(StateType:: STATE_OPTION),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}

GSOption::~GSOption() 
{
}

void GSOption::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_main.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	m_Sound = std::make_shared<Sound>("Data/Sounds/Alarm01.wav");
	m_Sound->PlaySound();

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// button mute
	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	std::shared_ptr<MouseButton> btnMute = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMute->SetSize(100, 100);
	btnMute->Set2DPosition(SCREEN_WIDTH / 2, SCREEN_HEIDHT / 2);
	btnMute->SetOnClick([=]() mutable {
		if (Mix_PausedMusic() == 0) {
			m_Sound->PlaySound();
			 texture = ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga");
			btnMute->SetTexture(texture);
		}
		else {
			m_Sound->PlaySound();
			texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
			btnMute->SetTexture(texture);
		}
		});
	m_listButton.push_back(btnMute);
}

void GSOption::Exit()
{
}

void GSOption::Pause()
{
	m_Sound->StopSound();
}

void GSOption::Resume()
{
	m_Sound->PlaySound();
}

void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(SDL_Event& e)
{
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{
}

void GSOption::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSOption::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSOption::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
}