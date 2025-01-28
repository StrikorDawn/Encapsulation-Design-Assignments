/*************************************************************
 * 1. Name:
 *      Mark Van Horn & Taden Marston
 * 2. Assignment Name:
 *      Practice 03: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      This one was a learning process for us. Once we got the
 *      program to compile we got a ton of failed tests, but after
 *      an extremely helpful consultation we began the debugging
 *      process which solved 89.7% of our problems, we then got
 *      very stuck on the display portion, which was highly
 *      frustrating because while the output was exactly what was
 *      listed in the tests, the tests failed.
 * 5. How long did it take for you to complete the assignment?
 *      2.5 hours :(
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

   /***************************************
    * CONVERT
    ***************************************/
   
      // normalizes radians to 0 < radian < TWO_PI
      double normalize(double radian) const
      {
         radian = fmod(radian, TWO_PI);
         if (radian < 0)
            radian += TWO_PI;
         return radian;
      }
   
      // normalizes radians and then converts to degrees
      double convertToDegrees(double radian) const
      {
         return normalize(radian) * (360 / TWO_PI);
      }
   
      // converts to radians and then normalizes
      double convertToRadians(double degrees) const
      {
         return normalize(degrees * (TWO_PI / 360));
      }
   public:
   /***************************************
   * CONTSTRUCTORS
   ***************************************/
      // Default Constructor
      Angle()
      {
         radians = 0.0;
      };

      // copy constructor
      Angle(const Angle & rhs)
      {
         radians = rhs.radians;
      };

      // non-default constructor
      Angle(double degrees)
      {
         this->radians = convertToRadians(degrees);
      };
      
      double radians;

   /***************************************
   * SET
   ***************************************/
   
      // converts radians to degrees and returns the value
      double getDegrees() const
      {
         return convertToDegrees(radians);
      };
   
      // returns radians
      double getRadians() const
      {
         return radians;
      };
   
   /***************************************
   * SET
   ***************************************/
   
      // converts degrees param to radians and sets value
      void setDegrees(double degrees)
      {
         radians = convertToRadians(degrees);
      };
   
      // sets radians to param value
      void setRadians(double radian)
      {
         radians = normalize(radian);
      };
   
   /***************************************
    * DISPLAY
    ***************************************/
   
      //Displays radians variable in degrees format
      ostream& display(ostream& out) const
      {
         out.setf(ios::fixed);     // "fixed" means don't use scientific notation
         out.setf(ios::showpoint); // "showpoint" means always show the decimal point
         out.precision(1);         // Set the precision to 1 decimal place of accuracy.
         out << convertToDegrees(radians) << "degrees";
         return out;
      }
};

