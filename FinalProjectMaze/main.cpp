#include <vector>
#include <iostream>
#include <windows.h>
#include "UI.h"
#include "GlobalVariables.h"
#include "TopAndFiles.h"

void StartGame()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	TopInitialize();
	ReadData();
	PrintMenu();
}

int main()
{ 
	StartGame();
}
