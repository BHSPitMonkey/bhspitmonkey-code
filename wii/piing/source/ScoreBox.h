/*
 *      ScoreBox.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for ScoreBox objects.  A ScoreBox instance keeps track
 * 		of a score, and contains a method to draw it as a progress bar
 * 		on the screen.
 */

#include <wiisprite.h>

#ifndef SCOREBOX_H
#define SCOREBOX_H

#define MAXSCORE 15

using namespace wsp;

class ScoreBox {
public:

	// Constructors and destructor:
	ScoreBox(int x, int y, int width);
	~ScoreBox();		// destructor

	// Accessors:

	// Operations:
	bool incrementScore();
	void Draw();

protected:

	int score;
   
	Rectangle outerRect;
	Rectangle innerRect;
	Quad outerQuad;
	Quad innerQuad;

};  // end class

#endif
