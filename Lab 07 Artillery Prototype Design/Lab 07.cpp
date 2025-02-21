#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = 3.141592653589793;
const double INITIAL_SPEED = 827.0; // m/s
const double ANGLE_DEGREES = 75.0; // degrees
const double T = 0.01; // seconds
const int ARR_SIZE = 20;
const double C = 0.3; // drag coefficient
const double P = 0.6; // air density
const double A = 0.01884; // meters squared
const double MASS = 46.7; // Mass of the projectile in kg
// Array of gravity values based on altitude
const double G_ARRAY[] = {9.807, 9.804, 9.801, 9.797, 9.794, 9.791, 9.788,
                          9.785, 9.782, 9.779, 9.776, 9.761, 9.745, 9.730,
                          9.715, 9.684, 9.654, 9.624, 9.594, 9.564};
// Array of altitude variables
const double A_ARRAY[] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000,
                          9000, 10000, 15000, 20000, 25000, 30000, 40000,
                          50000, 60000, 70000, 80000};

double ddx; // horizontal acceleration
double ddy; // vertical acceleration
double dx;  // horizontal velocity
double dy;  // vertical velocity
double x;   // latitude
double y;   // altitude
double ht;  // Hang time
double g;   // gravity

double interpolate(double d0, double d1, double r0, double r1, double d)
{
   double r;
   r = (r1 * (d - d0) + r0 * (d1 - d)) / (d1 - d0);
   return r;
}

double findGravity(double altitude)
{
   for (int i = 0; i < ARR_SIZE; i++)
   {
      if (altitude == A_ARRAY[i])
         return G_ARRAY[i];
      else if (altitude > A_ARRAY[i] && altitude < A_ARRAY[i + 1])
         return -interpolate(A_ARRAY[i],
                             A_ARRAY[i + 1],
                             G_ARRAY[i],
                             G_ARRAY[i + 1],
                             altitude);
   }
   return 0.0;
}

double calculateDrag(double c, double p, double v, double a)
{
   double f; // drag force in newtons
   f = 0.5 * c * p * v * v * a;
   return f / MASS;
}

int main()
{
   // Convert angle to radians
   double angle_radians = ANGLE_DEGREES * (PI / 180.0);
   
   // Compute initial velocity components
   double dx = INITIAL_SPEED * sin(angle_radians);
   double dy = INITIAL_SPEED * cos(angle_radians);
   
   // Initialize position
   x = 0.0;
   y = 0.0;
   ht = 0.0;
   g = 0.0;
   
   // Loop through 20 time units
   while (y >= 0)
   {
      g = findGravity(y);
      
      // Time is 1 because t changes from 1-20
      x += dx * T + 0.5 * 0 * T * T;
      y += dy * T + 0.5 * g * T * T;
      
      // Update the velocity
      dx += 0 * T;
      dy += g * T;
      
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
