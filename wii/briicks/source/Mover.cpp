/*
 *      Mover.cpp
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for Mover objects.  A Mover is any in-game entity that
 * 		moves (with 2D physics).  Players and Balls will both be
 * 		types of Movers.
 */

#include <wiisprite.h>
#include "Mover.h"

using namespace wsp;

// Default constructor
Mover::Mover() { }

// Destructor
Mover::~Mover() { }

void Mover::spawn(Rectangle rect, GXColor color, int x, int y) {

	x_coord = x;	// Remember where to draw this Mover.
	y_coord = y;	// Remember where to draw this Mover.
	x_veloc = 0;	// Reset x velocity.
	y_veloc = 0;	// Reset y velocity.

	theRect = rect;
	theQuad.SetFillColor(color);
}

// Velocity getters
float Mover::getXveloc() {
	return x_veloc;
}
float Mover::getYveloc() {
	return y_veloc;
}

// Position getters
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

// Collision with top/bottom occurred
void Mover::horizontalBounce() {
	x_veloc = -x_veloc;
	// TODO: Play a beep!
}

// Collision with top/bottom occurred
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

// Draws the mover
int Mover::Draw() {

	// Return value.  Will be -1 for bottom wall collide, 0 otherwise
	int retValue = 0;

	// Make sure mover doesn't leave TV screen (collide with edges)
	if (x_coord+theRect.width > 640) {			// Collided with screen right
		x_coord = 640-theRect.width;
		horizontalBounce();
	}
	else if (x_coord < 0) {		// Collided with screen left
		x_coord = 0;
		horizontalBounce();
	}
	if (y_coord+theRect.height > 480) {			// Collided with screen bottom
		y_coord = 480;
		verticalBounce();
		retValue = -1;
	}
	else if (y_coord < 0) {
		y_coord = 0;
		verticalBounce();
	}
	
	// Move the position, according to velocity.
	x_coord += x_veloc;
	y_coord += y_veloc;

	// Redefine the drawing rectangle according to mover position.
	theRect.x = x_coord;
	theRect.y = y_coord;
	theQuad.SetRectangle(&theRect);

	theQuad.Draw();

	return retValue;
}
