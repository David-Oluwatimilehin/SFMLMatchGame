#pragma once

#include "State.h"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <SFML/System/Clock.hpp>


class StateMachine;
class BackgroundManager;
class HUDManager;
namespace sf {
	class RenderWindow;
}

class MenuState final : public State {
private:
	
	sf::Clock m_clock;
	sf::IntRect* m_rect;

	BackgroundManager* m_menuBackground;
	std::unique_ptr<HUDManager>m_menuManager;
public:
	MenuState(StateMachine& machine, sf::RenderWindow& window, bool shouldReplace = true);
	~MenuState();

	void Pause() override;
	void Resume() override;

	void Update() override;
	void Draw() override;

};