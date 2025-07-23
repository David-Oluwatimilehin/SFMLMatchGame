#pragma once

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
class StateMachine;
class HUDManager;
namespace sf {
	class RenderWindow;
	
}

class MenuState final : public State {
private:
	
	sf::IntRect* m_rect;
	sf::Clock* m_clock;

	std::unique_ptr<sf::Texture> m_texture;
	std::unique_ptr<sf::Sprite> m_background;
	std::unique_ptr<HUDManager>m_menuManager;
public:
	MenuState(StateMachine& machine, sf::RenderWindow& window, bool shouldReplace = true);

	void Pause() override;
	void Resume() override;

	void Update() override;
	void Draw() override;

};