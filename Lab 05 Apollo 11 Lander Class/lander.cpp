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
   status = DEAD;
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
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
   // Update the velocity based on acceleration and time
   velocity.setDX(velocity.getDX() + acceleration.getDDX() * time);
   velocity.setDY(velocity.getDY() + acceleration.getDDY() * time);
   
   // Update the position based on velocity and time
   pos.setX(pos.getX() + velocity.getDX() * time);
   pos.setY(pos.getY() + velocity.getDY() * time);
}
