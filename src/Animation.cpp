#include "Animation.h"

#include <SFML/Graphics/RenderWindow.hpp>

Animation::Animation(sf::Texture& texture, sf::Vector2f position, int frameCount, float animDuration)
	: m_sprite(texture), m_frameCount(frameCount), m_duration(animDuration), m_currFrame(0), m_elapsedTime(0.0f)
{

}

bool Animation::IsFinished() const
{
	return false;
}

void Animation::Draw(sf::RenderWindow& window) {

}

void Animation::Update(float dt) {

}