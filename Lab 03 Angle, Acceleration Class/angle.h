/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159
#include <cmath> // for nice little abs() functions

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestLander;
   
   // Constructors
   Angle()                 : radians(-99.9)  {}
   Angle(const Angle& rhs) : radians(-99.9)  {}
   Angle(double degrees)   : radians(-99.9)  {}

   // Getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   // Setters
   void setDegrees(double degrees) { }
   void setRadians(double radians) { }
   void setUp()                    { }
   void setDown()                  { }
   void setRight()                 { }
   void setLeft()                  { }
   void reverse()                  { }
   Angle& add(double delta)
   {
      radians += delta;
      radians = abs(radians);
      return *this;
   }

private:
   double normalize(double radians) const;
   double convertToDegrees(double radian) const { return 360 * radian / 2 * M_PI; }
   double convertToRadians(double degrees) const { return (degrees / 360) * 2 * M_PI; }

   double radians;   // 360 degrees equals 2 PI radians
};

