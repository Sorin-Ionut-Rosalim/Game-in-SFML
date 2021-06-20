#include "Player.h"
#include <iostream>

Player::Player()
{
	xvel = 0;
	yvel = 0;
	xpos = 0;
	ypos = 24 * 6;
	lookRight = true;
	onBlock = false;
}

void Player::update(bool playerRight, bool playerLeft, bool playerUp, bool playerDown)
{
	if (playerRight) {
		lookRight = true;
		xvel = 1;
	}
	if (playerLeft) {
		lookRight = false;
		xvel = -1;
	}
	if (playerUp) {
		yvel = -1;
		onBlock = false;
	}
	if (playerDown) {
		yvel = 1;

	}
	
	if (!(playerRight || playerLeft)) {
		xvel = 0;
	}
	if (!(playerUp || playerDown)) {
		yvel = 0;
	}

	xpos += xvel;
	if (!onBlock) {
		ypos += yvel;
	}
	else
	{
		yvel = 0;
	}
	
	
	collide();

	
}

void Player::collide() {
	if (ypos > 24*6) {
		onBlock = true;
	}
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f(xpos,ypos);
}
