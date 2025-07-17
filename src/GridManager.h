#pragma once
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
class Tile;

class GridManager
{
private:
	int m_rows;
	int m_columns;
	
	float m_tileSize;
	float m_tileSpacing;

	sf::Vector2f m_startPos;
	std::mt19937 m_randEngine;

	Tile* selectedTile{ nullptr };
	Tile* secondTile{ nullptr };

	sf::Vector2i selectedCoords = { -1,-1 };
public:
	//int checkCounts;
	std::vector<std::vector<Tile*>> m_gameBoard;
	
	bool HasWonGame();	
	bool ResolveMatches(Tile& tileOne, Tile& tileTwo);
	bool HandleTileSelection(const sf::Vector2i mousePressed);
	void GeneratePatterns();
	void RemoveTile(int x, int y);
	void DrawTiles(sf::RenderWindow& window);
	
	std::pair<int, int> GetTileCoords(const sf::Vector2i& mousePos);

	GridManager(unsigned int rows, unsigned int columns, sf::Vector2f startPos, const float tileSize, const float tileSpacing);
	~GridManager();
	
};

