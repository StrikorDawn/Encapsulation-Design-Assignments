/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <vector>        // for VECTOR
#include <iomanip>       // for SETW and SETPRECISION
using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight) :
      ground(posUpperRight),
      lander(posUpperRight)
   {
      lander.reset(posUpperRight);
   }
   Ground ground;
   Lander lander;
   Thrust thrust;
   vector<Star> stars;
   bool isRunning = true;  // Flag to indicate if the simulation is running
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Simulator* pSimulator = (Simulator*)p;

   

   ogstream gout;

   // If stars have not been initialized, initialize them
   if (pSimulator->stars.empty())
   {
      const int STAR_COUNT = 50;
      for (int i = 0; i < STAR_COUNT; i++)
      {
         Star star;
         star.reset(random(0, 400), random(0, 400));
         pSimulator->stars.push_back(star);
      }
   }

   // Draw all stars
   for (Star& star : pSimulator->stars)
   {
      star.draw(gout);

   }

   // draw the ground
   pSimulator->ground.draw(gout);

   // draw the lander
   pSimulator->lander.draw(pSimulator->thrust, gout);

   if (pSimulator->isRunning)
   {

      // Update the lander's position
      pSimulator->thrust.set(pUI);
      Acceleration accel = pSimulator->lander.input(pSimulator->thrust, -1.625);
      pSimulator->lander.coast(accel, 0.1);

      if (pSimulator->ground.onPlatform(pSimulator->lander.getPosition(),
         pSimulator->lander.getWidth()))
      {
         pSimulator->lander.land();
         pSimulator->isRunning = false;  // Stop the simulation
         return;
      }
      // Check for ground collision and handle landing or crashing
      else if (pSimulator->ground.hitGround(pSimulator->lander.getPosition(),
         pSimulator->lander.getWidth()))
      {
            pSimulator->lander.crash();
            pSimulator->isRunning = false;  // Stop the simulation
            return;

      }
   }

   // Calculate the altitude
   double altitude = pSimulator->lander.getPosition().getY() - pSimulator->ground.getElevation(pSimulator->lander.getPosition());

   // Construct the text to be displayed
   stringstream ss;
   ss << left << setw(15) << "Fuel: " << setw(1) << left
      << pSimulator->lander.getFuel() << " lbs\n";
   ss << left << setw(15) << "Altitude: " << setw(1) << left
      << static_cast<int>(altitude) << " meters\n";
   ss << left << setw(14) << "Velocity: " << setw(1) << left
      << fixed << setprecision(2) << pSimulator->lander.getSpeed() << " m/s";

   // Move the position to the top left corner
   gout.setPosition(Position(10, 370));

   // Use the stream to draw the text
   gout << ss.str();
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();


   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action   
   ui.run(callBack, (void*)&simulator);

   return 0;
}