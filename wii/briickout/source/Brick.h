/*
 *		Brick.cpp
 *
 *		Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 *
 *		Header file for Brick objects.
 */

#include <wiisprite.h>
#include "Mover.h"

#ifndef BRICK_H
#define BRICK_H

using namespace wsp;

class Brick : public Mover {
public:

	// Constructors and destructor

	Brick();				// Default constructor
	Brick(int x, int y);	// Constructor + Spawn call
	~Brick();				// Destructor

	// Initializer

	void spawn(int x, int y);

	// Accessors

	bool isDead();			// Returns brick status

	// Operations

	void wasHit();			// Called when hit by ball
	void Draw();

protected:

	bool dead;
	// Quad glossQuad;

};

#endif
