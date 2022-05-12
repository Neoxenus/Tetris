#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <windows.h>
#include <fstream>

#include "Game.h"
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
	sf::Clock clock, fpsClock;
	Cell cell;
	Field mainField(constants::heightBlocks,constants::widthBlocks, constants::height, constants::delayEasy, constants::mainFieldOffsetX, 0),
		additionalField(constants::additonalFieldHeight, constants::widthBlocks, 0, 0, 0, constants::additionalFieldOffsetY);// static field
	Tetromino currentTetromino(mainField), nextTetromino(additionalField);
	Menu menu(constants::menuWidth, constants::menuHeight, constants::MAX_NUMBER_OPTIONS_MAIN_MENU, constants::mainMenu),
		difficultMenu(constants::menuWidth, constants::menuHeight, constants::MAX_NUMBER_OPTIONS_DIFFICULTY_MENU, constants::difficultyMenu);
	Bot bot;
	sf::RenderWindow window(sf::VideoMode(constants::windowWidth, constants::windowHeight), "Tetris", sf::Style::Titlebar | sf::Style::Close );
	
	StatisticBox statistics(constants::widthBlocks * constants::SizeOfSquare, constants::heightBlocks / 3 * constants::SizeOfSquare, 0, 2 * constants::heightBlocks / 3 * constants::SizeOfSquare);
	

	Game game(mainField, additionalField, currentTetromino, nextTetromino, menu, difficultMenu, statistics, window);
	
	return game.start();
}