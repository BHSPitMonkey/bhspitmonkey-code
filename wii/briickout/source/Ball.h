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
#include "Brick.h"

#ifndef BALL_H
#define BALL_H

using namespace wsp;

class Ball : public Mover {
public:

	// Constructors and destructor

	Ball();		// default constructor
	~Ball();	// destructor

	// Initializer

	void spawn(int playerXcoord);

	// Operations

	void deflectFromPlayer(Player * player);
	void deflectFromBrick(Brick * brick);

	int Move();
	
	// Properties
	
	bool dead;
	bool unstoppable;
};

#endif
