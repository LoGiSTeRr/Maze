#include <vector>
#include "GlobalVariables.h"
#include "Unit.h"

Unit CreateNewUnit(short hp, short xCoord, short yCoord, char icon)
{
	Unit unit;

	unit.hp = hp;
	unit.xCoord = xCoord;
	unit.yCoord = yCoord;

	unit.icon = icon;

	return unit;
}

Unit CreatePlayer()
{
	Unit player;
	player = CreateNewUnit(3, 1, 1, '#');
	return player;
}

Unit CreateBomb(int x, int y)
{
	Unit bomb;
	bomb = CreateNewUnit(1, x, y, '0');
	Maze[x][y] = bomb.icon;
	return bomb;
}
Unit CreateCoin(int x, int y)
{
	Unit coin;
	coin = CreateNewUnit(1, x, y, '$');
	Maze[x][y] = coin.icon;
	return coin;
}
Unit CreateGhost(int x, int y)
{
	Unit ghost;
	ghost = CreateNewUnit(1, x, y, '~');
	Maze[x][y] = ghost.icon;
	return ghost;
}