#include <iostream>
#include <vector>
#include <cstdlib>
#include "MazeGeneration.h"
#include "TopAndFiles.h"
#include "Console/console.h"
#include "UI.h"
#include "GlobalVariables.h"
#include "UnitFuncs.h"
#include "PlayerMovement.h"
using namespace app::console;



struct Button
{
	std::string text;

	int x;
	int y;

	bool selected;

	void(*func_ptr)();

};
struct MyMenu
{
	std::string nameOfMenu;

	bool active;

	std::vector<Button> buttons;
};

const int amountOfMenus = 5;
MyMenu menus[amountOfMenus];
bool gameStarted = false;
void StartReplay();
void PrintMaze(std::vector<std::vector<char>> Maze)
{

	io.scpos(0, 0);
	for (int i = 0; i < originalHeight; i++)
	{
		for (int j = 0; j < originalWidth; j++)
		{
			char temp = Maze[i][j];
			io << Maze[i][j] << Maze[i][j];
		}
		io.scpos(0, 1 + i);
	}
}
MyMenu CreateMyMenu(std::string nameOfMenu, bool active)
{
	MyMenu menu;

	menu.nameOfMenu = nameOfMenu;
	menu.active = active;

	return menu;
}
Button CreateButton(std::string text, int x, int y, bool selected, void(*func_ptr)())
{
	Button button;

	button.text = text;
	button.x = x;
	button.y = y;
	button.selected = selected;

	button.func_ptr = func_ptr;

	return button;
}
void PrintMenu(MyMenu menus[])
{
	for (int cur = 0; cur < amountOfMenus; cur++)
	{
		if (menus[cur].active)
		{
			io.scpos(89, 3);
			io << menus[cur].nameOfMenu;
			for (size_t i = 0; i < menus[cur].buttons.size(); i++)
			{
				io.scpos(menus[cur].buttons[i].x, menus[cur].buttons[i].y);
				if (menus[cur].buttons[i].text == "Amount Of Bombs: ")
				{
					menus[cur].buttons[i].selected == true ? io << menus[cur].buttons[i].text << amountOfBombs << " <-" : io << menus[cur].buttons[i].text << amountOfBombs << "   ";
					continue;
				}
				else if (menus[cur].buttons[i].text == "Amount Of Ghosts: ")
				{
					menus[cur].buttons[i].selected == true ? io << menus[cur].buttons[i].text << amountOfGhosts << " <-" : io << menus[cur].buttons[i].text << amountOfGhosts << "   ";
					continue;
				}
				else if (menus[cur].buttons[i].text == "Ability to walk through the ghost's trail: ")
				{
					std::string temp = abilityToWalk ? "On" : "Off";
					menus[cur].buttons[i].selected == true ? io << menus[cur].buttons[i].text << temp << "  <-" : io << menus[cur].buttons[i].text << temp << "     ";
					continue;
				}
				menus[cur].buttons[i].selected == true ? io << menus[cur].buttons[i].text << " <-" : io << menus[cur].buttons[i].text << "   ";
			}
			io.scpos(0, 0);
		}
	}

}
void ChangeSelectedButton(MyMenu menus[])
{
	for (int cur = 0; cur < amountOfMenus; cur++)
	{
		if (menus[cur].active)
		{
			key k = io.readk();
			switch (k)
			{
			case key::s:
			case key::S:
			{
				for (int i = 0; i < menus[cur].buttons.size(); i++)
				{
					if (menus[cur].buttons[i].selected)
					{
						if (i == menus[cur].buttons.size() - 1)
						{
							menus[cur].buttons[i].selected = false;
							menus[cur].buttons[0].selected = true;
							break;
						}
						menus[cur].buttons[i].selected = false;
						menus[cur].buttons[i + 1].selected = true;
						break;
					}
				}
				break;
			}
			case key::w:
			case key::W:
			{
				for (int i = 0; i < menus[cur].buttons.size(); i++)
				{
					if (menus[cur].buttons[i].selected)
					{
						if (i == 0)
						{
							menus[cur].buttons[i].selected = false;
							menus[cur].buttons[menus[cur].buttons.size() - 1].selected = true;
							break;
						}
						menus[cur].buttons[i].selected = false;
						menus[cur].buttons[i - 1].selected = true;
						break;
					}
				}
				break;
			}
			case key::ENTER:
			{
				for (int i = 0; i < menus[cur].buttons.size(); i++)
				{
					if (menus[cur].buttons[i].selected)
					{
						menus[cur].buttons[i].func_ptr();
						break;
					}
				}
				break;
			}
			case key::r:
			case key::R:
			{
				if (menus[4].active)
				{
					io.scpos(80, 14);
					std::string name;
					std::string moves;
					io << "Enter player's name: ";
					std::getline(std::cin, name);
					io.scpos(80, 14);
					io << "Enter " << name << "'s amount of moves: ";
					std::getline(std::cin, moves);
					if (moves.size() < 5 && isNameMoveReal(name, std::stoi(moves)))
					{
						ReadMazeInfo(name, std::stoi(moves));
						StartReplay();
					}
					else
					{
						io.scpos(80, 14);
						io << "Not found.                                      ";
					}

				}
				break;
			}

			}
			break;
		}
	}
	if (gameStarted)
	{
		return;
	}
	PrintMenu(menus);
	ChangeSelectedButton(menus);
}
void PrintInGameUI(Unit player)
{
	io.vrepeat(originalWidth * 2 + 7, 0, (char)177, 25);
	io.vrepeat(originalWidth * 2 + 7 + 40, 0, (char)177, 25);

	io.vrepeat(originalWidth * 2 + 7 + 1, 0, (char)177, 25);
	io.vrepeat(originalWidth * 2 + 7 + 40 + 1, 0, (char)177, 25);

	io.repeat(originalWidth * 2 + 7, 0, (char)177, 40);
	io.repeat(originalWidth * 2 + 7, 0 + 25, (char)177, 42);

	io.scpos(originalWidth * 2 + 10, 3);
	io << "Info:";

	io.scpos(originalWidth * 2 + 10, 5);
	io << player.icon << player.icon << " - you";

	io.scpos(originalWidth * 2 + 10, 7);
	io << "WASD for move.";

	io.scpos(originalWidth * 2 + 10, 8);
	io << "Enter for use bombs.";

	io.scpos(originalWidth * 2 + 10, 9);
	io << "Escape to leave.";

	io.scpos(originalWidth * 2 + 10, 12);
	io << "Statistics:";

	io.scpos(originalWidth * 2 + 10, 14);
	io << "HP: " << player.hp;

	io.scpos(originalWidth * 2 + 10, 15);
	io << "Bombs: 1";

	io.scpos(originalWidth * 2 + 10, 16);
	io << "Coins: 0";

	io.scpos(originalWidth * 2 + 10, 17);
	io << "Moves: 0";

	io.scpos(originalWidth * 2 + 10, 20);
	io << "Collect all coins to open exit!";


}

