#include "IntroState.h"
#include "StateMachine.h"
//#include "GameState.h"

#include <iostream>
#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>


IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, const bool replace) :
	State { machine, window, replace }
{
	
	// Fill the fader surface with black
	std::cout << "IntroState Init\n";
}


void IntroState::Pause()
{
	std::cout << "IntroState Pause\n";
}

void IntroState::Resume()
{
	std::cout << "IntroState Resume\n";
}

void IntroState::Update()
{
	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_machine.Quit();
			break;
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) 
		{
			switch (keyPressed->scancode) 
			{
			case sf::Keyboard::Scancode::Space:
				//m_next = StateMachine::build<GameState>(m_machine, m_window, true);
				break;
			case sf::Keyboard::Scancode::Escape:
				m_machine.Quit();
				break;
			default:
				break;
			}
		}
	}

}

void IntroState::Draw()
{

	m_window.clear(sf::Color::Black);
	
	m_window.display();
}
