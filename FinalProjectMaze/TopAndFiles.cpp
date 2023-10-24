#include "TopAndFiles.h"
#include "GlobalVariables.h"
#include "Console/console.h"
#include "UnitFuncs.h"
#include <iostream>
#include <fstream>
// add to topdata #ghosts: 3
//loop on amount of ghosts
// x y // in chars
// x y
// x y

void SortTop()
{
	for (int arr = 0; arr < 4; arr++)
	{
		int len = top[arr].size();
		for (int i = 1; i < len - 1; i++)
		{
			int min_idx = i;
			for (int j = i + 1; j < len; j++)
			{
				int digit1 = std::stoi(top[arr][j].substr(top[arr][j].find("moves: ") + 7, top[arr][j].length() - 8));
				int digit2 = std::stoi(top[arr][min_idx].substr(top[arr][min_idx].find("moves: ") + 7, top[arr][j].length() - 8));
				if (digit1 < digit2)
				{
					min_idx = j;
				}
			}
			std::swap(top[arr][min_idx], top[arr][i]);



		}
	}

}

void TopInitialize()
{
	for (int i = 0; i < 4; i++)
	{
		top.push_back({" "});
	}
}
void SavePlayerMoves()
{
	std::fstream stream;
	stream.open("TopData.txt", std::ios::app);

	int len = movesOfPlayer.size();
	for (int i = 0; i < len; i++)
	{
		stream << (char)movesOfPlayer[i];
	}
	stream << '\n';
	movesOfPlayer.clear();
	stream.close();
}
void SaveGhostsPos()
{
	std::fstream stream;
	stream.open("TopData.txt", std::ios::app);
	stream << "ghosts: " << ghostsCopy.size() << '\n';
	for (int i = 0; i < ghostsCopy.size(); i++)
	{
		stream << (char)ghostsCopy[i].xCoord << (char)ghostsCopy[i].yCoord << '\n';
	}
	ghosts.clear();
	stream.close();
}
void SaveAbility()
{
	std::fstream stream;
	stream.open("TopData.txt", std::ios::app);
	stream << "Ability: " << abilityToWalk << '\n';
	stream.close();
}
void SaveMap()
{
	std::fstream stream;
	stream.open("TopData.txt", std::ios::app);
	for (int i = 0; i < originalHeight; i++)
	{
		for (int j = 0; j < originalWidth; j++)
		{
			stream << OriginalMazeCopy[i][j];
		}
		stream << '\n';
	}
	stream.close();
	OriginalMazeCopy.clear();
	Maze.clear();
}

void SaveScore(std::string name, int moves, int mapSize)
{
	std::fstream stream;
	stream.open("TopData.txt", std::ios::app);

	stream << "#name: " << name << " #moves: " << std::to_string(moves) << " #mapSize: " << std::to_string(mapSize) << '\n';
	std::string temp = name;
	temp.append(", moves: ");
	temp.append(std::to_string(moves));
	top[mapSize].push_back(temp);
	stream.close();
	SaveMap();
	SavePlayerMoves();
	SaveAbility();
	SaveGhostsPos();
	SortTop();

}

bool isNameMoveReal(std::string seacrhName, int searchMoves)
{
	std::fstream stream;
	stream.open("TopData.txt", std::ios::in);
	int i = 0;
	std::string line;
	while (!stream.eof())
	{
		line.clear();
		std::getline(stream, line);
		if (line.empty())
		{
			break;
		}
		if (line[0] != '#')
		{
			continue;
		}
		std::string name = line.substr(line.find("#name: ") + 7, line.find("#moves: ") - 8);
		int moves = std::stoi(line.substr(line.find("#moves: ") + 8, line.find("#mapSize: ") - 8));
		if (seacrhName == name && searchMoves == moves)
		{
			return true;
		}
	}
	return false;
}

void ReadData()
{
	std::fstream stream;
	stream.open("TopData.txt", std::ios::in);
	std::string line;
	while (!stream.eof())
	{
		line.clear();
		std::getline(stream, line);
		if (line.empty())
		{
			break;
		}
		if (line[0] != '#')
		{
			continue;
		}
		std::string name = line.substr(line.find("#name: ") + 7, line.find("#moves: ") - 8);
		int moves = std::stoi(line.substr(line.find("#moves: ") + 8, line.find("#mapSize: ") - 8));
		int mapSize = 0;
		for (int j = 0; j < 4; j++) // detecting mapSize
		{
			if (j == (int)line[line.size() - 1] - 48)
			{
				mapSize = j;
				break;
			}
		}
		std::string temp = name;
		temp.append(", moves: ");
		temp.append(std::to_string(moves));
		top[mapSize].push_back(temp);
	}
	stream.close();
	SortTop();

}

void ReadMazeInfo(std::string seacrhName, int searchMoves)
{
	std::fstream stream;
	stream.open("TopData.txt", std::ios::in);

	int i = 0;
	std::string line;
	while (!stream.eof())
	{
		line.clear();
		std::getline(stream, line);
		if (line.empty())
		{
			break;
		}
		if (line[0] != '#')
		{
			continue;
		}
		std::string name = line.substr(line.find("#name: ") + 7, line.find("#moves: ") - 8);
		int moves = std::stoi(line.substr(line.find("#moves: ") + 8, line.find("#mapSize: ") - 8));
		int mapSize = 0;
		if (seacrhName == name && searchMoves == moves)
		{
			for (int j = 0; j < 4; j++) // detecting mapSize
			{
				if (j == (int)line[line.size() - 1] - 48)
				{
					mapSize = j;
					switch (mapSize)
					{
					case Tiny:
						originalWidth = 20;
						originalHeight = 20;
						break;
					case Little:
						originalWidth = 35;
						originalHeight = 35;
						break;
					case Medium:
						originalWidth = 50;
						originalHeight = 50;
						break;
					case Big:
						originalWidth = 75;
						originalHeight = 50;
						break;
					}
					break;
				}
			}
			line.clear();
			std::getline(stream, line);
			std::vector<std::vector<char>> tempMaze(originalHeight);
			for (size_t x = 0; x < originalHeight; x++)
			{
				tempMaze[x] = std::vector<char>(originalWidth);
				for (int y = 0; y < originalWidth; y++)
				{
					tempMaze[x][y] = line[y];
				}
				line.clear();
				std::getline(stream, line);
			}
			for (size_t i{ }; i < tempMaze.size(); i++)
			{
				Maze.push_back(tempMaze.at(i));
			}
			int len = line.size();
			for (int i = 0; i < len; i++)
			{
				movesOfPlayer.push_back(line[i]);
			}
			line.clear();
			std::getline(stream, line);
			abilityToWalk = line.at(line.size() - 1) - 48;
			line.clear();
			std::getline(stream, line);
			amountOfGhosts = line.at(line.size() - 1) - 48;
			ghosts.clear();
			for (int i = 0; i < amountOfGhosts; i++)
			{
				line.clear();
				std::getline(stream, line);
				ghosts.push_back(CreateGhost(line[0], line[1]));
			}
			ghostsCopy.clear();
			break;
		}
	}
	stream.close();
}

