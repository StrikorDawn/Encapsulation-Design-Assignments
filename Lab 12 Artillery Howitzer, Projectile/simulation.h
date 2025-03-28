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
   Simulator(const Position & posUpperRight);

   void draw();

private:
   Ground ground;
   Howitzer howitzer;
};
