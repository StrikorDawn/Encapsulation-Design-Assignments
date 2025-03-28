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
#include "uiDraw.h"

class Simulator
{
public:
   Simulator(const Position& posUpperRight);
   void update(const Interface* pUI);
   void draw(ogstream& gout) const;

private:
   Ground ground;
   Howitzer howitzer;
   Position projectilePath[20];
   Position ptUpperRight;
   double angle;
   double time;
};
