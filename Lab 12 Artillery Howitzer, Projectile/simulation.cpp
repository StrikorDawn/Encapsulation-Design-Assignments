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
   // Create an ogstream object for drawing
   ogstream gout;

   // Draw the ground
   ground.draw(gout);

   // Draw the howitzer
   howitzer.draw(gout, 0.0); // Assuming flightTime is 0.0 for now
}

#include "simulation.h"
#include "uiInteract.h"
#include "uiDraw.h"

Simulator::Simulator(const Position& posUpperRight) :
   ptUpperRight(posUpperRight),
   ground(posUpperRight),
   time(0.0),
   angle(0.0)
{
   // Set the horizontal position of the howitzer. This should be random.
   ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

   // Generate the ground and set the vertical position of the howitzer.
   ground.reset(ptHowitzer);

   // Initialize the projectile path
   for (int i = 0; i < 20; i++)
   {
      projectilePath[i].setPixelsX((double)i * 2.0);
      projectilePath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
   }
}

void Simulator::update(const Interface* pUI)
{
   // Accept input
   if (pUI->isRight())
      angle += 0.05;
   if (pUI->isLeft())
      angle -= 0.05;
   if (pUI->isUp())
      angle += (angle >= 0 ? -0.003 : 0.003);
   if (pUI->isDown())
      angle += (angle >= 0 ? 0.003 : -0.003);
   if (pUI->isSpace())
      time = 0.0;

   // Perform game logic
   time += 0.5;
   for (int i = 0; i < 20; i++)
   {
      double x = projectilePath[i].getPixelsX();
      x -= 1.0;
      if (x < 0)
         x = ptUpperRight.getPixelsX();
      projectilePath[i].setPixelsX(x);
   }
}

void Simulator::draw(ogstream& gout) const
{
   // Draw the ground
   ground.draw(gout);

   // Draw the howitzer
   gout.drawHowitzer(ptHowitzer, angle, time);

   // Draw the projectile
   for (int i = 0; i < 20; i++)
      gout.drawProjectile(projectilePath[i], 0.5 * (double)i);

   // Draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);
   gout << "Time since the bullet was fired: " << time << "s\n";
}
