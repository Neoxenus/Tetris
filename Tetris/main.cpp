#include "Game.h"
#include <windows.h>


int main()
{
	//hide console
	{
		HWND Hide;
		AllocConsole();
		Hide = FindWindowA("ConsoleWindowClass", NULL);
		ShowWindow(Hide, 0);//0-hide//1-show
	}
	//variables

	Game game;
	
	return game.start();
}