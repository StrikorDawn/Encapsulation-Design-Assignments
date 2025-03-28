/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Taden Marston & Mark Van Horn
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


#include "projectile.h"
#include "angle.h"
#include "acceleration.h"
#include "cmath"
using namespace std;

void Projectile::reset()
{
   mass = DEFAULT_PROJECTILE_WEIGHT;
   radius = DEFAULT_PROJECTILE_RADIUS;
   flightPath.clear();
}

void Projectile::fire(const Position& pos,
                      Angle a,
                      double muzzleVelocity,
                      double time)
{
   PositionVelocityTime pvt;
   pvt.pos = pos;
   pvt.v.set(a, muzzleVelocity);
   pvt.t = time;
   flightPath.push_back(pvt);
}

void Projectile::advance(double simulationTime)
{
   // Check if flightPath is empty
   if (flightPath.empty())
      return;
   
   // Get time interval
   PositionVelocityTime pvt = flightPath.back();
   double t = simulationTime - pvt.t;
   
   // Get current altitude
   double altitude = pvt.pos.getMetersY();
   
   // Calculate drag
   double c = accelerationFromForce(
                 forceFromDrag(
                    densityFromAltitude(altitude),
                    dragFromMach(
                       pvt.v.getSpeed() / speedSoundFromAltitude(altitude)),
                    radius,
                    pvt.v.getSpeed()),
                 mass);
   
   double cX = 0.0;
   double cY = 0.0;
   if (pvt.v.getSpeed() != 0.0)
   {
      cX = c * (pvt.v.getDX() / pvt.v.getSpeed());
      cY = c * (pvt.v.getDY() / pvt.v.getSpeed());
   }
   
   // Calculate vertical acceleration
   double ddy = gravityFromAltitude(altitude) - cY;
   
   // Calculate horizontal acceleration
   double ddx = cX;
   
   // Create acceleration object with these values
   Acceleration a = Acceleration(-ddx, -ddy);
   
   // Update pvt and push it back to flightPath
   pvt.pos.add(a, pvt.v, t);
   pvt.v.add(a, t);
   pvt.t = simulationTime;
   flightPath.push_back(pvt);

}
