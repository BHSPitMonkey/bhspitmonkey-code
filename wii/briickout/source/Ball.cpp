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

	// Ball's maximum y speed
	max_x_speed = 10;

	// The Ball should be white
	theQuad.SetFillColor((GXColor){ 255, 255, 255, 255 });

	// Ball is initially dead (absent)
	dead = true;

	// Unstoppable mode is off by default
	unstoppable = false;
}

// Destructor
Ball::~Ball() { }

// Reset the ball's location and speed
void Ball::spawn(int playerXcoord) {

	// Reset the Ball's position (centered)
	x_coord = playerXcoord + 32 - 10;
	y_coord = 200;

	// Reset the Ball's velocity (horizontal, with passed X velocity)
	x_veloc = 0;
	y_veloc = 3;

	// Reset Ball's rotation
	theQuad.SetRotation(0);

	// Bring the ball to life
	dead = false;
}

// Call repeatedly to 'react' to player's paddle.
void Ball::deflectFromPlayer(Player * player) {

	// Don't do anything if the ball is dead.
	if (dead)
		return;

	// This assignment only happens once.
	static unsigned int collisionTimer = 0;

	// Only act if there hasn't been a collision for a while.
	if (collisionTimer == 0) {
	
		if ( CollidesWith(player) ) {

			verticalBounce();
			// Get some x velocity from player
			x_veloc += player->getXveloc()/2;

			// Wait a while 'till the next collision
			collisionTimer = 20;
		}
	}
	else collisionTimer--;
}

void Ball::deflectFromBrick(Brick * brick) {

	// Don't do anything if the ball is dead.
	if (dead)
		return;

	// If the brick is alive and touching the ball
	if ( !brick->isDead() && CollidesWith(brick) ) {

		if (!unstoppable)		// If "unstoppable" is disabled
			verticalBounce();	// reverse the ball direction.
		brick->wasHit();		// Tell the brick it was hit.
	}
}

int Ball::Move() {

	theQuad.SetRotation( theQuad.GetRotation() + x_veloc);

	return Mover::Move();
}
