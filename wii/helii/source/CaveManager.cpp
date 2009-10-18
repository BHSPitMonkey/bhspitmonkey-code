/*
 *      CaveManager.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class implementation for CaveManager objects.
 */

#include <wiisprite.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "globals.h"
#include "CaveManager.h"

using namespace wsp;

extern std::ofstream logFile;
extern unsigned int g_gameTime;

// Default constructor
CaveManager::CaveManager() { 

	// Initially, first is the first index in the array.
	first = 0;
}

// Destructor
CaveManager::~CaveManager() { }

// Reset all columns, start a new game
void CaveManager::resetAll() {

	// Reset caveTop and currentCaveHeight to default values
	caveTop = INITIAL_CAVE_TOP;
	caveSpacing = INITIAL_CAVE_SPACING;

	// Go through every roof and ground column, resetting each.
	float x = -MARGIN;
	for (int i=0; i<NUM_COLUMNS; i++) {
		roof[i].spawn(false, x + (i * COL_WIDTH), caveTop);
		ground[i].spawn(true, x + (i * COL_WIDTH), CAVE_HEIGHT - (caveTop + caveSpacing));
	}
	
	first = 0;

	// Spawn obstacles
	for (int i=0; i<NUM_OBSTACLES; i++) {
		obstacles[i].spawnObstacle(	1280 + (i * OBSTACLE_SPACING), 
									caveTop + 20 + (i * (caveSpacing/2.0)), 
									caveSpacing/4.0);
	}
}

bool CaveManager::CollidesWithPlayer() {

	// Define which columns to compare
	u8 start = first;
	logFile << first << "\n";
	u8 end = (first + (NUM_COLUMNS / 3)) % NUM_COLUMNS;

	// Loop through these columns
	for (int i = start; i != end; i = (i+1)%NUM_COLUMNS) {
		
		if (roof[i].CollidesWithPlayer()) {		// Check the roof

#ifdef DEBUGMODE
			logFile << "Collision with roof, column " << ((i - first) % NUM_COLUMNS) << ".\n";
#endif

			return true;
		}
		if (ground[i].CollidesWithPlayer()) {	// Check the ground

#ifdef DEBUGMODE
			logFile << "Collision with ground, column " << ((i - first) % NUM_COLUMNS) << ".\n";
#endif

			return true;
		}
	}
	
	// Now check all the obstacle columns for collision
	for (int i=0; i<NUM_OBSTACLES; i++) {

		if (obstacles[i].CollidesWithPlayer()) {
#ifdef DEBUGMODE
			logFile << "Player hit obstacle " << i << ".\n";
#endif
			return true;
		}
	}

	// No collisions were found
	return false;
}

// Shift and update the cave manager.
void CaveManager::update() {

	// Update the roof and ground
	for (int i=0; i<NUM_COLUMNS; i++) {
		roof[i].pushLeft(CAVE_SPEED);
		ground[i].pushLeft(CAVE_SPEED);

		// If this column is too far off-screen
		if (roof[i].getXpos() <= -MARGIN - 1) {

			// Update the caveTop position interestingly yet safely
			caveTop += (int)(50 * cos(g_ticks / 50)) % MAX_CAVE_TOP_CHANGE;
			if (caveTop < 50)	// Bounds check
				caveTop = 50;
			else if (caveTop + caveSpacing > CAVE_HEIGHT - 50)
				caveTop = CAVE_HEIGHT - (50 + caveSpacing);

			// Update the caveSpacing to make the cave narrower, more difficult over time
			if (caveSpacing > MIN_CAVE_SPACING)
				caveSpacing -= .1;					// Make narrow the cave
			else
				caveSpacing = INITIAL_CAVE_SPACING;	// Make the cave wide again

			// Prepare to move the first columns to the last column positions
			float newX = roof[i].getXpos() + (NUM_COLUMNS * COL_WIDTH);

			// Respawn the first columns at the right side of screen with updated sizes
			roof[i].spawn(false, newX, caveTop);
			ground[i].spawn(true, newX, CAVE_HEIGHT - (caveTop + caveSpacing));

			first = (i+1) % NUM_COLUMNS;	// Change the index of the first column
		} // end if column is off-screen
	} // end for all roof/ground columns

	// Update the obstacles
	for (int i=0; i<NUM_OBSTACLES; i++) {

		// Push the obstacle left
		obstacles[i].pushLeft(CAVE_SPEED);
		
		// If too far off-screen...
		if (obstacles[i].getXpos() <= -MARGIN - 1) {

			// Prepare to move the first columns to the last column positions
			float newH = caveSpacing / 4.0;
			float newX = obstacles[i].getXpos() + (NUM_OBSTACLES * OBSTACLE_SPACING);
			float newY = caveTop-(newH/2.0) + abs(((int)(caveSpacing * cos(g_ticks / 1)) % (int)caveSpacing));
			
			// Respawn obstacle at new location
			obstacles[i].spawnObstacle(newX, newY, newH);
		}
	}
}

void CaveManager::Draw() {

	// Draw all the columns
	for (int i=0; i<NUM_COLUMNS; i++) {
		roof[i].Draw();
		ground[i].Draw();
	}

	// Draw all the obstacles
	for (int i=0; i<NUM_OBSTACLES; i++) {
		obstacles[i].Draw();
	}
}
