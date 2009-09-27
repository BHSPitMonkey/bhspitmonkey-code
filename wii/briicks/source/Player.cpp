/*
 *      Player.cpp
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for Player objects.
 */

#include <wiisprite.h>
#include "Player.h"

using namespace wsp;

// Default constructor
Player::Player() {

	// Player width and height
	theRect.width = 64;
	theRect.height = 20;

	// Players should be green
	theQuad.SetFillColor((GXColor){ 0, 255, 0, 255 });
}

// Destructor
Player::~Player() { }

// Reset the player's position and velocity
void Player::spawn() {

	// Default position for a Player (centered)
	x_coord = 320; // - (theRect.width/2);
	y_coord = 460;

	// Reset Player velocity to 0
	x_veloc = 0;
	y_veloc = 0;
}

// Moves the player left
void Player::pushLeft() {
	if (x_veloc > -30)
		x_veloc--;
}

// Moves the player right
void Player::pushRight() {
	if (x_veloc < 30)
		x_veloc++;
}

// Draws the player
void Player::Draw() {

	// Bring velocity down (closer to zero) each tick.
	if (x_veloc < 0) x_veloc += 0.25;
	if (x_veloc > 0) x_veloc -= 0.25;

	Mover::Draw();
}
