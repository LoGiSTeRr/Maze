#pragma once

#ifndef UnitFuncsh
#define UnitFuncsh

#include "Unit.h"
#include <vector>
Unit CreateNewUnit(short hp, short xCoord, short yCoord, char icon);
Unit CreatePlayer();
Unit CreateBomb(int x, int y);
Unit CreateCoin(int x, int y);
Unit CreateGhost(int x, int y);
#endif