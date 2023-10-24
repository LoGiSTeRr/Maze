#include <vector>
#include <string>
#include "Unit.h"
#pragma once

#ifndef varh
#define varh

enum size
{
	Tiny,
	Little,
	Medium,
	Big
};

extern int originalWidth;
extern int originalHeight;

extern int amountOfBombs;
extern int amountOfGhosts;

extern int mapSize;

extern bool abilityToWalk; // ability to walk through ghost's trail

extern std::vector<std::vector<char>> Maze;
extern std::vector<std::vector<char>> OriginalMazeCopy; // for save
extern std::vector<std::vector<std::string>> top;
extern std::vector<int> movesOfPlayer;

extern std::vector<Unit> bombs;
extern std::vector<Unit> coins;
extern std::vector<Unit> ghosts;
extern std::vector<Unit> ghostsCopy; // for save
#endif