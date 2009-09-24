/*
 *      Ball.cpp
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for Ball objects.
 */

#include <wiisprite.h>
#include "Ball.h"
#include "Player.h"

using namespace wsp;

// Default constructor
Ball::Ball() {

	// Ball's default size
	theRect.width = 20;
	theRect.height = 20;

	// Set the bounding area for the Ball (represents the entire screen)
	x_min = 0;
	x_max = 640;

	// The Ball should be white
	theQuad.SetFillColor((GXColor){ 255, 255, 255, 255 });
}

// Destructor
Ball::~Ball() { }

// Reset the ball's location and speed
void Ball::spawn(float initialXVelocity) {

	// Reset the Ball's position (centered)
	x_coord = 320 - (theRect.width/2);
	y_coord = 240 - (theRect.height/2);

	// Reset the Ball's velocity (horizontal, with passed X velocity)
	x_veloc = initialXVelocity;
	y_veloc = 0;
}

// Call repeatedly to 'react' to player's paddle.
void Ball::deflectFromPlayer(Player * player) {

	static unsigned int collisionTimer = 0;

	if (collisionTimer == 0) {
	
		if ( CollidesWith(player) ) {

			horizontalBounce();
			// get y velocity from player
			y_veloc += player->getYveloc()/2;

			// Wait a while 'till the next collision
			collisionTimer = 20;

		}
	}
	else collisionTimer--;
}
