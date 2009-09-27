/*
 *      main.cpp
 * 
 * 		Briickout
 * 		A very simple Breakout-style game for the Wii.
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		This is the main source file for Briicks, a Breakout-like game
 * 		for Wii homebrew that uses some fun basic physics.
 * 
 * 		Looking at the other source files in this directory, the
 * 		classes used should be fairly self-explanatory.
 * 
 * 		This program depends on libwiisprite for drawing, but you
 * 		should be able to port this code for other drawing libraries
 * 		pretty easily. (Look for Draw() methods and Rectangle/Quad
 * 		instances.)
 * 
 * 		More details should be in README.
 */

#include <wiiuse/wpad.h>
#include <wiisprite.h>
#include "Player.h"
#include "Ball.h"

// libwiisprite uses wsp as its namespace
using namespace wsp;

// Global variables
unsigned int g_ticks = 0;	// Counts how many frames we've drawn

int main(int argc, char **argv) {

	// Create the game window and initalise the VIDEO subsystem
	GameWindow gwd;
	gwd.InitVideo();
	
	gwd.SetBackground((GXColor){ 0, 0, 0, 255 });

	// Initialise Wiimote
	WPAD_Init();

	// Create and spawn the player
	Player firstPlayer;
	firstPlayer.spawn();

	// Create and spawn the ball near the player
	Ball theBall;
	theBall.spawn(firstPlayer.getXcoord());

	// Create/Load Bricks
	Brick bricks[8][5];
	for (int i=0; i<8; i++)
		for (int j=0; j<5; j++)
			bricks[i][j].spawn(20+(75*i), 20+(32*j));

	// This is the game's run loop. It is executed several times per second.
	while(1) {

		// Look for new Wii controllers
		WPAD_ScanPads();

		// Handle controller events
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_HOME)
			break;
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_LEFT)
			firstPlayer.pushLeft();
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_RIGHT)
			firstPlayer.pushRight();

		// Handle the objects
		
		// Draw the ball, and react if it reached the bottom of the screen.
		if (theBall.Draw() == -1) {
			// The player has failed!
			theBall.spawn(firstPlayer.getXcoord());	// Respawn the ball
		}

		// Draw the first player
		firstPlayer.Draw();

		// Tell the ball where the player is, so that it can react
		// if the two are touching.
		theBall.deflectFromPlayer(&firstPlayer);

		// Draw, and deflect Ball from, all bricks. Also check 
		// to see if the level is completed.
		bool allDead = true;				// Start by assuming all bricks are dead
		for (int i=0; i<8; i++) {			// Then loop through each of the bricks...
			for (int j=0; j<5; j++) {		// ... in both dimensions.

				bricks[i][j].Draw();		// Draw this brick
				theBall.deflectFromBrick(&bricks[i][j]);
				if (!bricks[i][j].isDead())	// If this brick is alive...
					allDead = false;		// then the level is unfinished.
			}
		}
		
		// At this point, if any of the bricks were alive, allDead will
		// be set to false now. If none were alive, allDead will still be true.

		// If all bricks are dead, we move on to a new level.
		if (allDead) {

			// Respawn all bricks
			for (int i=0; i<8; i++)
				for (int j=0; j<5; j++)
					bricks[i][j].spawn(20+(75*i), 20+(32*j));

			// Respawn the Player
			firstPlayer.spawn();

			// Respawn the ball
			theBall.spawn(firstPlayer.getXcoord());
		}

		// Draw the buffer to the screen and reset it.
		gwd.Flush();

		// Increase our count of how many frames have been drawn.
		g_ticks++;
	}

	// The program has finished, so we return to the loader.
	return 0;
}
