#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = 3.141592653589793;
const double INITIAL_SPEED = 827.0; // m/s
const double ANGLE_DEGREES = 75.0;
const double T = 0.01;
const double G = -9.8;

double acceleration;
double drag;
double dx;  // horizontal velocity
double dy;  // vertical velocity
double x;   // latitude
double y;   // altitude
double ht;  // Hang time




int main()
{
   // Convert angle to radians
   double angle_radians = ANGLE_DEGREES * (PI / 180.0);
   
   // Compute initial velocity components
   double dx = INITIAL_SPEED * sin(angle_radians);
   double dy = INITIAL_SPEED * cos(angle_radians);
   
   // Initialize position
   double x = 0.0;
   double y = 0.0;
   
   // Loop through 20 time units
   while (y >= 0)
   {
      // Time is 1 because t changes from 1-20
      x += dx * T + 0.5 * 0 * T * T;
      y += dy * T + 0.5 * G * T * T;
      
      // Update the velocity
      dx += 0 * 1;
      dy += G * 1;
      
      // Update the hang time
      ht += T;
      
      // Output current position
      cout.setf(ios::fixed);
      cout.setf(ios::showpoint);
      cout.precision(1);
      cout << "Distance: " << setw(7) << x << "m   "
           << "Altitude: " << setw(5) << y << "m   "
           << "Hang Time: " << setw(4) << ht << "s\n";
   }
}
