#include <iostream>
#include <random>
#include <vector>
#include "MazeGeneration.h"
#include "GlobalVariables.h"
#include "UnitFuncs.h"

//Maze Generation: Recursive Division
// http://weblog.jamisbuck.org/2011/1/12/maze-generation-recursive-division-algorithm
// the algorithm used in this code.

std::default_random_engine engine(time(nullptr));
std::uniform_int_distribution<int> directionOfWall(0, 1);

#define Wall 219
enum Directions { Horizontal = 1, Vertical = 0 };

std::vector<std::vector<char>> CreateMaze()
{
	std::vector<std::vector<char>> Maze(originalHeight);
	for (size_t x = 0; x < originalHeight; x++)
	{
		Maze[x] = std::vector<char>(originalWidth);
		for (int y = 0; y < originalWidth; y++)
		{
			if (y == 0 || y == originalWidth - 1 || x == 0 || x == originalHeight - 1)
			{
				Maze[x][y] = Wall;
				continue;
			}
			Maze[x][y] = ' ';
		}
	}
	Divide(Maze, 1, 1, -1, originalWidth - 2, originalHeight - 2, ChooseDirection(originalWidth, originalHeight));
	return Maze;
}
int ChooseDirection(int width, int height)
{
	if (width < height)
	{
		return Horizontal;
	}
	else if (width > height)
	{
		return Vertical;
	}
	else
	{
		return directionOfWall(engine);
	}

}
bool NormalWallCheck(std::vector<std::vector<char>> Maze, int wx, int wy, int width, int height, bool& horizontal, int& i)
{
	if (i++ == 10)
	{
		i = -1; // if its unreal to place a wall, just quit from this area
		return true;
	}
	if (horizontal)
	{
		if (Maze[wx][wy - 1] == ' ')
		{
			horizontal = !horizontal;
			return false;
		}
		if (Maze[wx][width + wy] == ' ')
		{
			horizontal = !horizontal;
			return false;
		}
	}
	else
	{
		if (Maze[wx - 1][wy] == ' ')
		{
			horizontal = !horizontal;
			return false;
		}
		if (Maze[wx + height][wy] == ' ')
		{
			horizontal = !horizontal;
			return false;
		}
	}
	return true;
}
void Divide(std::vector<std::vector<char>>& Maze, int x, int y, int previousPassCoord, int width, int height, int direction)
{
	bool horizontal = direction;

	if (width <= 2 || height <= 2)
	{
		return;
	}


	std::uniform_int_distribution<int> WallFromX(1, height - 2);
	std::uniform_int_distribution<int> WallFromY(1, width - 2);
	std::uniform_int_distribution<int> PassageInWallX(0, height - 1);
	std::uniform_int_distribution<int> PassageInWallY(0, width - 1);


	//Wall will be drawn from:
	int wx;
	int wy;
	int i = 0;
	do
	{
		wx = x + (horizontal ? WallFromX(engine) : 0); // wall X
		wy = y + (horizontal ? 0 : WallFromY(engine)); // wall Y
	} while (i != -1 && !NormalWallCheck(Maze, wx, wy, width, height, horizontal, i));

	if (i == -1) // if its unreal to place a wall, just quit from this area
	{
		return;
	}


	//Passage in the wall:
	int px = wx + (horizontal ? 0 : PassageInWallX(engine)); // Passage X
	int py = wy + (horizontal ? PassageInWallY(engine) : 0); // Passage Y

	// direction of wall:
	int dx = horizontal ? 0 : 1; // Direction X
	int dy = horizontal ? 1 : 0; // Direction Y

	// length of wall:
	int length = horizontal ? width : height;

	//draw the wall:
	for (int i = 0; i < length; i++)
	{
		if (wx != px || wy != py)
		{
			Maze[wx][wy] = Wall;
		}
		wx += dx;
		wy += dy;
	}



	int nx = x; // new x
	int ny = y; // new y 
	int nw = horizontal ? width : wy - y; // new width
	int nh = horizontal ? wx - x : height; // new height
	int pw = horizontal ? py : px; // Previous Pass Coord

	Divide(Maze, nx, ny, pw, nw, nh, ChooseDirection(nw, nh));

	nx = horizontal ? wx + 1 : x;
	ny = horizontal ? y : wy + 1;
	nw = horizontal ? width : y + width - wy - 1;
	nh = horizontal ? x + height - wx - 1 : height;
	pw = horizontal ? py : px;

	Divide(Maze, nx, ny, pw, nw, nh, ChooseDirection(nw, nh));
}
void GenerateBombs()
{
	std::uniform_int_distribution<int> Xpos(1, originalHeight - 2);
	std::uniform_int_distribution<int> Ypos(1, originalWidth - 2);

	for (int i = 0; i < amountOfBombs; i++)
	{
		int x;
		int y;
		do
		{
			x = Xpos(engine);
			y = Ypos(engine);
		} while (Maze[x][y] != ' ');
		bombs.push_back(CreateBomb(x, y));
	}
}
void GenerateCoins()
{
	std::uniform_int_distribution<int> Xpos(1, originalHeight - 2);
	std::uniform_int_distribution<int> Ypos(1, originalWidth - 2);

	for (int i = 0; i < 5; i++)
	{
		int x;
		int y;
		do
		{
			x = Xpos(engine);
			y = Ypos(engine);
		} while (Maze[x][y] != ' ');
		coins.push_back(CreateCoin(x, y));
	}
}
void GenerateGhosts()
{
	std::uniform_int_distribution<int> Xpos(1, originalHeight - 2);
	std::uniform_int_distribution<int> Ypos(1, originalWidth - 2);

	for (int i = 0; i < amountOfGhosts; i++)
	{
		int x;
		int y;
		do
		{
			x = Xpos(engine);
			y = Ypos(engine);
		} while (Maze[x][y] != ' ' && x <= 13 && y <= 13);
		ghosts.push_back(CreateGhost(x, y));
	}
	for (int i = 0; i < amountOfGhosts; i++)
	{
		ghostsCopy.push_back(ghosts[i]);
	}
}

