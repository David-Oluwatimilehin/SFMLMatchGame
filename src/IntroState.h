#pragma once

#include "State.h"

class StateMachine;

namespace sf
{
	class RenderWindow;
	
}

class IntroState final: public State {
private:

public:
	IntroState(StateMachine& machine, sf::RenderWindow& window, const bool replace);

	void Pause() override;
	void Resume() override;

	void Update() override;
	void Draw() override;
};