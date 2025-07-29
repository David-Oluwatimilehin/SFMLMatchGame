#pragma once


#include "StateMachine.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Game {
private:
	StateMachine m_machine;
	sf::RenderWindow m_window;
	
public:
	Game(unsigned int width, unsigned int height, int frameRate, const char* windowTitle, int frameLimit);
	~Game();
	void Run();
	
};

