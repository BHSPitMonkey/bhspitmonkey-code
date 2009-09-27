/*
 *      main.cpp
 * 
 * 		Piing
 * 		A very simple Pong-style game for the Wii.
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		This is the main source file for Piing, a Pong-like game
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
#include <fat.h>
#include "Player.h"
#include "Ball.h"
#include "ScoreBox.h"

// libwiisprite uses wsp as its namespace
using namespace wsp;

// Global variables
unsigned int g_ticks = 0;	// Counts how many frames we've drawn

int main(int argc, char **argv) {

	// Create the game window and initalise the VIDEO subsystem
	GameWindow gwd;
	gwd.InitVideo();
	
	gwd.SetBackground((GXColor){ 0, 30, 0, 255 });

	// Initialise Wiimote
	WPAD_Init();

	// Enable SD card stuff
	fatInitDefault();

	// Create a rectangle representing the net and set its properties
	Quad net;
	net.SetPosition(320-2, 0);
	net.SetWidth(4);
	net.SetHeight(480);
	net.SetFillColor((GXColor){ 0, 255, 0, 255 });

	// Create the two score boxes (x position, y position, width)
	ScoreBox firstScoreBox(35, 10, 250);
	ScoreBox secondScoreBox(355, 10, 250);

	// Create and spawn the first player
	Player firstPlayer;
	firstPlayer.spawn(0, 100);

	// Create and spawn the second player
	Player secondPlayer;
	secondPlayer.spawn(510, 610);

	// Create and spawn the ball (-3 seems like a good initial speed!)
	Ball theBall;
	theBall.spawn(-3);

	// Player 2 A.I. is turned on by default
	bool AImode = true;

	// This is the game's run loop. It is executed several times per second.
	while(1) {

		// Look for new Wii controllers
		WPAD_ScanPads();

		// Handle controller events

		// Quit the game (break out of the runloop) if HOME is pressed
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_HOME)
			break;

		// Player 1 Controls
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_DOWN)
			firstPlayer.pushDown();
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_UP)
			firstPlayer.pushUp();
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_LEFT)
			firstPlayer.pushLeft();
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_RIGHT)
			firstPlayer.pushRight();

		// Player 2 Controls
		if(WPAD_ButtonsDown(WPAD_CHAN_1)&WPAD_BUTTON_PLUS)
			AImode = !AImode;
		// If AI is enabled, control Player 2 using the following code.
		if ( AImode ) {
			// Player 2 AI
			if (theBall.getYcoord()+10 < secondPlayer.getYcoord()+32)
				secondPlayer.pushUp();
			else if (theBall.getYcoord()+10 > secondPlayer.getYcoord()+32)
				secondPlayer.pushDown();
		}
		// If AI is disabled, let the Wii remote control Player 2.
		else {
			if(WPAD_ButtonsHeld(WPAD_CHAN_1)&WPAD_BUTTON_DOWN)
				secondPlayer.pushDown();
			if(WPAD_ButtonsHeld(WPAD_CHAN_1)&WPAD_BUTTON_UP)
				secondPlayer.pushUp();
			if(WPAD_ButtonsHeld(WPAD_CHAN_1)&WPAD_BUTTON_LEFT)
				secondPlayer.pushLeft();
			if(WPAD_ButtonsHeld(WPAD_CHAN_1)&WPAD_BUTTON_RIGHT)
				secondPlayer.pushRight();
		}

		// Handle all the game objects

		net.Draw();					// Draw the net
		firstScoreBox.Draw();		// Draw the first score box
		secondScoreBox.Draw();		// Draw the second score box

		// Draw the ball, then react if it bounced off the side of the screen.
		switch (theBall.Draw()) {

			// If the ball hit the left side of the screen...
			case -1:
				// Player 1 has failed
				if (secondScoreBox.incrementScore() == false) return 0;
				theBall.spawn(-3);	// Reset ball going left
				firstPlayer.spawn(0, 100);
				break;

			// If the ball hit the right side of the screen...
			case +1:
				// Player 2 has failed
				if (firstScoreBox.incrementScore() == false) return 0;
				theBall.spawn(3);	// Reset ball going rightward
				secondPlayer.spawn(510, 610);
				break;

			// If neither of the above cases happened...
			default:
				// Nobody failed! :)
				break;
		}

		firstPlayer.Draw();		// Draw Player 1
		secondPlayer.Draw();	// Draw Player 2

		// Tell the ball where each player is, so that it can react
		// to them if they are touching.
		theBall.deflectFromPlayer(&firstPlayer);
		theBall.deflectFromPlayer(&secondPlayer);

		// Draw the buffer to the screen and reset it.
		gwd.Flush();

		// Increase our count of how many frames have been drawn.
		g_ticks++;
	}
	
	// The program has finished, so we return to the loader.
	return 0;
}
