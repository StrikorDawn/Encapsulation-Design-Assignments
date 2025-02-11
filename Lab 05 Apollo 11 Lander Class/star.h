/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

 /*****************************************************
  * STAR
  * A star that twinkles
  *****************************************************/
class Star
{
private:
	Position pos;
	unsigned char phase = random(0, 255); // For out of phase stars
public:
	void reset(double width, double height)
	{
		pos.setX(width);
		pos.setY(height);
	}
	void draw(ogstream& gout)
	{
		gout.drawStar(pos, phase);
		phase++;
	}
};
