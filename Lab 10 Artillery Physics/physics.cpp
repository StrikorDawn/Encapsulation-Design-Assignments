/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/
  
 #include "physics.h"  // for the prototypes
 
 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain) {
   // Edge cases: If domain is outside the given mapping range
   if (domain <= mapping[0].domain) {
      return mapping[0].range;
   }
   if (domain >= mapping[numMapping - 1].domain) {
      return mapping[numMapping - 1].range;
   }
   
   // Find the interval containing 'domain'
   for (int i = 0; i < numMapping - 1; ++i) {
      double x0 = mapping[i].domain, y0 = mapping[i].range;
      double x1 = mapping[i + 1].domain, y1 = mapping[i + 1].range;
      
      if (domain >= x0 && domain <= x1) {
         // Apply the linear interpolation formula
         return y0 + (domain - x0) * (y1 - y0) / (x1 - x0);
      }
   }
   
   // Default return (should never reach here)
   return 0.0;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
   const double g0 = 9.80665; // Standard gravity at sea level in m/s^2
   const double R = 6371000.0;  // Radius of the Earth in meters

   return g0 * pow(R / (R + altitude), 2);
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
   return -99.9;
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
   return -99.9;
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   return -99.9;
}

