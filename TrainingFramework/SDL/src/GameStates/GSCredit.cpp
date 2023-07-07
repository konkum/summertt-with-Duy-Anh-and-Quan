#include "GSCredit.h"
#include "GameObject/TextureManager.h"
#include "GameObject/SpriteAnimation.h"

GSCredit::GSCredit()
{
}


GSCredit::~GSCredit()
{
}


void GSCredit::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_play.png");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

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
	
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
	
}

void GSCredit::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
}