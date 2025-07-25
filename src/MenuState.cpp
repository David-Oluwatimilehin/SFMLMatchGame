#include "MenuState.h"
#include "StateMachine.h"
#include "GameState.h"
#include "ELevelData.h"
#include "HUDManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>


MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool shouldReplace) 
	: State{ machine,window,shouldReplace }
{
	m_texture = std::make_unique<sf::Texture>("Assets/Background/backTwo.jpg");
	
	m_rect = new sf::IntRect({ 0,0 }, { (int)window.getView().getSize().x, (int)window.getView().getSize().y });

	// Create the background and set the rectangle
	m_background = std::make_unique<sf::Sprite>(*m_texture);
	m_background.get()->setTextureRect(*m_rect);

	// Create the menu text
	m_menuManager = std::make_unique<HUDManager>("Assets/Fonts/SolerinMagica.otf");
	m_menuManager->CreateText(sf::Color::White, { (float)m_window.getView().getSize().x / 4, 
		(float)m_window.getView().getSize().y/4}, 
		"MATCH GAME", "welcomeMessage", (int)m_window.getView().getSize().x/12, true);

	m_menuManager->CreateText(sf::Color::White, { (float)m_window.getView().getSize().x / 4,
		(float)m_window.getView().getSize().y / 6 * 5 }, 
		"Press Space to start", "spaceStart", (int)m_window.getView().getSize().x/20, true);

	std::cout << "Menu Initialised\n";	

}

void MenuState::Pause()
{
	std::cout << "Menu Screen Paused\n";
}

void MenuState::Resume()
{
	std::cout << "Menu Screen Resumed\n";
}

void MenuState::Update()
{
	//std::cout << "Menu Screen Updated\n";

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
			case sf::Keyboard::Scancode::Space:
				
				m_machine.SetDifficulty(EDifficultyLevel::eEasy);

				m_next = StateMachine::build<GameState>(m_machine, m_window, true);
				break;
			default:
				break;
			}
		}
		
	}
	//m_clock.getElapsedTime();
}

void MenuState::Draw()
{

	m_window.clear(sf::Color::White);

	m_window.draw(*m_background);
	m_menuManager.get()->DisplayElements(m_window);
	//m_gridManager

	m_window.display();
}
