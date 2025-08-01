#include "State.h"


State::State(StateMachine& machine, sf::RenderWindow& window, bool replaceScreen)
	: m_machine{ machine }
	, m_window{ window }
	, m_replacing{ replaceScreen }
{

}

std::unique_ptr<State> State::Next()
{
	return std::move(m_next);
}

