#pragma once
#include <string>
#ifndef TopAndFilesH
#define TopAndFilesH


void TopInitialize();
void SaveScore(std::string name, int moves, int mapSize);
void ReadMazeInfo(std::string seacrhName, int searchMoves);
bool isNameMoveReal(std::string seacrhName, int searchMoves);
void ReadData();


#endif