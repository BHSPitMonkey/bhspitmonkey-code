/*
 *      Mover.cpp
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for Mover objects.  A Mover is any in-game entity that
 * 		moves (with 2D physics).  Movers and Balls will both be
 * 		types of Movers.
 */

#include <wiisprite.h>
#include "Mover.h"

using namespace wsp;

void Mover::spawn(Rectangle rect, GXColor color, int xmin, int xmax, int x, int y) {

	x_coord = xmin + (xmax-xmin)/2;		// Remember where to draw this Mover.
	y_coord = 240;		// Remember where to draw this Mover.
	x_veloc = 0;
	y_veloc = 0;
	x_min = xmin;		// Mover's minimum X position
	x_max = xmax;		// Mover's maximum X position
	
	theRect = rect;
	theQuad.SetFillColor(color);

	// button_sprite.SetPosition(x, y);	// Tell the sprite where to draw itself
}

// Default constructor
Mover::Mover() { }

// Destructor
Mover::~Mover() { }

// Coordinate getters
float Mover::getXveloc() {
	return x_veloc;
}
float Mover::getYveloc() {
	return y_veloc;
}
int Mover::getXcoord() {
	return x_coord;
}
int Mover::getYcoord() {
	return y_coord;
}

// Rectangle getter
Rectangle * Mover::getRect() {
	return &theRect;
}

// Reverses horizontal velocity. Call this when we collide with the floor/ceiling.
void Mover::horizontalBounce() {
	x_veloc = -x_veloc;
	// TODO: Play a beep!
}

// Reverses vertical velocity. Call this when we collide with a paddle side.
void Mover::verticalBounce() {
	y_veloc = -y_veloc;
	// TODO: Play a beep!
}

// Returns true if this Mover object collides with some other Mover object
bool Mover::CollidesWith(Mover * otherMover) {
	return CollidesWith(otherMover->getRect(), otherMover->getXcoord(), otherMover->getYcoord());	
}

// Returns true if this Mover's rectangle collides with another given rectangle
bool Mover::CollidesWith(Rectangle * otherRect, int other_x, int other_y) {

	int tw = theRect.width;
	int th = theRect.height;
	int rw = otherRect->width;
	int rh = otherRect->height;
	if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) {
	return false;
	}
	int tx = x_coord;
	int ty = y_coord;
	int rx = other_x;
	int ry = other_y;

	rw = rw+rx;
	rh = rh+ry;
	tw = tw+tx;
	th = th+ty;

	if ((rw < rx || rw > tx) && (rh < ry || rh > ty) &&
	(tw < tx || tw > rx) &&	(th < ty || th > ry))
		return true;
	else
		return false;
}

// Draws this Mover
int Mover::Draw() {

	// Return value.  Will be -1 for left wall collide, +1 for right wall, 0 otherwise
	int retValue = 0;

	// Make sure mover doesn't leave TV screen (collide with edges)
	if (x_coord > x_max) {			// Collided with screen right
		x_coord = x_max;
		horizontalBounce();
		retValue = 1;
	}
	else if (x_coord < x_min) {		// Collided with screen left
		x_coord = x_min;
		horizontalBounce();
		retValue = -1;
	}
	if (y_coord > 480) {			// Collided with screen bottom
		y_coord = 480;
		verticalBounce();
	}
	else if (y_coord < 0) {			// Collided with screen top
		y_coord = 0;
		verticalBounce();
	}

	// Adjust the position, according to velocity.
	x_coord += x_veloc;
	y_coord += y_veloc;

	// Redefine the drawing rectangle according to mover position.
	theRect.x = x_coord;
	theRect.y = y_coord;
	theQuad.SetRectangle(&theRect);

	// Draw the Quad
	theQuad.Draw();

	return retValue;
}
