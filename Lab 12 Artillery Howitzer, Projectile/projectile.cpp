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

void Projectile::fire(const Position& pos, Angle a, double muzzleVelocity, double time)
{
   PositionVelocityTime pvt;
   pvt.pos = pos;
   pvt.v.setDX(muzzleVelocity * a.getDx());
   pvt.v.setDY(muzzleVelocity * a.getDy());
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
   double altitude = pvt.pos.getMetersX();
   
   // Calculate drag
   double c = accelerationFromForce(forceFromDrag(densityFromAltitude(altitude),
                                                  dragFromMach(speedSoundFromAltitude(altitude)),
                                                  radius,
                                                  pvt.v.getSpeed()),
                                    mass);
   
   // Calculate vertical acceleration
   double ddy = gravityFromAltitude(altitude) + c;
   
   // Calculate horizontal acceleration
   double ddx = c;
   
   // Create acceleration object with these values
   Acceleration a = Acceleration(-ddx, -ddy);
   
   // Update pvt and push it back to flightPath
   pvt.pos.add(a, pvt.v, t);
   pvt.v.add(a, t);
   pvt.t = simulationTime;
   flightPath.push_back(pvt);

}
