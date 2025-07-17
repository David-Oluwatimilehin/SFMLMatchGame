#pragma once

#include <SFML/Graphics.hpp>

class GridManager;
class HUDManager;

class Game {
private:
	int m_rows = 0;
	int m_columns = 0;

	int m_screenWidth;
	int m_screenHeight;

	GridManager* m_gridManager;
	HUDManager* m_hudManager;
	sf::RenderWindow* m_window;
	
	void End();
public:
	Game();
	void Start(unsigned int width, unsigned int height, const char* windowTitle, unsigned int rows, unsigned int columns);
	void Update(unsigned int fpsLimit);
	
};