void StartReplay()
{
	system("cls");
	Unit player = CreatePlayer();
	gameStarted = true;
	PrintMaze(Maze);
	PrintInGameUI(player);
	PlayerMovement(player, 0, true, 0);
}
void StartMaze()
{
	system("cls");
	Maze = CreateMaze();
	GenerateBombs();
	GenerateCoins();
	GenerateGhosts();
	OriginalMazeCopy = Maze;
	gameStarted = true;
	Unit player = CreatePlayer();
	PrintMaze(Maze);
	PrintInGameUI(player);
	PlayerMovement(player, 0, false , 0);

}

void EraseMenuAndDeselectAll()
{
	for (int i = 0; i < 50; i++)
	{
		io.scpos(10, 2 + i);
		io.repeat(' ', 160);
	}
	for (int i = 0; i < amountOfMenus; i++)
	{
		menus[i].active = false;
	}
}
// Button functions
void ExitGameBut()
{
	io.scpos(50, 50);
	exit(0);
}
void InfoMenuBut()
{
	EraseMenuAndDeselectAll();
	menus[1].active = true;
	io.scpos(80, 15);
	io << "This game was created by LoGiSTeRr.";
	io.scpos(80, 16);
	io << "Maze project for ItStep.";
	io.scpos(80, 17);
	io << "Date: 03.10.2021";
}
void TopMenuBut()
{
	EraseMenuAndDeselectAll();
	menus[4].active = true;
	io.scpos(80, 12);
	io << "If you want to see, how one of them played, press R.";
	for (int j = 0; j < 4; j++)
	{
		switch (j)
		{
			case Tiny:
				io.scpos(25 + j * 45, 18);
				io << "Tiny";
				break;
			case Little:
				io.scpos(25 + j * 45, 18);
				io << "Little";
				break;
			case Medium:
				io.scpos(25 + j * 45, 18);
				io << "Medium";
				break;
			case Big:
				io.scpos(25 + j * 45, 18);
				io << "Big";
				break;
		}
		int len = top[j].size();
		for (int i = 1; i < len; i++) // start from 1, cuz of first bad element
		{
			io.scpos(10 + j * 45, 20 + i * 2);
			io << i << ": " << top[j][i] << '\n';
		}
	}

}
void PlayMenuBut()
{
	EraseMenuAndDeselectAll();
	menus[2].active = true;
}
void GoBack()
{
	EraseMenuAndDeselectAll();
	menus[0].active = true;
}
void TinyStart()
{
	mapSize = Tiny;
	originalHeight = 20;
	originalWidth = 20;
	EraseMenuAndDeselectAll();
	StartMaze();
}
void LittleStart()
{
	mapSize = Little;
	originalHeight = 35;
	originalWidth = 35;
	EraseMenuAndDeselectAll();
	StartMaze();
}
void MediumStart()
{
	mapSize = Medium;
	originalHeight = 50;
	originalWidth = 50;
	EraseMenuAndDeselectAll();
	StartMaze();
}
void BigStart()
{
	mapSize = Big;
	originalHeight = 50;
	originalWidth = 75;
	EraseMenuAndDeselectAll();
	StartMaze();
}
void AmountOfBomb()
{
	amountOfBombs++;
	if (amountOfBombs == 6)
	{
		amountOfBombs = 1;
	}
}
void AmountOfGhost()
{
	amountOfGhosts++;
	if (amountOfGhosts == 4)
	{
		amountOfGhosts = 0;
	}
}
void AbilityToWalk()
{
	abilityToWalk = !abilityToWalk;
}
void YesBut()
{
	io.scpos(originalWidth * 2 + 8, 38);
	std::string nameBuf;
	do
	{
		io << "Enter your name please(20 symbols max): ";
		std::getline(std::cin, nameBuf);
		io.scpos(originalWidth * 2 + 8, 38);
		io << "                                                                                                                                                                                                             "; // cool code, i know
		io.scpos(originalWidth * 2 + 8, 38);
	} while (nameBuf.size() > 20);

	SaveScore(nameBuf, moveCounter, mapSize);
	ghostsCopy.clear();
	io.scpos(originalWidth * 2 + 8, 40);
	io << "Saved! Exiting to menu...";
	moveCounter = 0;
	Sleep(2000);
	PrintMenu();

}
void NoBut()
{
	ghostsCopy.clear();
	moveCounter = 0;
	PrintMenu();
}

