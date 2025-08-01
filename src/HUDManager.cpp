#include "HUDManager.h"
#include <unordered_map>


HUDManager::~HUDManager()
{
	for (auto itr : m_textMap)
		delete(itr.second.first);
	
}

HUDManager::HUDManager(const std::string& fontFileName)
{
	if (!m_displayFont.openFromFile(fontFileName)) {
		std::cout << "The font didn't load.\n";
	}

	std::cout << "The font did load.\n";
}

HUDManager::HUDManager(int width, int height, const std::string& fontFileName, const sf::Color& color)
{
	
	m_comboScore = 0;
	m_longComboScore = 0;

	if (!m_displayFont.openFromFile(fontFileName)) {
		std::cout << "The font didn't load.\n";
	}

	std::cout << "The font did load.\n";


	sf::Text* currText = new sf::Text(m_displayFont);
	currText->setFillColor(color);
	currText->setPosition({ float(width / 8) * 6, float(height / 10) * 7 + 40 });
	currText->setCharacterSize(50);
	currText->setString(std::to_string(m_comboScore));
	m_textMap.insert({ "longComboAmount", {currText ,true} });


	sf::Text* newText = new sf::Text(m_displayFont);
	newText->setFillColor(color);
	newText->setPosition({ float(width / 8), float(height / 10) * 7 + 40 });
	newText->setCharacterSize(50);
	newText->setString(std::to_string(m_longComboScore));
	m_textMap.insert({ "currComboAmount", {newText,true} });

};

void HUDManager::CreateText(const sf::Color& chosenColor, const sf::Vector2f& position, const std::string& textContent, const std::string& textID, int size, bool isVisible)
{
	sf::Text* newText = new sf::Text(m_displayFont);
	newText->setFillColor(chosenColor);
	newText->setPosition(position);
	newText->setCharacterSize(size);
	newText->setString(textContent);

	m_textMap.insert({ textID, {newText ,isVisible} });

}

void HUDManager::UpdateText(const std::string& textName, const std::string& message)
{
	auto it = m_textMap.find(textName);
	if (it != m_textMap.end()) {
		it->second.first->setString(message);
	}
}

void HUDManager::SetAllTextInvisible()
{
	for (auto &curr : m_textMap) {
		curr.second.second = false;
	}
}

void HUDManager::SetNewVisibility(const std::string& textToChange,bool newVisiblity)
{
	auto it = m_textMap.find(textToChange);
	if (it != m_textMap.end()) {
		it->second.second = newVisiblity; 
	}
}

void HUDManager::UpdateComboScore(int newScore) {
	m_comboScore = newScore;
	auto it = m_textMap.find("currComboAmount");
	if (it != m_textMap.end()) {
		it->second.first->setString(std::to_string(m_comboScore));
	}
}

void HUDManager::UpdateTimerAmount(const std::string& currTime)
{
	auto itr = m_textMap.find("timerText");

	if (itr != m_textMap.end()) {
		itr->second.first->setString(currTime);
	}
}

void HUDManager::UpdateLongComboScore(int newScore) {
	if (newScore > m_longComboScore) { // Only update if it's truly a new high
		m_longComboScore = newScore;
		auto it = m_textMap.find("longComboAmount");
		if (it != m_textMap.end()) {
			it->second.first->setString(std::to_string(m_longComboScore));
		}
	}
}

void HUDManager::IncrementComboScore(int amount) {
	m_comboScore += amount;
	UpdateComboScore(m_comboScore); // Reuse the update function
}

void HUDManager::DisplayElements(sf::RenderWindow& window)
{

	for (const auto& text : m_textMap) {

		if (text.second.second) {
			window.draw(*text.second.first);
		}
	}

}
