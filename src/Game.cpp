#include "Game.h"


#include "MenuState.h"

#include <iostream>


Game::Game(unsigned int width, unsigned int height, int frameRate, const char* windowTitle, int frameLimit)
{
    m_window = sf::RenderWindow(sf::VideoMode({ width, height }), windowTitle, sf::Style::Default);
    m_window.setFramerateLimit(frameLimit);

    std::cout << "Game Initialised\n";
}

// Game Destructor: The window is destroyed automatically.
Game::~Game()
{
    
    std::cout << "Game Cleaned Up\n";
}

// The ONLY function needed to run the game.
void Game::Run()
{
    // Create the first state (MenuState) and run the machine.
    m_machine.Run(StateMachine::build<MenuState>(m_machine, m_window, true));

    // The main game loop, driven entirely by the state machine.
    while (m_machine.IsRunning())
    {
        m_machine.NextState();
        m_machine.Update();
        m_machine.Draw();
    }
}

