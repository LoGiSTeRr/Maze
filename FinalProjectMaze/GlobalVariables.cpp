#include "GlobalVariables.h"

int originalHeight = 50;
int originalWidth = 50;

int amountOfBombs = 4;
int amountOfGhosts = 1;
int mapSize = Tiny;

bool abilityToWalk = false; // ability to walk through ghost's trail

std::vector<std::vector<char>> Maze;
std::vector<std::vector<char>> OriginalMazeCopy;
std::vector<std::vector<std::string>> top; // top[j][i] j-mapSize, i - place
std::vector<int> movesOfPlayer;

std::vector<Unit> bombs;
std::vector<Unit> coins;
std::vector<Unit> ghosts;
std::vector<Unit> ghostsCopy;