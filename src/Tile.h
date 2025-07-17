#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Tile
{
private:
	bool fronVisible;
	bool middVisible;
	bool backVisible;

	int backNumber;
	int middleNumber;
	int frontNumber;

	float m_tileSize;
	sf::Vector2f m_pos;

	sf::Color backColour;
	sf::Color middleColour;
	sf::Color frontColour;
public:
	bool isHighlighted{false};

	Tile(int back, int mid, int front, float tileSize);

	bool IsFullyInvisible() const { return !fronVisible && !middVisible && !backVisible; }
	bool GetMiddleVis() const { return middVisible; }
	bool GetFrontVis() const { return fronVisible; }
	bool GetBackVis() const { return backVisible; }

	int GetFrontNumber() const { return frontNumber; }
	int GetMiddleNumber() const { return middleNumber; }
	int GetBackNumber() const { return backNumber; }

	void SetFrontInvisible(bool newVisiblity) { fronVisible = newVisiblity; }
	void SetMiddleInvisible(bool newVisiblity) { middVisible = newVisiblity; }
	void SetBackInvisible(bool newVisiblity) { backVisible = newVisiblity; }



	void Draw(sf::RenderWindow& window, const sf::Vector2f& pos);

};

