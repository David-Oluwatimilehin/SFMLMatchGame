#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>

class HUDManager
{
private:
	int m_comboScore=0;
	int m_longComboScore=0;

	sf::Font m_displayFont;
	std::unordered_map<std::string,std::pair<sf::Text*, bool>> m_textMap;
	
public:
	~HUDManager();
	HUDManager(const std::string& fontFileName);
	HUDManager(int width, int height, const std::string& fontFileName, const sf::Color& color);

	void CreateText(const sf::Color& chosenColor, const sf::Vector2f& position, const std::string& textContent, const std::string& textID, int size, bool isVisible);
	void UpdateText(const std::string& textName, const std::string& message);
	void SetAllTextInvisible();
	void SetNewVisibility(const std::string& textToChange, bool newVisiblity);
	int GetComboScore() const { return m_comboScore; }
	void UpdateComboScore(int newScore);
	void UpdateTimerAmount(const std::string& currTime);
	void UpdateLongComboScore(int newScore);
	void IncrementComboScore(int amount = 1);
	void DisplayElements(sf::RenderWindow& window);

};

