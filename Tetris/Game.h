#pragma once
#include "Tetromino.h"
#include "Menu.h"
#include "StatisticBox.h"
#include "Bot.h"
#include "Constants.h"
class Game
{
public:
	Game(Field& main, Field& secondary, Tetromino& cur, Tetromino& next, Menu& menu, Menu& diff,  StatisticBox& stat, sf::RenderWindow& window) :
		mainField(main), additionalField(secondary), currentTetromino(cur), nextTetromino(next), menu(menu), difficultMenu(diff), window(window), statistics(stat)
	{	
		this->window.setFramerateLimit(constants::maxFps);
		dx = 0;
		rotate = false;
		pause = true;
		dMenu = false;
		isGameActive = false;
		isBot = false;
		isFirstAppearanceTetromino = true;
		timer = 0;
		mainTimer = 0;
		fpsTimer = 0;
		mainField.SetDefaultDelay(constants::delayEasy);
		statistics.SetStatistics(static_cast<int>(constants::Difficulty::EASY), static_cast<int>(constants::Stat::DIFFICULTY));
		statistics.SetStatistics(0, static_cast<int>(constants::Stat::FPS));
	}
	~Game();
	int start();
private://varibles
	sf::Clock clock, fpsClock;
	Cell cell;


	Field& mainField, &additionalField;
	Tetromino& currentTetromino, nextTetromino;
	Menu menu, difficultMenu;
	Bot bot;
	sf::RenderWindow& window;
	StatisticBox& statistics;


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

