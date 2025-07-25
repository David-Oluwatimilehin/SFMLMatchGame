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
	sf::Time currentTime;
	sf::Time elapsedBaseTime;

	sf::IntRect* m_rectView;
	GridManager* m_gridManager;
	SoundManager* m_soundManager;
	std::unique_ptr<HUDManager>m_guiManager;
	
	std::unique_ptr<sf::Sprite> m_gameBackground;
	std::unique_ptr<sf::Texture> m_backGameTexture;

public:
	GameState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
	~GameState();

	void SetupSound();
	void InitialiseHUD(const sf::Vector2f& window);
	void InitialiseGrid(const sf::Vector2f& window);

	void Pause() override;
	void Resume() override;

	void Update() override;
	void Draw() override;

};