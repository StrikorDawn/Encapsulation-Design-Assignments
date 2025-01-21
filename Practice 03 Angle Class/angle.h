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
#include <cmath>     // for fmod()
using namespace std;

class TestAngle;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;
   private:
      double normalize(double radian)
      {
         radian = fmod(radian, TWO_PI);
         if (radian < 0)
            radian += TWO_PI;
         return radian;
      }
      double convertToDegrees(double radian)
      {
         return normalize(radian) * (360 / TWO_PI);
      }
      double convertToRadians(double degrees)
      {
         return normalize(degrees * (TWO_PI / 360));
      }
   public:
      double radians = 0;
      double getDegrees()
      {
         return convertToDegrees(radians);
      }
      double getRadians()
      {
         return radians;
      }
      void setDegrees(double degrees)
      {
         radians = convertToRadians(degrees);
      }
      void setRadians(double radian)
      {
         radians = normalize(radian);
      }
      void display(ostream& out) const
   {
      cout.setf(ios::fixed);     // "fixed" means don't use scientific notation
      cout.setf(ios::showpoint); // "showpoint" means always show the decimal point
      cout.precision(1);         // Set the precision to 1 decimal place of accuracy.
   }
};


