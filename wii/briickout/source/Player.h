/*
 *      Player.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class header for Player objects.
 */

#include <wiisprite.h>
#include "Mover.h"

#ifndef PLAYER_H
#define PLAYER_H

using namespace wsp;

class Player : public Mover {
public:

	// Constructors and destructor

	Player();						// default constructor
	~Player();						// destructor

	// Initializer

	void spawn();

	// Operations

	// Pushes the object.
	void pushLeft();
	void pushRight();
	void pushUp();
	void pushDown();

	void Move();
};

#endif
