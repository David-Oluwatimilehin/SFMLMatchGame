#pragma once
#include <memory>

class StateMachine;

namespace sf {
	class RenderWindow;
}

class State {
protected:
	bool m_replacing;

	StateMachine& m_machine;
	
	sf::RenderWindow& m_window;
	std::unique_ptr<State> m_next;

public:
	State(StateMachine& machine, sf::RenderWindow& window, bool replaceScreen);
	State(const State&) = delete;
	
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~State()= default;
	std::unique_ptr<State> Next();
	State& operator=(const State&) = delete;

	bool isReplacing() const { return m_replacing; }
	
};