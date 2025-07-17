#pragma once

#include "State.h"

#include <memory>
#include <stack>

namespace sf {
	class RenderWindow;
}

class StateMachine {
private:
	bool m_resume;
	bool m_running;

	std::stack<std::unique_ptr<State>> m_stateStack;

public:

	StateMachine();
	void NextState();
	void LastState();
	
	void Run(std::unique_ptr<State> state);
	void Update();
	
	void Draw();
	void Quit();

	bool IsRunning() const { return m_running; }

	/*template <typename T>
	static std::unique_ptr<T> build(StateMachine& machine, sf::RenderWindow& window, bool replace = true);*/
};


/*template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine& machine, sf::RenderWindow& window, bool replace)
{
	auto new_state = std::unique_ptr<T>{ nullptr };

	try
	{
		new_state = std::make_unique<T>(machine, window, replace);
	}
	catch (std::runtime_error& exception)
	{
		std::cout << "Creation of new state was unsuccessful\n";
		std::cout << exception.what() << std::endl;
	}

	return new_state;
}*/