/**********************************************************************
 * Source File:
 *    Lab 12: M777 Howitzer
 * Author:
 *    Taden Marston & Mark Van Horn
 * Summary:
 *    Simulate firing the M777 howitzer 15mm artillery piece
 ************************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "simulation.h" // for SIMULATION
#include "position.h"   // for POSITION
#include "test.h"       // for the unit tests
using namespace std;


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
	// Cast the void pointer into our Simulator object.
	Simulator* pSim = (Simulator*)p;
	static bool isHit = false;
	static bool isFiring = false;

	// Process user input for howitzer movement
	if (pUI->isRight())
		pSim->howitzer.rotate(0.05);
	if (pUI->isLeft())
		pSim->howitzer.rotate(-0.05);

	if (pUI->isUp())
		pSim->howitzer.raise(0.003);
	if (pUI->isDown())
		pSim->howitzer.raise(-0.003);

	// Add a flag to check if the projectile is in flight

	// Fire the projectile when space is pressed, but only if not already firing
	if (pUI->isSpace() && !isFiring)
	{
		pSim->time = 0.0;
		pSim->projectile.reset();
		pSim->projectile.fire(pSim->howitzer.getPosition(),
			pSim->howitzer.getElevation(),
			pSim->howitzer.getMuzzleVelocity(),
			pSim->time);

		// Set the firing flag to true to prevent firing until projectile lands
		isFiring = true;
		isHit = false;
	}

	// Advance game time
	pSim->time += 0.5;

	// Check if the bullet is still in the air (if its Y position is above ground level)
	bool isFlying = true;
	if (pSim->projectile.getPosition().getMetersY() >= pSim->ground.getElevationMeters(pSim->projectile.getPosition()))
	{
		pSim->projectile.advance(pSim->time);
	}
	else
	{
		isFlying = false;
	}

	// Now check if the bullet has hit the ground
	if (!isFlying)
	{
		// Bullet has landed, reset the firing flag to allow another shot
		isFiring = false;

		// Increase the acceptable distance for the target area (e.g., 10 meters instead of 5 meters)
		if (pSim->projectile.getPosition().getMetersX() >= (pSim->ground.getTarget().getMetersX() - 175) &&
			pSim->projectile.getPosition().getMetersX() <= (pSim->ground.getTarget().getMetersX() + 175))
		{
			// Bullet is near the target area, reset ground and projectile
			pSim->projectile.reset();
			pSim->ground.reset(pSim->howitzer.getPosition());
			isHit = true;
		}
		else
		{
			// Bullet hit the ground but not near the target, only reset the projectile
			pSim->projectile.reset();
		}
	}

	// Shift old positions in the projectilePath array so the trail is preserved
	for (int i = 19; i > 0; i--)
	{
		pSim->projectilePath[i] = pSim->projectilePath[i - 1];
	}
	// Store the current projectile position at the beginning of the trail
	pSim->projectilePath[0] = pSim->projectile.getPosition();

	// Prepare for drawing text and graphics
	ogstream gout(Position(10.0, pSim->posUpperRight.getPixelsY() - 20.0));

	// Draw the ground and the howitzer
	pSim->ground.draw(gout);
	pSim->howitzer.draw(gout, pSim->time);

	// Get the bullet position (most recent)
	Position bulletPos = pSim->projectilePath[0];
	// Compute the maximum distance in the trail using the oldest trail point (index 19)
	double dx = pSim->projectilePath[19].getPixelsX() - bulletPos.getPixelsX();
	double dy = pSim->projectilePath[19].getPixelsY() - bulletPos.getPixelsY();
	double maxDistance = sqrt(dx * dx + dy * dy);

	// Set a constant maximum age value for scaling (tweak this as needed)
	double MAX_AGE = 5.0;

	// Draw the trail (indices 1 to 19)
	for (int i = 1; i < 20; i++)
	{
		double diffX = pSim->projectilePath[i].getPixelsX() - bulletPos.getPixelsX();
		double diffY = pSim->projectilePath[i].getPixelsY() - bulletPos.getPixelsY();
		double distance = sqrt(diffX * diffX + diffY * diffY);
		double ageValue = 0.0;
		if (maxDistance > 0)
			ageValue = (distance / maxDistance) * MAX_AGE;
		gout.drawProjectile(pSim->projectilePath[i], ageValue);
	}

	// Draw the bullet (index 0) on top (always drawn as black since age is 0)
	gout.drawProjectile(bulletPos, 0.0);

	// Draw some status text on the screen
	gout.setf(ios::fixed | ios::showpoint);
	gout.precision(1);
	gout << "Time since the bullet was fired: " << pSim->time << "s\n";
	if (isHit)
	{
		gout << "Target: Hit!";
	}
	else
	{
		gout << " ";
	}


}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pCmdLine,
	_In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
	// unit tests
	testRunner();

	// Initialize OpenGL
	Position posUpperRight;
	posUpperRight.setZoom(40.0 /* 40 meters equals 1 pixel */);
	posUpperRight.setPixelsX(700.0);
	posUpperRight.setPixelsY(500.0);
	Interface ui("M777 Howitzer Simulation", posUpperRight);

	// Initialize the simulation.
	Simulator sim(posUpperRight);


	// set everything into action
	ui.run(callBack, (void*)&sim);

	return 0;
}
