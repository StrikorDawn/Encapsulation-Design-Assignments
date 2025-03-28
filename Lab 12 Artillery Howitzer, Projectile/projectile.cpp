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
	 pvt.v.set(a, muzzleVelocity);
    pvt.t = time;
    flightPath.push_back(pvt);
 }
