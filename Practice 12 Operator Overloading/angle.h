/*************************************************************
 * 1. Name:
 *      Mark Van Horn & Taden Marston
 * 2. Assignment Name:
 *      Practice 12: C++ Operator Overloading
 * 3. Assignment Description:
 *      Practice Overloading Operators
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was figuring out how to make the increment
 *      and decrement operators work, we figured out that it was
 *      incrementing and decrementing radians, not degrees, so we
 *      made the adjustment. Also, the ostream and istream operators
 *      were a bit tricky, but we got them working.
 * 5. How long did it take for you to complete the assignment?
 *      About an hour.
 **************************************************************/

#pragma once

#define PI     3.141592653589793238462643383279502
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
      out << convertToDegrees(radians);
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
   inline Angle operator-() const
   {
      return Angle(convertToDegrees(normalize(radians + PI)));
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
      
      if (in.fail()) {
         return in; // Do NOT modify rhs
      }
      
      rhs.setDegrees(degrees); // Only modify rhs if input was valid
      return in;
   }
   
   // Prefix increment for the '++' operator
   inline Angle& operator++()
   {
      radians = normalize(radians + (TWO_PI / 360)); // Increment by one degree in radians
      return *this;
   }
   
   // Postfix increment for the '++' operator
   inline Angle operator++(int)
   {
      Angle temp(*this);
      ++(*this);
      return temp;
   }
   
   // Prefix decrement for the '--' operator
   inline Angle& operator--()
   {
      radians = normalize(radians - (TWO_PI / 360)); // Decrement by one degree in radians
      return *this;
   }
   
   // Postfix decrement for the '--' operator
   inline Angle operator--(int)
   {
      Angle temp(*this);
      --(*this);
      return temp;
   }
};

