#pragma once

#ifndef MazeGenerationh
#define MazeGenerationh

std::vector<std::vector<char>> CreateMaze();
int ChooseDirection(int width, int height);
bool NormalWallCheck(std::vector<std::vector<char>> Maze, int wx, int wy, int width, int height, bool& horizontal, int& i);
void Divide(std::vector<std::vector<char>>& Maze, int x, int y, int previousPassCoord, int width, int height, int direction);

void GenerateBombs();
void GenerateCoins();
void GenerateGhosts();
#endif