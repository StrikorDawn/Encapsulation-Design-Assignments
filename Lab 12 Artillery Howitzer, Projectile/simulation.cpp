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
   // initializers
   time = 0.0;
   angle = 0.0;
   
   // Set horizontal position of the howitzer
   posHowitzer.setPixelsX(Position(posUpperRight).getPixelsX() / 2.0);
   
   // Draw the ground and set the vertical position of the howitzer
   ground.reset(posHowitzer);
   
   // This is the trail of the projectile
   for (int i = 0; i < 20; i++)
   {
      projectilePath[i].setPixelsX(posHowitzer.getPixelsX() + (double)i * 2.0);
      projectilePath[i].setPixelsY(posHowitzer.getPixelsY() + 20);
   }
}
