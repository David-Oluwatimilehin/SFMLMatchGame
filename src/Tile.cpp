#include "Tile.h"


Tile::Tile(int back, int mid, int front, float tileSize): backNumber(back), middleNumber(mid), frontNumber(front), m_tileSize(tileSize)
{
	fronVisible = true;
	middVisible = true;
	backVisible = true;

	switch (back) {
	case 0:
		backColour = sf::Color(160, 22, 65); // Pink
		break;
	case 1:
		backColour = sf::Color::Green;
		break;
	case 2:
		backColour = sf::Color(248, 204, 105); // Crimson
		break;
	case 3:
		backColour = sf::Color(0, 127, 255); // Blue
		break;
	default:
		backColour = sf::Color::Magenta;
		break;
	}

	switch (mid) {
	case 0:
		middleColour = sf::Color(0, 45, 98);
		break;
	case 1:
		middleColour = sf::Color(250, 190, 16);
		break;
	case 2:
		middleColour = sf::Color(185, 217, 235);
		break;
	case 3:
		middleColour = sf::Color(230, 99, 134);
		break;
	default:
		middleColour = sf::Color::Magenta;
		break;
	}

	switch (front) {
	case 0:
		frontColour = sf::Color(255, 87, 51);
		break;
	case 1:
		frontColour = sf::Color(255, 192, 203);
		break;
	case 2:
		frontColour = sf::Color::White;
		break;
	case 3:
		frontColour = sf::Color::Yellow;
		break;
	default:
		frontColour = sf::Color::Magenta;
		break;
	}
}

void Tile::Draw(sf::RenderWindow& window, const sf::Vector2f& pos)
{
    sf::RectangleShape highlightRect;
    highlightRect.setPosition(pos);
    highlightRect.setSize({ m_tileSize, m_tileSize });
    highlightRect.setFillColor(sf::Color::Transparent);
    highlightRect.setOutlineColor(sf::Color::Magenta);
    highlightRect.setOutlineThickness(3.0f);

    sf::RectangleShape backRect;
    backRect.setPosition(pos);
    backRect.setSize({ m_tileSize, m_tileSize });
    backRect.setFillColor(backColour);
    
    sf::RectangleShape middleRect;
    middleRect.setOrigin(sf::Vector2f(-7.5f, -7.5f));
    middleRect.setPosition(pos);
    middleRect.setSize({ 35.0f, 35.0f });
    middleRect.setFillColor(middleColour);

    sf::RectangleShape frontRect;
    frontRect.setOrigin(sf::Vector2f(-15.0f, -15.0f));
    frontRect.setPosition(pos);
    frontRect.setSize({ 20.0f, 20.0f });
    frontRect.setFillColor(frontColour);

    if (isHighlighted)
        window.draw(highlightRect);

    if (backVisible)
        window.draw(backRect);

    if (middVisible)
        window.draw(middleRect);

    if (fronVisible)
        window.draw(frontRect);

}
