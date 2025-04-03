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
   // the first step is to cast the void pointer into a simulator object. This
   // is the first step of every single callback function in OpenGL.
   Simulator* pSim = (Simulator*)p;
   
   // move a lot
   if (pUI->isRight())
      pSim->angle += 0.05;
   if (pUI->isLeft())
      pSim->angle -= 0.05;
   
   // move a little
   if (pUI->isUp())
      pSim->angle += (pSim->angle >= 0 ? -0.003 : 0.003);
   if (pUI->isDown())
      pSim->angle += (pSim->angle >= 0 ? 0.003 : -0.003);
   
   // fire gun
   if (pUI->isSpace())
   {
      pSim->time = 0.0;
      pSim->projectile.reset();
      pSim->projectile.fire(pSim->howitzer.getPosition(), pSim->angle,
                            pSim->howitzer.getMuzzleVelocity(), pSim->time);
      pSim->projectile.advance(pSim->time);
   }
   
   // Advance game time
   pSim->time += 0.5;
   
   // move the projectile across the screen
      for (int i = 0; i < 20; i++)
      {
         // this bullet is moving left at 1 pixel per frame
         pSim->projectile.advance(pSim->time);
         pSim->projectilePath[i].setPixelsX(pSim->projectile.getPosition().getPixelsX());
         pSim->projectilePath[i].setPixelsY(pSim->projectile.getPosition().getPixelsY());
      }
   
   ogstream gout(Position(10.0, pSim->posUpperRight.getPixelsY() - 20.0));
   
   // Draw the ground
   pSim->ground.draw(gout);
   
   // Draw the howitzer
   gout.drawHowitzer(pSim->posHowitzer, pSim->angle, pSim->time);
   
   // draw the projectile
   for (int i = 0; i < 20; i++)
      gout.drawProjectile(pSim->projectilePath[i], 0.5 * (double)i);
   
   // draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);
   gout << "Time since the bullet was fired: "
   << pSim->time << "s\n";
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
   ui.run(callBack, (void *)&sim);

   return 0;
}
