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

// libwiisprite uses wsp as it's namespace
using namespace wsp;

int main(int argc, char **argv) {

	// Create the game window and initalise the VIDEO subsystem
	GameWindow gwd;
	gwd.InitVideo();
	
	gwd.SetBackground((GXColor){ 0, 30, 0, 255 });

	// Initialise Wiimote
	WPAD_Init();

	// Enable SD card stuff
	fatInitDefault();

	Quad net;
	net.SetPosition(320-2, 0);
	net.SetWidth(4);
	net.SetHeight(480);
	net.SetFillColor((GXColor){ 0, 255, 0, 255 });

	ScoreBox firstScoreBox(35, 10, 250);
	ScoreBox secondScoreBox(355, 10, 250);

	Player firstPlayer;
	firstPlayer.spawn(0, 100);

	Player secondPlayer;
	secondPlayer.spawn(510, 610);

	Ball theBall;
	theBall.spawn(-3);

	uint ticks;

	bool AImode = true;

	while(1)
	{
		WPAD_ScanPads();

		// Handle controller events

		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_HOME)
			break;

		// Player 1 Controller
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_DOWN)
			firstPlayer.pushDown();
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_UP)
			firstPlayer.pushUp();
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_LEFT)
			firstPlayer.pushLeft();
		if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_RIGHT)
			firstPlayer.pushRight();

		// Player 2 Controller
		
		if(WPAD_ButtonsDown(WPAD_CHAN_1)&WPAD_BUTTON_PLUS)
			AImode = !AImode;

		if ( AImode ) {
			// Player 2 AI
			if (theBall.getYcoord()+10 < secondPlayer.getYcoord()+32)
				secondPlayer.pushUp();
			else if (theBall.getYcoord()+10 > secondPlayer.getYcoord()+32)
				secondPlayer.pushDown();
		}
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

		net.Draw();
		firstScoreBox.Draw();
		secondScoreBox.Draw();

		// Draw the ball, then react if it bounced off the side of the screen.
		switch (theBall.Draw()) {

			// If the ball hit the left side of the screen...
			case -1:
				// Player 1 fail
				if (secondScoreBox.incrementScore() == false) return 0;
				theBall.spawn(-3);	// Reset ball going left
				firstPlayer.spawn(0, 100);
				break;
			// If the ball hit the right side of the screen...
			case +1:
				// Player 2 fail
				if (firstScoreBox.incrementScore() == false) return 0;
				theBall.spawn(3);	// Reset ball going rightward
				secondPlayer.spawn(510, 610);
				break;
			default:
				// No fail
				break;
		}

		firstPlayer.Draw();
		secondPlayer.Draw();

		theBall.deflectFromPlayer(&firstPlayer);
		theBall.deflectFromPlayer(&secondPlayer);

		gwd.Flush();

		ticks++;
	}
	return 0;
}
