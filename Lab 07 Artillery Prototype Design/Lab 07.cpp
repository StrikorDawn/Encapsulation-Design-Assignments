#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = 3.141592653589793;
const double INITIAL_SPEED = 827.0; // m/s
const double T = 0.01; // seconds
const int ARR_SIZE = 20;
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
// Array of density variables
const double D_ARRAY[] = {1.2250000, 1.1120000, 1.0070000, 0.9093000,
                          0.8194000, 0.7364000, 0.6601000, 0.5900000,
                          0.5258000, 0.4671000, 0.4135000, 0.1948000,
                          0.0889100, 0.0400800, 0.0184100, 0.0039960,
                          0.0010270, 0.0003097, 0.0000828, 0.0000185};
// Array of sound speed variables
const double S_ARRAY[] = {340, 336, 332, 328, 324, 320, 316, 312, 308, 303,
                          299, 295, 295, 295, 305, 324, 337, 319, 289, 269};
// Array of mach values
const double M_ARRAY[] = {0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980,
                          1.000, 1.020, 1.060, 1.240, 1.530, 1.990, 2.870,
                          2.890, 5.000};
// Array of drag coefficient values
const double C_ARRAY[] = {0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287,
                          0.4002, 0.4258, 0.4335, 0.4483, 0.4064, 0.3663,
                          0.2897, 0.2297, 0.2306, 0.2656};

double angleDegrees; // angle in degrees
double ddx; // horizontal acceleration
double ddy; // vertical acceleration
double dx;  // horizontal velocity
double dy;  // vertical velocity
double x;   // latitude
double y;   // altitude
double ht;  // Hang time
double g;   // gravity
double p;   // air density
int i;      // index i (altitude)
int j;      // index j (mach)
double ss;  // speed of sound
double m;   // current mach value
double c;   // drag coefficient
double px;  // distance from previous iteration
double py;  // altitude from previous iteration

double interpolate(double d0, double d1, double r0, double r1, double d)
{
   double r;
   r = (r1 * (d - d0) + r0 * (d1 - d)) / (d1 - d0);
   return r;
}

int findIndex(double x)
{
   for (int i = 0; i < ARR_SIZE; i++)
   {
      if (x >= A_ARRAY[i] && x < A_ARRAY[i + 1])
         return i;
   }
   return 0.0;
}

int findIndexJ(double m)
{
   for (int i = 0; i < 16; i++)
   {
      if (m >= M_ARRAY[i] && m < M_ARRAY[i + 1])
         return i;
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
   cout << "What is the angle of the howitzer where 0 is up? ";
   cin >> angleDegrees;
   
   // Convert angle to radians
   double angle_radians = angleDegrees * (PI / 180.0);
   
   // Compute initial velocity components
   double dx = INITIAL_SPEED * sin(angle_radians);
   double dy = INITIAL_SPEED * cos(angle_radians);
   
   // Initialize position
   x = 0.0;
   y = 0.0;
   ht = 0.0;
   px = 0.0;
   py = 0.0;
   g = 0.0;
   i = 0;
   
   // Loop through 20 time units
   while (y >= 0)
   {
      
      
      i = findIndex(y);
      
      // gravity calculation
      g = -interpolate(A_ARRAY[i],
                       A_ARRAY[i + 1],
                       G_ARRAY[i],
                       G_ARRAY[i + 1],
                       y);
      
      // air density calculation
      p = interpolate(A_ARRAY[i],
                       A_ARRAY[i + 1],
                       D_ARRAY[i],
                       D_ARRAY[i + 1],
                       y);
      
      // speed of sound calculation
      ss = interpolate(A_ARRAY[i],
                       A_ARRAY[i + 1],
                       S_ARRAY[i],
                       S_ARRAY[i + 1],
                       y);
      
      // calculate velocity
      double v = sqrt(dx * dx + dy * dy);
      
      // calculate mach
      m = v / ss;
      
      j = findIndexJ(m);
      
      // calculate drag coefficient
      c = interpolate(M_ARRAY[j],
                      M_ARRAY[j + 1],
                      C_ARRAY[j],
                      C_ARRAY[j + 1],
                      m);
      
      // calculate drag acceleration
      double drag = calculateDrag(c, p, v, A);
      ddx = -drag * (dx / v);
      ddy = -drag * (dy / v) + g;
      
      // Time is 1 because t changes from 1-20
      x += dx * T + 0.5 * ddx * T * T;
      y += dy * T + 0.5 * ddy * T * T;
      
      // Update the velocity
      dx += ddx * T;
      dy += ddy * T;
      
      // Update the hang time
      ht += T;
      if (y >= 0)
      {
         px = x;
         py = y;
      }
   }
   
   x = interpolate(y, py, x, px, 0);
   
   // Output current position
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(1);
   cout << "Distance: " << setw(12) << abs(x) << "m   "
   << "Hang Time: " << setw(10) << ht - T << "s\n";
   
}
