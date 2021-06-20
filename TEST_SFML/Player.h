#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player
{
public:
	Player();
	bool lookRight, onBlock;
	float xvel, yvel, xpos, ypos;
	void update(bool,bool,bool,bool);
	void collide();
	sf::Vector2f getPosition();
};

