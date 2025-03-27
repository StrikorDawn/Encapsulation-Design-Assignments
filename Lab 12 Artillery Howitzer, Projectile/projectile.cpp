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
    pvt.v.setDX(muzzleVelocity * a.getDx());
    pvt.v.setDY(muzzleVelocity * a.getDy());
    pvt.t = time;
    flightPath.push_back(pvt);
 }
