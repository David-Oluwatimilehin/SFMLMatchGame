#include "BackgroundManager.h"

#include <SFML/Graphics/RenderWindow.hpp>


BackgroundManager::BackgroundManager(float scrollSpeed, const std::string& path):
	m_scrollSpeed(scrollSpeed)
{
	m_backgroundTexture = std::make_unique<sf::Texture>(path);
	m_gameBackground = std::make_unique<sf::Sprite>(*m_backgroundTexture);

	m_loopWidth = m_gameBackground.get()->getTexture().getSize().x / 2;
	
	m_gameBackground->setPosition({ 0, 0 });
}

void BackgroundManager::ScrollingBackground(const sf::Time& deltaTime)
{
    m_scrollOffset += m_scrollSpeed * deltaTime.asSeconds();
	    
    if (m_scrollOffset > m_loopWidth)
    {
        m_scrollOffset -= m_loopWidth;
    }
}


void BackgroundManager::Draw(sf::RenderWindow& window)
{	
	m_drawRect = sf::IntRect({ (int)m_scrollOffset, 0 }, { (int)window.getSize().x, (int)window.getSize().y });
	m_gameBackground->setTextureRect(m_drawRect);

	window.draw(*m_gameBackground);
}