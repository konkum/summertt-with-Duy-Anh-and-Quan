#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Sound.h"
#include "GSOption.h"

class Sprite2D;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;

private:
	int scrolling_offset = 0;
	SDL_Event e;
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::shared_ptr<Sound>					m_Sound;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::vector<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	float time = 0.0f;
	float m_Velocity = 10.0f;
};

