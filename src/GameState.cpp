#include "GameState.h"
#include "StateMachine.h"
#include "GridManager.h"

#include <memory>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

GameState::GameState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{
	//if (!m_backgroundTexture.loadFromFile("img/play.png"))
	//{
	//	throw std::runtime_error{ "Was unable to load image 'img/play.png'" };
	//}

	//m_background.setTexture(m_backgroundTexture, true);*/

	std::cout << "PlayState Init\n";
}

void GameState::Pause()
{
	std::cout << "PlayState Pause\n";
}

void GameState::Resume()
{
	std::cout << "PlayState Resume\n";
}

void GameState::Update()
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
			case sf::Keyboard::Scancode::Escape:
				m_machine.Quit();
				break;
			
			default:
				break;
			}
		}
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
			if (mouseButtonPressed->button == sf::Mouse::Button::Left)
			{
				std::cout << "The right mouse button was pressed\n";
				/*if (m_gridManager->HandleTileSelection(sf::Vector2i(mouseButtonPressed->position.x, mouseButtonPressed->position.y))) {
					std::cout << "Game won";
				}*/


			}
        }
	}
}

void GameState::Draw()
{
	m_window.clear(sf::Color(9, 9, 10));

	m_gridManager->DrawTiles(m_window);

	m_window.display();

}


