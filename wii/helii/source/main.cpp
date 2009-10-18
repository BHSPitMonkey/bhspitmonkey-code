/*
 *      main.cpp
 * 
 * 		Helii
 * 		A helicopter flying game for the Wii.
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		This is the main source file for Helii.
 * 
 * 		More details should be in README.
 */

#include <wiiuse/wpad.h>
#include <wiisprite.h>
#include <fat.h>
#include <iostream>
#include <fstream>
#include "globals.h"
#include "Player.h"
#include "CaveManager.h"

// #define DEBUGMODE

// libwiisprite uses wsp as its namespace
using namespace wsp;

// Global variables
unsigned int g_ticks = 0;			// Counts how many frames we've drawn, period
unsigned int g_gameTime;			// Counts how many frames have passed in current game
unsigned int g_currentStateTime;	// Counts how many frames have passed in current state
GameState g_currentState;			// Decides what state or mode the game is in
Player thePlayer;
CaveManager theCave;
std::ofstream logFile;

void setGameState(GameState newState) {

	// First things first
	g_currentState = newState;

	// Reset the timer
	g_currentStateTime = 0;

	// Do certain things when these changes happen
	switch (newState) {

		// When changing to the Main Menu state
		case MAIN_MENU_STATE:
		
			// Respawn the player and the cave
			thePlayer.spawn();
			theCave.resetAll();

			// Update the player and the cave once, just to get their starting appearances right.
			theCave.update();		// Update the position of the cave
			thePlayer.Move();		// Reposition the player

		break;

		// When changing to the Flying state
		case FLYING_STATE:

			g_gameTime = 0;

		break;

		// When changing to the Dead state (does nothing for now)
		case DEAD_STATE:
		break;
	}
}

int main(int argc, char **argv) {

	// Create the game window and initalise the VIDEO subsystem
	GameWindow gwd;
	gwd.InitVideo();
	gwd.SetBackground((GXColor){ 0, 30, 0, 255 });

	// Initialise Wiimote
	WPAD_Init();

	// Look for new Wii controllers
	WPAD_ScanPads();

	// Enable SD card stuff
	fatInitDefault();
	
	// Logging
#ifdef DEBUGMODE
		logFile.open ("/log.txt");
		logFile << "Opening log for Wiings.\n";
#endif

	// Go into the main menu state
	setGameState(MAIN_MENU_STATE);

	bool paused = false;

	// This is the game's run loop. It is executed several times per second.
	while(1) {

		// Look for new Wii controllers
		WPAD_ScanPads();

		// Handle controller events:

		// Quit the game (break out of the runloop) if HOME is pressed
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_HOME)
			break;

		// Do different things depending on the game state.
		switch (g_currentState) {
			
			case MAIN_MENU_STATE:

				// When A is pressed, start the game's flying mode
				if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_A) {

					g_currentState = FLYING_STATE;

					// Reset the current game timer
					g_gameTime = 0;
				}

				// Draw everything
				theCave.Draw();			// Draw the cave
				thePlayer.Draw();		// Draw the player
				
				// TODO: Draw some menu text on screen
			
			break;
			
			case FLYING_STATE:

				// When A is held (and game is not paused), fly the plane.
				if(WPAD_ButtonsHeld(WPAD_CHAN_0)&WPAD_BUTTON_A && !paused)
					thePlayer.thrust();
				// When + is pressed, pause or unpause.
				if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_PLUS)
					paused = !paused;

				// If the player touches the cave, you die.
				if (theCave.CollidesWithPlayer()) {
					setGameState(DEAD_STATE);
				}

				// Move everything (unless paused)
				if (!paused) {
					theCave.update();		// Update the position of the cave
					thePlayer.Move();		// Reposition the player
				}

				// Draw everything
				theCave.Draw();			// Draw the cave
				thePlayer.Draw();		// Draw the player

				// Increment the game timer
				g_gameTime++;

			break;
			
			case DEAD_STATE:

				// When + is pressed, reset back to main menu
				if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_PLUS) {
					setGameState(MAIN_MENU_STATE);
				}
				
				// Draw everything
				theCave.Draw();			// Draw the cave
				thePlayer.Draw();		// Draw the player
			
			break;			
		}

		// Draw the buffer to the screen and reset it.
		gwd.Flush();

		// Increase our count of how many frames have been drawn.
		g_ticks++;
		g_currentStateTime++;
	}

#ifdef DEBUGMODE
		logFile.close();
#endif

	// Closing game animation loop (or, Fancy Outro Sequence!)
	int closingTicks = 0;
	while (closingTicks < 180) {
		if (g_currentState != DEAD_STATE)
			thePlayer.thrust();				// Lift the player
		thePlayer.Move();				// Move the player
		if (thePlayer.GetY() < -100)	// If the player flies off-screen
			break;						// 		we're done.
		thePlayer.Draw();				// Draw the player
		int green = 30 - (0.3 * closingTicks);
		if (green < 0) green = 0;
		gwd.SetBackground((GXColor){ 0, green, 0, 255 });	// Fade to black
		gwd.Flush();					
		closingTicks++;
	}
	
	// The program has finished, so we return to the loader.
	return 0;
}
