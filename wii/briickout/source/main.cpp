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
#include "bg_circles.h"

// libwiisprite uses wsp as its namespace
using namespace wsp;

// Global variables
unsigned int g_ticks = 0;	// Counts how many frames we've drawn

int main(int argc, char **argv) {

	// Create the game window and initalise the VIDEO subsystem
	GameWindow gwd;
	gwd.InitVideo();

	// Background
	gwd.SetBackground((GXColor){ 33, 33, 33, 255 });
	Image bgImage;
	Sprite bgSprite;
	bgImage.LoadImage(bg_circles, IMG_LOAD_TYPE_BUFFER);
	bgSprite.SetImage(&bgImage);
	bgSprite.SetPosition(0, 0);

	// Initialise Wiimote
	WPAD_Init();

	// Create and spawn the player
	Player firstPlayer;
	firstPlayer.spawn();

	// Create the ball
	Ball theBall;

	// Create/Load Bricks
	Brick bricks[8][5];
	for (int i=0; i<8; i++)
		for (int j=0; j<5; j++)
			bricks[i][j].spawn(20+(75*i), 20+(32*j));

	bool paused = false;

	// This is the game's run loop. It is executed several times per second.
	while(1) {

		// Look for new Wii controllers
		WPAD_ScanPads();

		// Handle controller events
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_HOME)
			break;
		if (!paused) {
			if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_UP)
				firstPlayer.pushLeft();
			if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_DOWN)
				firstPlayer.pushRight();
		}
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_PLUS)
			paused = !paused;
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_2)
			if (theBall.dead)
				theBall.spawn(firstPlayer.getXcoord());

		if (!paused) {

			// Move the player
			firstPlayer.Move();

			// Move and manage the ball, if the ball is alive
			if (theBall.dead == false)		// If the ball is not dead...
				if (theBall.Move() == -1)	// then draw the ball, and if it hits the bottom of the screen...
					theBall.dead = true;	// then kill the ball.

			// Tell the ball where the player is, so that it can react if the two are touching.
			theBall.deflectFromPlayer(&firstPlayer);

		} // end if !paused

		// Draw the background picture
		bgSprite.Draw();

		// Draw, and deflect Ball from, all bricks. Also check to see if the level is completed.
		bool allDead = true;				// Start by assuming all bricks are dead
		for (int i=0; i<8; i++) {			// Then loop through each of the bricks...
			for (int j=0; j<5; j++) {		// ... in both dimensions.
				bricks[i][j].Move();
				theBall.deflectFromBrick(&bricks[i][j]);
				if (!bricks[i][j].isDead())	// If this brick is alive...
					allDead = false;		// then the level is unfinished.
				bricks[i][j].Draw();		// Draw this brick
			}
		}

		// If all bricks are dead, we move on to a new level.
		if (allDead) {

			// Respawn all bricks
			for (int i=0; i<8; i++)
				for (int j=0; j<5; j++)
					bricks[i][j].spawn(20+(75*i), 20+(32*j));

			// Respawn the Player
			firstPlayer.spawn();

			// Disable the ball
			theBall.dead = true;
		}

		if (theBall.dead == false)
			theBall.Draw();			// Draw the ball
		firstPlayer.Draw();			// Draw the first player

		// Write the buffer to the screen and reset it
		gwd.Flush();

		// Increase our count of how many frames have been drawn.
		g_ticks++;
	}

	// The program has finished, so we return to the loader.
	return 0;
}
