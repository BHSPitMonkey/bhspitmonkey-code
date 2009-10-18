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

	// Player's y position (never changes)
	y_coord = 440;

	// Player should be gray
	theQuad.SetFillColor((GXColor){ 100, 100, 100, 255 });
}

// Destructor
Player::~Player() { }

// Reset the player's position and velocity
void Player::spawn() {

	// Default position for a Player (centered)
	x_coord = 320; // - (theRect.width/2);

	// Reset Player velocity to 0
	x_veloc = 0;
	y_veloc = 0;

	max_x_speed = 30;
}

// Moves the player left
void Player::pushLeft() {
	x_veloc--;
}

// Moves the player right
void Player::pushRight() {
	x_veloc++;
}

// Reposition the player
void Player::Move() {

	// Bring velocity down (closer to zero) each tick.
	if (x_veloc < 0) x_veloc += 0.25;
	if (x_veloc > 0) x_veloc -= 0.25;

	Mover::Move();
}

