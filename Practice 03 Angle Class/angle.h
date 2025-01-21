/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 03: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#pragma once

#define TWO_PI 6.28318530718

#include <math.h>    // for floor()
#include <iostream>  // for cout
#include <cassert>   // for assert()
using namespace std;

class TestAngle;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;
   
   double radians;

   private:

      double normalize(double radian)
      {
         while (radian < 0)
         {
            radian += TWO_PI;
         }
         while (radian >= TWO_PI)
         {
            radian -= TWO_PI;
         }
         return radian;
      }

      double convertToDegrees(double radian)
      {
         return normalize(radian * (360 / TWO_PI)); // M_PI wasn't working
      }

      double convertToRadians(double degree)
      {
         return normalize(degree * (TWO_PI / 360)); // M_PI wasn't working
      }

   public:
      double getDegrees()
      {
         
      }

      double getRadians()
      {
         return radians;
      }

      double setDegrees()
      {

      }

      double setRadians(double radian)
      {
         radians = radian;
      }

      ostream& display(ostream& out) const
      {
         cout.setf(ios::fixed);     // "fixed" means don't use scientific notation
         cout.setf(ios::showpoint); // "showpoint" means always show the decimal point
         cout.precision(1);         // Set the precision to 1 decimal place of accuracy.
      }
};


