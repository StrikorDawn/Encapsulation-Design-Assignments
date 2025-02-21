#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.141592653589793;
const double INITIAL_SPEED = 827.0; // m/s
const double ANGLE_DEGREES = 75.0;
const int TIME_UNITS = 20;

double acceleration;
double drag;

double angle;
double dx;  // horizontal velocity
double dy;  // vertical velocity
double x;   // latitude
double y;   // altitude
const double GRAVITY = -9.8;



int main() {
   // Convert angle to radians
   double angle_radians = ANGLE_DEGREES * (PI / 180.0);
   
   // Compute initial velocity components
   double dx = INITIAL_SPEED * sin(angle_radians);
   double dy = INITIAL_SPEED * cos(angle_radians);
   
   // Initialize position
   double x = 0.0;
   double y = 0.0;
   
   // Loop through 20 time units
   for (int t = 1; t <= TIME_UNITS; ++t)
   {
      // Time is 1 because t changes from 1-20
      x += dx * 1 + 0.5 * 0 * 1 * 1;
      y += dy * 1 + 0.5 * GRAVITY * 1 * 1;
      
      dx += 0 * 1;
      dy += GRAVITY * 1;
      
      // Output current position
      cout << "Distance: " << x << "m, Altitude: " << y << "m\n";
   }
}
