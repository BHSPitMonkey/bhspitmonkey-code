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

void Player::spawn(int xmin, int xmax) {

	// Default position for a Player (centered within its bounding area)
	x_coord = xmin + (xmax-xmin)/2;
	y_coord = 240 - (theRect.height/2);

	// Reset Player velocity to 0
	x_veloc = 0;
	y_veloc = 0;

	// Remember the parameters given
	x_min = xmin;		// Mover's minimum X position
	x_max = xmax;		// Mover's maximum X position

}

// Default constructor
Player::Player() { 

	// Player width and height
	theRect.width = 32;
	theRect.height = 64;

	// Players should be green
	theQuad.SetFillColor((GXColor){ 0, 255, 0, 255 });
}

// Destructor
Player::~Player() { }


// Player operations:

// Moves the Player
void Player::pushDown() {
	y_veloc++;
}
void Player::pushUp() {
	y_veloc--;
}
void Player::pushLeft() {
	x_veloc--;
}
void Player::pushRight() {
	x_veloc++;
}

void Player::Draw() {

	// Bring velocity down (greater) each tick.
	if (x_veloc < 0) x_veloc += 0.25;
	if (x_veloc > 0) x_veloc -= 0.25;
	if (y_veloc < 0) y_veloc += 0.25;	// if the object is moving in the -y direction (up)
	if (y_veloc > 0) y_veloc -= 0.25;

	Mover::Draw();
	
}
