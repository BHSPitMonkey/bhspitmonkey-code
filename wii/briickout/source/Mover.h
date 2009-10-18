/*
 *      Mover.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for Mover objects.  A Mover is any in-game entity that
 * 		moves (with 2D physics).  Players and Balls will both be
 * 		types of Movers.
 */

#include <wiisprite.h>

#ifndef MOVER_H
#define MOVER_H

using namespace wsp;

class Mover {
public:

	// Constructors and destructor

	Mover();		// default constructor
	~Mover();		// destructor

	// Initializer

	void spawn(Rectangle rect, GXColor color, int x=320, int y=240);

	// Accessors

	float getXveloc();
	float getYveloc();
	int getXcoord();
	int getYcoord();
	Rectangle * getRect();

	// Operations

	void horizontalBounce();	// Reverses X movement
	void verticalBounce();		// Reverses Y movement
	bool CollidesWith(Mover * otherMover);
	bool CollidesWith(Rectangle * otherRect, int other_x=0, int other_y=0);
	int Move();					// Recalculate position
	void Draw();

	// Properties

	bool gloss;		// True if object should appear glossy

protected:

	// Variables to hold current position
	int x_coord;
	int y_coord;

	// Variables to hold current velocity
	float x_veloc;
	float y_veloc;
	float max_x_speed;
	float max_y_speed;

	// Drawing objects
	Rectangle theRect;
	Quad theQuad;
	Quad glossQuad;

};

#endif
