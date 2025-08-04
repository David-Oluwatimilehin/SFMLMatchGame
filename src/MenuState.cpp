#include "MenuState.h"
#include "StateMachine.h"
#include "BackgroundManager.h"
#include "GameState.h"
#include "ELevelData.h"
#include "HUDManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>


MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool shouldReplace) 
	: State{ machine,window,shouldReplace }
{

	

	m_menuBackground = new BackgroundManager(50.0f, "Assets/Background/backThree.jpg");

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

MenuState::~MenuState()
{
	delete m_menuBackground;
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
	
	const sf::Time dt = m_clock.restart();

	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_machine.Quit();
			break;
		}
		else if (event->is<sf::Event::Resized>()) {
			m_window.setSize(sf::Vector2u( (int)m_window.getDefaultView().getSize().x, (int)m_window.getDefaultView().getSize().y ));
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

	m_menuBackground->ScrollingBackground(dt);
	//m_clock.getElapsedTime();
}

void MenuState::Draw()
{

	m_window.clear(sf::Color::White);

	m_menuBackground->Draw(m_window);
	m_menuManager.get()->DisplayElements(m_window);

	m_window.display();
}
