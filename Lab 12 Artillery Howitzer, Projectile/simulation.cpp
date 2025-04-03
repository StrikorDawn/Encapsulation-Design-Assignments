/**********************************************************************
 * Source File:
 *    SIMULATION
 * Author:
 *    Taden Marston & Mark Van Horn
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION


Simulator::Simulator(const Position& posUpperRight)
: ground(posUpperRight), howitzer()
{
   // Set horizontal position of the howitzer
   posHowitzer.setPixelsX(Position(posUpperRight).getPixelsX() / 2.0);
   
   // Draw the ground and set the vertical position of the howitzer
   ground.reset(posHowitzer);
   
   // This is temporary
   for (int i = 0; i < 20; i++)
   {
      projectilePath[i].setPixelsX((double)i * 2.0);
      projectilePath[i].setPixelsY(posUpperRight.getPixelsY() / 1.5);
   }
}
