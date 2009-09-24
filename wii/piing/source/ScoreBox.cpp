/*
 *      ScoreBox.cpp
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for ScoreBox objects.  A ScoreBox instance keeps track
 * 		of a score, and contains a method to draw it as a progress bar
 * 		on the screen.
 */

#include <wiisprite.h>
#include "ScoreBox.h"

using namespace wsp;

// Default constructor
ScoreBox::ScoreBox(int x, int y, int width) {

	score = 0;
	
	innerRect.x = x;
	outerRect.x = x;
	innerRect.y = y;
	outerRect.y = y;

	innerRect.width = 0;
	outerRect.width = width;
	innerRect.height = 16;
	outerRect.height = 16;
	
	outerQuad.SetFillColor((GXColor){ 0, 0, 0, 255 });
	outerQuad.SetBorder(true);
	outerQuad.SetBorderColor((GXColor){ 0, 255, 0, 255 });
	outerQuad.SetBorderWidth(10);

	innerQuad.SetFillColor((GXColor){ 0, 255, 0, 255 });

	outerQuad.SetRectangle(&outerRect);
	innerQuad.SetRectangle(&innerRect);
}

// Destructor
ScoreBox::~ScoreBox() { }


// Operations:

bool ScoreBox::incrementScore() {

	if (score < MAXSCORE) {
		score++;
		innerRect.width = outerRect.width * ( (float)score / MAXSCORE );
		return true;
	}
	else return false;
}

// Draws the mover
void ScoreBox::Draw() {

	outerQuad.SetRectangle(&outerRect);
	innerQuad.SetRectangle(&innerRect);

	outerQuad.Draw();
	innerQuad.Draw();
}
