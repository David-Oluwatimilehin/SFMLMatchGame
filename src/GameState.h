#pragma once
#include "State.h"

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Tile;
class HUDManager;
class GridManager;
class SoundManager;
class BackgroundManager;
class StateMachine;
enum ELevelDifficulty;

namespace sf {
	class RenderWindow;
}

class GameState final: public State {
private:
	bool baseVisibility{ true };
	
	int m_rows{ 0 };
	int m_cols{ 0 };
	
	Tile* selectedTile = nullptr;
	sf::Vector2i selectedCoords = { -1,-1 };

	sf::Clock m_clock;
	sf::Clock m_deltaTime;
	sf::Time m_currentTime;
	sf::Time m_elapsedBaseTime;
	
	GridManager* m_gridManager;
	SoundManager* m_soundManager;
	BackgroundManager* m_backgroundManager;
	std::unique_ptr<HUDManager>m_guiManager;

public:
	GameState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
	~GameState();

	void SetupSound();
	void InitialiseHUD(const sf::Vector2f& window);
	void InitialiseGrid(const sf::Vector2f& window);
	void InitialiseBackground();

	void Pause() override;
	void Resume() override;

	void Update() override;
	void Draw() override;

};