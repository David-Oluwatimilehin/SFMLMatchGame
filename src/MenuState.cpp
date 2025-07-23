#include "MenuState.h"
#include "StateMachine.h"
#include "HUDManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool shouldReplace) 
	: State{ machine,window,shouldReplace }
{

	m_texture = std::make_unique<sf::Texture>("Assets/Background/backTwo.jpg");
	
	m_rect = sf::IntRect({ 0,0 }, { (int)window.getView().getSize().x, (int)window.getView().getSize().y });

	m_background = std::make_unique<sf::Sprite>(*m_texture);
	m_background.get()->setTextureRect(m_rect);

	m_menuManager = std::make_unique<HUDManager>("Assets/Fonts/SolerinMagica.otf");
	
	m_menuManager->CreateText(sf::Color::White, { m_window.getView().getSize().x / 4, 
		m_window.getView().getSize().y/4}, 
		"MATCH GAME", "welcomeMessage", m_window.getView().getSize().x/12, true);

	m_menuManager->CreateText(sf::Color::White, { m_window.getView().getSize().x / 4, 
		m_window.getView().getSize().y / 6 * 5 }, 
		"Press Space to start", "spaceStart", m_window.getView().getSize().x/20, true);

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
				m_next = StateMachine::build<MenuState>(m_machine, m_window, false);
				break;
			default:
				break;
			}
		}
		else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			
		}
	}
}

void MenuState::Draw()
{
	m_window.clear(sf::Color::White);

	m_window.draw(*m_background);
	m_menuManager.get()->DisplayElements(m_window);
	
	m_window.display();
}
