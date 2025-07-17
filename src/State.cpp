#include "State.h"


State::State(StateMachine& machine, sf::RenderWindow& window, const bool replace)
	: m_machine{ machine }
	, m_window{ window }
	, m_replacing{ replace }
{

}

std::unique_ptr<State> State::next()
{
	return std::move(m_next);
}

