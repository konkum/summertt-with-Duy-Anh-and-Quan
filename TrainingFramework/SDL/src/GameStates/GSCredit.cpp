#include "GSCredit.h"
#include "GameObject/TextureManager.h"
#include "GameObject/SpriteAnimation.h"

GSCredit::GSCredit() : GameStateBase(StateType::STATE_CREDIT),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textLine1(nullptr), m_textLine2(nullptr), m_textLine3(nullptr)
{
}


GSCredit::~GSCredit()
{
}


void GSCredit::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_credit.png");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// game title
	///Set Font
	m_textColor = { 0, 0, 0 };

	m_textLine1 = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textLine1->SetSize(300, 50);
	m_textLine1->Set2DPosition((SCREEN_WIDTH - m_textLine1->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 50 );
	m_textLine1->LoadFromRenderText("Thành viên");

	m_textLine2 = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textLine2->SetSize(160, 40);
	m_textLine2->Set2DPosition((SCREEN_WIDTH - m_textLine2->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 10);
	m_textLine2->LoadFromRenderText("Duy Anh");

	m_textLine3 = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textLine3->SetSize(112, 40);
	m_textLine3->Set2DPosition((SCREEN_WIDTH - m_textLine3->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 50);
	m_textLine3->LoadFromRenderText("Quân");

	m_Sound = std::make_shared<Sound>("Data/Sounds/Operation_Blade.mp3");
	if (m_Sound->isPlaying) {
		m_Sound->PlaySound();
	}
	else {
		m_Sound->PauseSound();
	}
}

void GSCredit::Exit()
{

}


void GSCredit::Pause()
{

}
void GSCredit::Resume()
{

}


void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(SDL_Event& e)
{
	
}

void GSCredit::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
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

void GSCredit::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textLine1->Draw(renderer);
	m_textLine2->Draw(renderer);
	m_textLine3->Draw(renderer);
}