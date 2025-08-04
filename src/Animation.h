#pragma once

#include<SFML/Graphics/Sprite.hpp>

namespace sf {
	class RenderWindow;
}

class Animation {
private:
	int m_frameCount;
	int m_currFrame;
	float m_duration;
	float m_elapsedTime;
	sf::Sprite m_sprite;

public:
	Animation(sf::Texture& texture, sf::Vector2f position, int frameCount, float animDuration);

	bool IsFinished() const;
	void Draw(sf::RenderWindow& window);
	void Update(float dt);
};