void DoAllStuffForInGameMenu()
{

	for (int i = 0; i < amountOfMenus; i++)
	{
		menus[i].active = false;
	}
	menus[3].buttons[0].x = originalWidth * 2 + 20;
	menus[3].buttons[1].x = originalWidth * 2 + 20;
	menus[3].active = true;
	gameStarted = false;
	PrintMenu(menus);
	ChangeSelectedButton(menus);
}
void CreateAllStuff()
{
	menus[0] = CreateMyMenu("Main Menu", true);
	menus[0].buttons.push_back(CreateButton("Play", 90, 10, true, PlayMenuBut));
	menus[0].buttons.push_back(CreateButton("Tops", 90, 15, false, TopMenuBut));
	menus[0].buttons.push_back(CreateButton("Info", 90, 20, false, InfoMenuBut));
	menus[0].buttons.push_back(CreateButton("Exit", 90, 25, false, ExitGameBut));

	menus[1] = CreateMyMenu("Info Menu", false);
	menus[1].buttons.push_back(CreateButton("Back", 90, 10, true, GoBack));

	menus[2] = CreateMyMenu("Play Menu", false);
	menus[2].buttons.push_back(CreateButton("Back", 90, 10, true, GoBack));
	menus[2].buttons.push_back(CreateButton("Amount Of Bombs: ", 90, 15, false, AmountOfBomb));
	menus[2].buttons.push_back(CreateButton("Amount Of Ghosts: ", 90, 17, false, AmountOfGhost));
	menus[2].buttons.push_back(CreateButton("Ability to walk through the ghost's trail: ", 90, 19, false, AbilityToWalk));
	menus[2].buttons.push_back(CreateButton("Tiny(20 x 20)", 90, 22, false, TinyStart));
	menus[2].buttons.push_back(CreateButton("Little(35 x 35)", 90, 24, false, LittleStart));
	menus[2].buttons.push_back(CreateButton("Medium(50 x 50)", 90, 26, false, MediumStart));
	menus[2].buttons.push_back(CreateButton("Big(75 x 50)", 90, 28, false, BigStart));

	menus[3] = CreateMyMenu("", false);
	menus[3].buttons.push_back(CreateButton("Yes", originalWidth * 2, 34, true, YesBut));
	menus[3].buttons.push_back(CreateButton("No", originalWidth * 2, 36, false, NoBut));

	menus[4] = CreateMyMenu("Top", false);
	menus[4].buttons.push_back(CreateButton("Back", 88, 10, true, GoBack));
}
void PrintMenu()
{
	gameStarted = false;
	system("cls");
	io.vrepeat(0, '#', 60);
	io.vrepeat(200, 0, '#', 60);
	io.repeat(0, 0, "# ", 100);
	io.repeat(0, 60, "# ", 100);
	io.scpos(85, 5);

	io << "use W/S and ENTER.";

	CreateAllStuff();

	PrintMenu(menus);
	ChangeSelectedButton(menus);
}