#pragma once
#include "State.h"

class StateMachine;
class GridManager;

namespace sf {
	class RenderWindow;
}

class GameState : public State {
private:
	
	GridManager* m_gridManager;

public:
	GameState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	void Pause() override;
	void Resume() override;

	void Update() override;
	void Draw() override;

};