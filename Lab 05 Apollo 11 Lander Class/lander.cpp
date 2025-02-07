/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   angle.setUp();
   status = PLAYING;
   fuel = 5000.0;
   velocity.setDX(random(-10, -4));
   velocity.setDY(random(-2, 2));
   pos.setX(posUpperRight.getX() - 1);
   pos.setY(posUpperRight.getY() * random(0.75, 0.95));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
   // Draw the main body of the lander
   gout.drawLander(pos, angle.getRadians());

   // Determine which flames to draw based on the thrust input
   bool mainEngine = thrust.isMain();
   bool leftThrust = thrust.isCounter();
   bool rightThrust = thrust.isClock();

   // Draw the flames under the lander
   gout.drawLanderFlames(pos, angle.getRadians(), mainEngine, leftThrust, rightThrust);
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   // Get the thrust acceleration
   double thrustAccel = thrust.mainEngineThrust();

   // Calculate the horizontal and vertical components of the thrust acceleration
   double thrustX = thrustAccel * cos(angle.getRadians());
   double thrustY = thrustAccel * sin(angle.getRadians());

   // Calculate the total acceleration considering thrust and gravity
   double accelX = thrustX;
   double accelY = thrustY - gravity;

   // Set the acceleration
   Acceleration acceleration;
   acceleration.setDDX(accelX);
   acceleration.setDDY(accelY);

   return acceleration;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   // Update the position based on velocity and time
   pos.setX(pos.getX() + velocity.getDX() * time + 0.5 *
      (acceleration.getDDX() * time * time));
   pos.setY(pos.getY() + velocity.getDY() * time + 0.5 *
      (acceleration.getDDY() * time * time));

   // Update the velocity based on acceleration and time
   velocity.setDX(velocity.getDX() + acceleration.getDDX() * time);
   velocity.setDY(velocity.getDY() + acceleration.getDDY() * time);
}
