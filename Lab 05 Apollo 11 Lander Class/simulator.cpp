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
using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(posUpperRight) {}
   Ground ground;
   //Lander lander;
   vector<Star> stars; 
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   Simulator* pSimulator = (Simulator*)p;

   ogstream gout;

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

   for (Star& star : pSimulator->stars)
   {
      star.draw(gout);
   }

   pSimulator->ground.draw(gout);

   //// Draw the lander
   //pSimulator->lander.draw(pSimulator->lander.thrust, gout);

   //// Update the lander's position
   //Acceleration accel = pSimulator->lander.input(pSimulator->lander.thrust, 1.625); // Assuming moon gravity of 1.625 m/s^2
   //pSimulator->lander.coast(accel, 0.1); // Assuming time step of 0.1 seconds
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
   ui.run(callBack, (void *)&simulator);
   
   return 0;
}
