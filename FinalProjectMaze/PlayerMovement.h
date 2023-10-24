#pragma once

#ifndef PlayerMovementh
#define PlayerMovementh
#include "Unit.h"
#include <vector>
#include "Console/console.h"

extern int moveCounter;
void PlayerMovement(Unit player, int i, bool replay, int repInstruct);

#endif