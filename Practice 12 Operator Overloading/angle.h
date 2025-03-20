/*************************************************************
 * 1. Name:
 *      Mark Van Horn & Taden Marston
 * 2. Assignment Name:
 *      Practice 04: C++ Method
 * 3. Assignment Description:
 *      Practice Overloading Operators
 * 4. What was the hardest part? Be as specific as possible.
 *
 * 5. How long did it take for you to complete the assignment?
 *
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
   Angle(const Angle& rhs)
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
    * GET
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
   
   /***************************************
    * Operator Overloads
    ***************************************/
   inline Angle& operator=(const Angle& rhs) {
      if (this != &rhs) { // Avoid self-assignment
         radians = rhs.radians;
      }
      return *this;
   }
   
   // extension for the '-' operator
   Angle operator-() const
   {
      return Angle(convertToDegrees(normalize(radians + M_PI)));
   }
   
   // extension for the '==' operator
   inline bool operator==(const Angle& rhs) const
   {
      return radians == rhs.radians;
   }
   
   // extension for the '!=' operator
   inline bool operator!=(const Angle& rhs) const
   {
      return !(*this == rhs);
   }
   
   // extension for the '<<' operator
   friend ostream& operator<<(ostream& out, const Angle& rhs)
   {
      return rhs.display(out);
   }
   
   // extension for the '>>' operator
   friend istream& operator>>(istream& in, Angle& rhs)
   {
      double degrees;
      in >> degrees;
      rhs.setDegrees(degrees);
      return in;
   }
   
   // Prefix increment for the '++' operator
   Angle& operator++()
   {
      return *this;
   }
   
   // Postfix increment for the '++' operator
   Angle operator++(int)
   {
      Angle temp(*this);
      ++(*this);
      return temp;
   }
   
   // Prefix increment for the '--' operator
   Angle& operator--()
   {
      return *this;
   }
   
   // Postfix increment for the '--' operator
   Angle operator--(int)
   {
      Angle temp(*this);
      --(*this);
      return temp;
   }
};

