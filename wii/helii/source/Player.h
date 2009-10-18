/*
 *      Player.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class header for Player objects.
 */

#include <wiisprite.h>
#include "SmokeTrail.h"

#ifndef PLAYER_H
#define PLAYER_H

#define MAX_VELOCITY 5
#define GRAVITATION .2
#define THRUST (2.5 * GRAVITATION)

using namespace wsp;

class Player {

public:

	// Constructors and destructor
	Player();		// default constructor
	~Player();		// destructor

	// Initializer
	void spawn();

	// Accessors
	int GetY();

	// Tests
	bool CollidesWith(const Rectangle * rect, f32 x=0, f32 y=0);

	// Operations
	void thrust();	// Accelerate the player up
	void Move();	// Recalculate position
	void Draw();	// Draw the player to the screen

protected:

	int y_coord;	// Vertical position
	float y_veloc;	// Vertical velocity

	// Drawing objects
	Image heliImage;
	Sprite heliSprite;
	
	Image fireImageSheet;
	Sprite fireSprite;
	
	Image smokeImage;
	Sprite smokeSprites[5];
	
	SmokeTrail theSmokeTrail;

};

#endif
