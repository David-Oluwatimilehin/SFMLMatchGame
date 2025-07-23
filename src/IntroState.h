#pragma once

#include "State.h"

#include <SFML/Graphics.hpp>


class StateMachine;

namespace sf
{
	class RenderWindow;
}

class IntroState final : public State
{
private:
	sf::Texture m_backgroundTexture;
	sf::Sprite m_background;

public:
	
	IntroState(StateMachine& machine, sf::RenderWindow& window, bool replaceScreen=true);

	void Pause() override;
	void Resume() override;

	void Update() override;
	void Draw() override;

};