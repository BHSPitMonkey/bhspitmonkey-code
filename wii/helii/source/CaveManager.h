/*
 *      CaveManager.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class header for CaveManager objects.
 */

#include <wiisprite.h>
#include "Column.h"

#ifndef CAVEMGR_H
#define CAVEMGR_H

#define CAVE_HEIGHT 480
#define NUM_COLUMNS 50
#define NUM_OBSTACLES 2
#define OBSTACLE_SPACING (int)((640.0 + (2.0 * MARGIN)) / NUM_OBSTACLES)
#define CAVE_SPEED 5
#define MARGIN 50
#define COL_WIDTH (int)((640.0 + (2.0 * MARGIN)) / NUM_COLUMNS)
#define INITIAL_CAVE_TOP 50
#define INITIAL_CAVE_SPACING 380
#define MIN_CAVE_SPACING 100
#define MAX_CAVE_TOP_CHANGE 4

using namespace wsp;

class CaveManager {
private:

	friend class Column;				// TODO: Not sure this is needed

	Column roof[NUM_COLUMNS];			// Roof columns
	Column ground[NUM_COLUMNS];			// Ground columns
	Column obstacles[NUM_OBSTACLES];	// Obstacle columns

	float caveTop;			// Holds the y-coordinate for the top of the cave
	float caveSpacing;		// Holds the current height of the cave

	u8 first;				// Index of the first column

public:

	// Constructors and destructor
	CaveManager();			// default constructor
	~CaveManager();			// destructor

	// Initializer
	void resetAll();		// All columns to starting positions!

	bool CollidesWithPlayer();

	// Operations
	void update();	// Recalculate positions
	void Draw();	// Draw the columns to the screen

};

#endif
