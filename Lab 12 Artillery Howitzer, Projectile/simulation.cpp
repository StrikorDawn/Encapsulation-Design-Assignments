/**********************************************************************
 * Source File:
 *    SIMULATION
 * Author:
 *    Taden Marston & Mark Van Horn
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION


Simulator::Simulator(const Position & posUpperRight)
   : ground(posUpperRight), howitzer()
{
   // Initialize ground and howitzer if needed
}

void Simulator::draw()
{
   // Create an ogstream object for drawing
   ogstream gout;

   // Draw the ground
   ground.draw(gout);

   // Draw the howitzer
   howitzer.draw(gout, 0.0); // Assuming flightTime is 0.0 for now
}
