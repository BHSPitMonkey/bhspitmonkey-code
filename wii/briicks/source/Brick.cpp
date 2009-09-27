/*
 *		Brick.cpp
 *
 *		Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 *
 *		Class for Brick objects.
 */

#include <wiisprite.h>
#include <ctime>
#include "Brick.h"

using namespace wsp;

// Default constructor
Brick::Brick() {

	// Brick width and height
	theRect.width = 64;
	theRect.height = 20;
	
	x_veloc = 0;
	y_veloc = 0;
}

// Constructor + Spawn at (x,y)
Brick::Brick(int x, int y) {

	Brick();		// Call the default constructor
	spawn(x, y);	// Spawn the brick, too
}

// Destructor
Brick::~Brick() { }

// Reset this brick's position, bring it to life, and give it a new color
void Brick::spawn(int x, int y) {

	x_coord = x;	// Remember where to draw this Brick.
	y_coord = y;	// Remember where to draw this Brick.
	dead = false;

	// Bricks should be... random-colored!
	srand(x+y);		// Seed the random number generator with the brick's position
	int r = 100 + rand()%155;
	int g = 100 + rand()%155;
	int b = 100 + rand()%155;
	theQuad.SetFillColor((GXColor){ r, g, b, 255 });
}

// Returns True if the brick is dead
bool Brick::isDead() {

	return dead;
}

// Call this method if the brick gets hit
void Brick::wasHit() {

	dead = true;
}

// Draw the brick (if it's alive)
void Brick::Draw() {

	if (!dead)
		Mover::Draw();
}
