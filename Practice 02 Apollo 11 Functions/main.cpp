/*************************************************************
 * 1. Name:
 *      Taden Marston & Mark Van Horn
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was adjusting the main function with
 *      the modified outputs and user inputs. On top of that,
 *      getting the indentation correct on the second counter
 *      was something new.
 * 5. How long did it take for you to complete the assignment?
 *      This assignment took us roughly 0.5 hrs to complete.
 **************************************************************/

#include <iostream>  // for CIN and COUT
#include <cmath>     // for MATH
#include <chrono>
#include <thread>
#include <iomanip> // Required for std::setw and std::right
using namespace std;

#define M_PI     3.14159265358979323846 // pi; cmath didn't pi didn't work.
#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double computeDistance(double s, double v, double  a, double t)
{
   return (s + v * t + 0.5 * a * t * t);
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double computeAcceleration(double f, double m)
{
   return (f / m);
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double computeVelocity(double v, double a, double t)
{
   return (v + a * t);
}

/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double computeVerticalComponent(double a, double total)
{
   return (cos(a) * total);
}

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
double computeHorizontalComponent(double a, double total)
{
   return (sin(a) * total);
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
double computeTotalComponent(double x, double y)
{
   return (sqrt(x * x + y * y));
}


/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
double radiansFromDegrees(double d)
{
   return ((d / 360) * (2 * M_PI));
}

/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(string x)
{
   double y;
   cout << x;
   cin >> y;
   return y;
}

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
   // Prompt for input and variables to be computed
   double dy = prompt("What is your vertical velocity (m/s)? ");
   double dx = prompt("What is your horizontal velocity (m/s)? ");
   double y = prompt("What is your altitude (m)? ");
   double x = 0; //prompt("What is your position (m)? ");
   double aDegrees = prompt("What is the angle of the LM "
                            "where 0 is up (degrees)? ");
   double t = 1; //prompt("What is the time interval (s)? ");
   double aRadians;            // Angle in radians
   double accelerationThrust;  // Acceleration due to thrust
   double ddxThrust;           // Horizontal acceleration due to thrust
   double ddyThrust;           // Vertical acceleration due to thrust
   double ddx;                 // Total horizontal acceleration
   double ddy;                 // Total vertical acceleration
   double v;                   // Total velocity
   
   // Output preamble outside loop so it's not repeated unnecessarily
   cout << "\nFor the next 5 seconds with the main engine on, ";
   cout << "the position of the lander is:\n\n";

   // Go through the simulator ten times, with a break halfway for angle
   // readjustment.
   for (int i = 0; i < 10; i++)
   {
      // Convert angle to radians 
      aRadians = radiansFromDegrees(aDegrees);
      // Compute acceleration due to thrust 
      accelerationThrust = computeAcceleration(THRUST, WEIGHT);
      // Compute horizontal and vertical components of thrust acceleration 
      ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
      ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);
      // Compute total horizontal and vertical accelerations 
      ddx = ddxThrust; ddy = ddyThrust + GRAVITY;
      // Compute new position
      x = computeDistance(x, dx, ddx, t);
      y = computeDistance(y, dy, ddy, t);
      // Compute new velocity 
      dx = computeVelocity(dx, ddx, t);
      dy = computeVelocity(dy, ddy, t);
      //Compute total velocity 
      v = computeTotalComponent(dx, dy);

      // Output
      cout.setf(ios::fixed | ios::showpoint);
      cout.precision(2);
      
      // Updates every 1 second
      cout << right << setw(2) << i + 1;
      cout << "s - x,y: (" << x << ", " << y << ")m  ";
      cout << "dx,dy: (" << dx << ", " << dy << ")m/s  ";
      cout << "speed:" << v << "m/s  angle:" << aDegrees << "deg" << endl;
      
      // Updates the angle after 5 seconds
      if (i == 4) {
         aDegrees = prompt("\nWhat is the new angle of the LM "
                           "where 0 is up (degrees)? ");
         cout << "\nFor the next 5 seconds with the main engine on, ";
         cout << "the position of the lander is:\n\n";
      }
      
      // 1 second sleep counter for visual splendor
      this_thread::sleep_for(chrono::seconds(1));
   }

   return 0;
}
