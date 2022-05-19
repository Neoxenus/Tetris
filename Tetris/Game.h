#pragma once
#include "Menu.h"
#include "StatisticBox.h"
#include "Bot.h"
/// <summary>
/// Main class for tetris game. It implemented the main logic.
/// </summary>
class Game
{
public:

	Game();

	~Game();
	int start();
private://varibles
	sf::Clock clock, fpsClock;
	Cell cell;


	Field mainField, additionalField;
	Tetromino currentTetromino, nextTetromino;
	Menu menu, difficultMenu;
	Bot bot;
	sf::RenderWindow window;
	StatisticBox statistics;


	int dx = 0;
	bool rotate = false, pause = true, dMenu = false;
	bool isGameActive = false, isBot = false, isFirstAppearanceTetromino = true;
	double timer = 0, mainTimer = 0, time, fpsTimer = 0;


private:
	void eventListener();
	void FPSCounter();
	void mainUpdate();
	void draw();
	void tickOfTimer();
	void UIMenu();
	void mainMenuChoose(int key);
	void difficultMenuChoose(int key);
};

