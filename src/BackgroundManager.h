#pragma once

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>

namespace sf {
	class RenderWindow;
}

class BackgroundManager
{
private:
	float m_loopWidth{ 0 };
	float m_scrollSpeed{ 0 };
	float m_scrollOffset{ 0 };
	sf::IntRect m_drawRect;
	std::unique_ptr<sf::Texture>m_backgroundTexture;
	std::unique_ptr<sf::Sprite> m_gameBackground;

public:
	BackgroundManager(float scrollSpeed, const std::string& path);
	void ScrollingBackground(const sf::Time& deltaTime);

	void Draw(sf::RenderWindow& window);
};

