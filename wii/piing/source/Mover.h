/*
 *      Mover.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for Mover objects.  A Mover is any in-game entity that
 * 		moves (with 2D physics).  Movers and Balls will both be
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

	// Initializers

	void spawn(Rectangle rect, GXColor color, int xmin=0, int xmax=640, int x=320, int y=240);

	// Accessors

	float getXveloc();
	float getYveloc();
	int getXcoord();
	int getYcoord();
	Rectangle * getRect();

	// Mover operations

	void horizontalBounce();	// Reverses X movement
	void verticalBounce();		// Reverses Y movement
	bool CollidesWith(Mover * otherMover);
	bool CollidesWith(Rectangle * otherRect, int other_x=0, int other_y=0);
	int Draw();					// Recalculate position and redraw

protected:

	// Variables to hold current position
	int x_coord;
	int y_coord;

	// Variables to hold current velocity
	float x_veloc;
	float y_veloc;

	// Variables to hold x position bounds
	int x_min;
	int x_max;
   
	Rectangle theRect;
	Quad theQuad;

};  // end class

#endif
