#pragma once

#include <memory>
#include <vector>

class Animation;

namespace sf {
	class RenderWindow;
}

class AnimationManager
{
private:
	std::vector<std::unique_ptr<Animation>> m_animVec;

public:
	void AddAnimation(std::unique_ptr<Animation> newAnim);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);


};

