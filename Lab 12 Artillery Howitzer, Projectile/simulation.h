/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    Taden Marston & Mark Van Horn
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "ground.h"
#include "howitzer.h"
#include "projectile.h"
#include "uiDraw.h"

class Simulator
{
public:
   Simulator(const Position& posUpperRight);
   Ground ground;
   Howitzer howitzer;
   Projectile projectile;
   Position posHowitzer;
   Position posUpperRight;
   Position projectilePath[20];
   double angle;
   double time;

};