#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


struct Tile
{
	bool fronVisible{ true };
	bool middVisible{ true };
	bool backVisible{ true };
	bool isHighlighted{false};

	int backNumber;
	int middleNumber;
	int frontNumber;

	float m_tileSize;
	float m_tileSpacing;

	sf::Color backColour;
	sf::Color middleColour;
	sf::Color frontColour;	

	Tile(int back, int mid, int front, float tileSize, float tileSpacing);

	bool IsFullyInvisible() const { return !fronVisible && !middVisible && !backVisible; }
	
	void SetFrontInvisible() { fronVisible = !fronVisible; }
	void SetMiddleInvisible() { middVisible = !middVisible; }
	void SetBackInvisible() { backVisible = !backVisible; }

	void Draw(sf::RenderWindow& window, const sf::Vector2f& pos);

};

