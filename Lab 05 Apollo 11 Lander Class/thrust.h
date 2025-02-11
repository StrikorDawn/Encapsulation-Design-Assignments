/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

class TestLander;
class TestThrust;

/*****************************************************
 * THRUST
 * Represents activation of thrusters
 *****************************************************/
class Thrust
{
	friend TestLander;
	friend TestThrust;

public:
	// Thrust is initially turned off
	Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

	// Get rotation in radians per second
	double rotation() const
	{
		if (clockwise && !counterClockwise)
			return 0.1; // Clockwise rotation
		else if (counterClockwise && !clockwise)
			return -0.1; // Counter-clockwise rotation
		else
			return 0.0; // No rotation
	}

	// get main engine thrust in  m / s ^ 2
	double mainEngineThrust() const
	{
		if (mainEngine)
		{
			const double thrust = 45000; // Newtons
			const double mass = 15103;   // Kilograms
			return thrust / mass;        // F = ma -> a = F / m
		}
		else
			return 0.0; // No thrust
	}

	// reflect what is firing
	bool isMain()    const { return mainEngine; }
	bool isClock()   const { return clockwise; }
	bool isCounter() const { return counterClockwise; }

	// set the thrusters
	void set(const Interface* pUI)
	{
		if (pUI->isDown())
		{
			mainEngine = true;
		}
		else
		{
			mainEngine = false;
		}

		if (pUI->isLeft())
		{
			clockwise = true;
		}
		else
		{
			clockwise = false;
		}

		if (pUI->isRight())
		{
			counterClockwise = true;
		}
		else
		{
			counterClockwise = false;
		}
	}

private:
	bool mainEngine;
	bool clockwise;
	bool counterClockwise;
};
