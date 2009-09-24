/*
 *      Ball.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class header for Ball objects.
 */

#include <wiisprite.h>
#include "Mover.h"
#include "Player.h"

#ifndef BALL_H
#define BALL_H

using namespace wsp;

class Ball : public Mover {
public:

	// Constructors and destructor

	Ball();			// default constructor
	~Ball();		// destructor

	// Initializer

	void spawn(float initialXVelocity);

	// Operations

	void deflectFromPlayer(Player * player);

private:

};  // end class

#endif
