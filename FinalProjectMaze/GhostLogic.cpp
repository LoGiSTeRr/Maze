#include "GhostLogic.h"

using namespace app::console;
#define Wall (char)219

int CheckDistance(Unit player, Unit ghost)
{
	return sqrt(pow(ghost.xCoord - player.xCoord, 2) + pow(ghost.yCoord - player.yCoord, 2));
}
void GhostMovement(Unit player)
{
	for (int i = 0; i < amountOfGhosts; i++)
	{
		if (!(CheckDistance(player, ghosts[i]) < 20)) // ghost array fix.
		{
			continue;
		}
		int mx = player.xCoord - ghosts[i].xCoord == 0 ? 0 : (player.xCoord - ghosts[i].xCoord > 0 ? 1 : -1);
		int my = player.yCoord - ghosts[i].yCoord == 0 ? 0 : (player.yCoord - ghosts[i].yCoord > 0 ? 1 : -1);

		Maze[ghosts[i].xCoord][ghosts[i].yCoord] = abilityToWalk ? ' ' : Wall;

		io.scpos(ghosts[i].yCoord * 2, ghosts[i].xCoord);
		io << color::VIOLET << Wall << Wall << color::WHITE;
		ghosts[i].xCoord += mx;
		ghosts[i].yCoord += my;
		if (Maze[ghosts[i].xCoord][ghosts[i].yCoord] == '$' || Maze[ghosts[i].xCoord][ghosts[i].yCoord] == '0')
		{
			ghosts[i].xCoord += mx;
			ghosts[i].yCoord += my;
		}
		io.scpos(ghosts[i].yCoord * 2, ghosts[i].xCoord);
		io << color::VIOLET_V2 << ghosts[i].icon << ghosts[i].icon << color::WHITE;
		Maze[ghosts[i].xCoord][ghosts[i].yCoord] = ghosts[i].icon;
	}
}



