#include <vector>
#include "Unit.h";
#include "UI.h"
#include "Console/console.h"
#include "PlayerMovement.h"
#include "GlobalVariables.h"
#include "GhostLogic.h"

using namespace app::console;

#define Wall (char)219

int moveCounter = 0;
int bombsCounter = 1;
int coinsCounter = 0;

void ClearAndExit()
{
	coins.clear();
	bombs.clear();
	ghosts.clear();
	ghostsCopy.clear();
	Maze.clear();
	OriginalMazeCopy.clear();
	moveCounter = 0;
	bombsCounter = 1;
	coinsCounter = 0;
	PrintMenu();
}
void PlayerMovement(Unit player, int i, bool replay, int repInstruct)
{
	bool alive = true;
	while (alive)
	{
		if (i == 2)
		{
			GhostMovement(player);
			i = 0;
		}

		if (Maze[player.xCoord][player.yCoord] == '~')
		{
			player.hp -= 1;
			io.scpos(originalWidth * 2 + 10 + 4, 14);
			io << player.hp;
			if (player.hp <= 0)
			{
				io.scpos(originalWidth * 2 + 8, 30);
				io << "You lost! Press smth to leave in Main Menu.";
				ClearAndExit();
			}
		}

		io.scpos(player.yCoord * 2, player.xCoord); // update user pos
		io << color::GOLD << player.icon << player.icon << color::WHITE;

		io.scpos(originalWidth * 2 + 10 + 7, 17); // update move counter
		io << moveCounter;
		io.scpos(originalWidth * 2 + 10, 24);
		io << "Press escape to leave in Main Menu.";
		if (Maze[player.xCoord][player.yCoord] == '0') // check if player on bomb
		{
			bombsCounter++;

			Maze[player.xCoord][player.yCoord] = ' ';
			io.scpos(originalWidth * 2 + 10 + 7, 15);
			io << bombsCounter;
		}
		else if (Maze[player.xCoord][player.yCoord] == '$') // check if player on coin
		{
			coinsCounter++;

			Maze[player.xCoord][player.yCoord] = ' ';
			io.scpos(originalWidth * 2 + 10 + 7, 16);
			io << coinsCounter;

			if (coinsCounter == 5)
			{
				Maze[originalHeight - 1][originalWidth - 2] = ' '; // exit
				io.scpos((originalWidth - 2) * 2, originalHeight - 1);
				io << "  ";
			}
		}

		if (player.xCoord == originalHeight - 1 && player.yCoord == originalWidth - 2)
		{
			if (replay)
			{
				io.scpos(originalWidth * 2 + 8, 30);
				io << "Quitting in 2 seconds...";
				Sleep(2000);
				PrintMenu();
			}
			else
			{
				io.scpos(originalWidth * 2 + 8, 30);
				io << "Congratz!";
				io.scpos(originalWidth * 2 + 8, 32);
				io << "Do you want to save this score?";
				coins.clear();
				bombs.clear();
				ghosts.clear();

				bombsCounter = 1;
				coinsCounter = 0;
				DoAllStuffForInGameMenu();
			}


		}
		key k;
		if (replay)
		{
			Sleep(85);
			if (movesOfPlayer[repInstruct] == 'E')
			{
				k = key::ENTER;
			}
			else
			{
				k = (key)movesOfPlayer[repInstruct];
			}

		}
		else
		{
			do
			{
				k = io.readk();
				if (k == key::ENTER || k == key::w || k == key::W || k == key::S || k == key::s ||
					k == key::A || k == key::a || k == key::D || k == key::d || k == key::ESCAPE)
				{
					if (k == key::ESCAPE)
					{
						break;
					}
					if (k == key::ENTER)
					{
						movesOfPlayer.push_back((char)'E');
					}
					else
					{
						movesOfPlayer.push_back((char)k);
					}
					break;
				}
			} while (true);

		}
		switch (k)
		{
		case key::ENTER:
		{
			if (bombsCounter != 0 && player.xCoord >= 2 && player.yCoord >= 2 && player.xCoord <= originalHeight - 3 && player.yCoord <= originalWidth - 3)
			{
				for (int i = -1; i <= 1; i++)
				{
					io.scpos(player.yCoord * 2 - 2, player.xCoord + i);
					io.repeat("  ", 3);
				}
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (i == 0 && j == 0)
						{
							continue;
						}
						if (Maze[player.xCoord + i][player.yCoord + j] == '$')
						{
							io.scpos(originalWidth * 2 + 8, 30);
							io << "You lost! Press smth to leave in Main Menu.";
							ClearAndExit();
						}
						if (Maze[player.xCoord + i][player.yCoord + j] == '~')
						{
							for (int j = 0; j < amountOfGhosts; j++)
							{
								if (CheckDistance(player, ghosts[j]) < 2)
								{
									ghosts.erase(ghosts.begin() + j);
									amountOfGhosts--;
									j = 0;
								}
							}
						}
						Maze[player.xCoord + i][player.yCoord + j] = ' ';

					}
				}
				bombsCounter--;
				io.scpos(originalWidth * 2 + 10 + 7, 15);
				io << bombsCounter;
			}
			break;
		}
		case key::w:
		case key::W:
		{
			if (Maze[player.xCoord - 1][player.yCoord] != Wall)
			{
				io.erase(player.yCoord * 2, player.xCoord);
				io.erase(player.yCoord * 2 + 1, player.xCoord);
				player.xCoord -= 1;
				moveCounter++;

			}
			break;
		}
		case key::s:
		case key::S:
		{
			if (Maze[player.xCoord + 1][player.yCoord] != Wall)
			{
				io.erase(player.yCoord * 2, player.xCoord);
				io.erase(player.yCoord * 2 + 1, player.xCoord);
				player.xCoord += 1;
				moveCounter++;

			}
			break;
		}
		case key::d:
		case key::D:
		{
			if (Maze[player.xCoord][player.yCoord + 1] != Wall)
			{
				io.erase(player.yCoord * 2, player.xCoord);
				io.erase(player.yCoord * 2 + 1, player.xCoord);
				player.yCoord += 1;
				moveCounter++;

			}
			break;
		}
		case key::a:
		case key::A:
		{
			if (Maze[player.xCoord][player.yCoord - 1] != Wall)
			{
				io.erase(player.yCoord * 2, player.xCoord);
				io.erase(player.yCoord * 2 + 1, player.xCoord);
				player.yCoord -= 1;
				moveCounter++;

			}
			break;
		}
		case key::ESCAPE:
		{
			ClearAndExit();
		}

		default:
			break;
		}
		i++;
		repInstruct++;
	}
	//PlayerMovement(player, ++i, replay, ++repInstruct);
}