#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <windows.h>
#include <fstream>

#include "Tetromino.h"
#include "Menu.h"
#include "StatisticBox.h"
#include "Bot.h"
int main()
{
	unsigned int maxFps = 60, maxBotFps = 240;
	std::ofstream cerrFile("../Logs/CERR.txt");
	std::cerr.rdbuf(cerrFile.rdbuf());

	void (*Hide)(){
		[]()
		{
			HWND Hide;
			AllocConsole();
			Hide = FindWindowA("ConsoleWindowClass", NULL);
			ShowWindow(Hide, 0);
		}
	};
	Hide();
	sf::Clock clock, fpsClock;
	Cell cell;
	Field A(constants::M, constants::N, constants::height, constants::delayEasy, constants::N * constants::SizeOfSquare + constants::borderThickness, 0),
		B(constants::M/6, constants::N, 0, 0, 0, constants::M / 2 * constants::SizeOfSquare);// static field
	Tetromino currentTetromino(A), nextTetromino(B);
	Menu menu(constants::N * constants::SizeOfSquare, constants::M / 2 * constants::SizeOfSquare,
		constants::MAX_NUMBER_OPTIONS_MAIN_MENU, constants::mainMenu),
		difficultMenu(constants::N * constants::SizeOfSquare, constants::M / 2 * constants::SizeOfSquare,
		constants::MAX_NUMBER_OPTIONS_DIFFICULTY_MENU, constants::difficultyMenu);
	Bot bot;
	sf::RenderWindow window(sf::VideoMode(constants::windowWidth, constants::windowHeight), "Tetris", sf::Style::Titlebar | sf::Style::Close );
	
	window.setFramerateLimit(maxFps);

	StatisticBox statistics(constants::N * constants::SizeOfSquare, constants::M / 3 * constants::SizeOfSquare, 0, 2 * constants::M / 3 * constants::SizeOfSquare);
	int dx = 0;
	bool rotate = false, pause = false, dMenu = false;
	bool isGameActive = false, isBot = false, isFirstAppearanceTetromino = true;
	double timer = 0, mainTimer = 0, time, fpsTimer = 0;

	A.SetDefaultDelay(constants::delayEasy);
	statistics.SetStatistics(static_cast<int>(constants::Difficulty::EASY), static_cast<int>(constants::Stat::DIFFICULTY));
	statistics.SetStatistics(0, static_cast<int>(constants::Stat::FPS));
	while (window.isOpen())
	{
		//fps counter
		fpsTimer += fpsClock.getElapsedTime().asMilliseconds();
		fpsClock.restart().asMilliseconds(); static unsigned int numOfTicks = 0;
		numOfTicks++;
		if (fpsTimer/1000 > 0.5)
		{
			statistics.SetStatistics(numOfTicks *1.0 / (fpsTimer/1000), static_cast<int>(constants::Stat::FPS));
			numOfTicks = 0;
			fpsTimer = 0;
		}	



		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::LostFocus)
				pause = true;
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				int x = sf::Mouse::getPosition(window).x, y = sf::Mouse::getPosition(window).y;
				//std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
				//std::cout << menu.choose(x, y) << std::endl;
				if(!dMenu)
				switch (menu.choose(x, y))
				{
				case 0:
					isGameActive = true;
					timer = 0; mainTimer = 0, time = 0;
					pause = false;
					A.clearField();
					statistics.SetStatistics(0, static_cast<int>(constants::Stat::SCORE));
					statistics.SetStatistics(0, static_cast<int>(constants::Stat::LINES));
					statistics.SetStatistics(0, static_cast<int>(constants::Stat::TIME));
					currentTetromino.newTetromino(A);
					nextTetromino.newTetromino(B);
					if (isBot)
						window.setFramerateLimit(maxBotFps);
					break;
				case 1:
					if(isGameActive)
						pause = !pause;
					break;
				case 2://stop
					isGameActive = false;
					break;
				case 3:
					pause = true;
					dMenu = true;
					break;
				case 4:
					isBot = !isBot;
					if (isBot)
						window.setFramerateLimit(maxBotFps);
					else
						window.setFramerateLimit(maxFps);
					if(isGameActive)
						bot.analysis(currentTetromino, nextTetromino, A);
					if (isBot)
						statistics.SetStatistics(1, static_cast<int>(constants::Stat::BOT));
					else
						statistics.SetStatistics(0, static_cast<int>(constants::Stat::BOT));
					break;
				default:
					//std::cout << "Something wrong with mouse coordinate\n";
					break;	
				}
				else
					switch (difficultMenu.choose(x, y))
					{
					case 4:
						dMenu = false;
						break;
					isGameActive = false;
					case 0:
						A.SetDefaultDelay(constants::delayEasy);
						statistics.SetStatistics(static_cast<int>(constants::Difficulty::EASY), static_cast<int>(constants::Stat::DIFFICULTY));
						break;
					case 1:
						A.SetDefaultDelay(constants::delayMedium);
						statistics.SetStatistics(static_cast<int>(constants::Difficulty::MEDIUM), static_cast<int>(constants::Stat::DIFFICULTY));
						break;
					case 2:
						A.SetDefaultDelay(constants::delayHard);
						statistics.SetStatistics(static_cast<int>(constants::Difficulty::HARD), static_cast<int>(constants::Stat::DIFFICULTY));
						break;
					case 3:
						A.setDynamicDelay();
						statistics.SetStatistics(static_cast<int>(constants::Difficulty::DYNAMIC), static_cast<int>(constants::Stat::DIFFICULTY));
						break;
					}

			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape && isGameActive)
				{
					pause = !pause;
				}
				if (isBot || pause)
					continue;
				if (isGameActive)
				{
					if (event.key.code == sf::Keyboard::Up)
						rotate = true;
					else if (event.key.code == sf::Keyboard::Left)
						dx = -1;
					else if (event.key.code == sf::Keyboard::Right)
						dx = 1;
				}
			}
			
		}



		if  (isBot && isGameActive)
		{
			if (isFirstAppearanceTetromino)
			{
				bot.analysis(currentTetromino,nextTetromino,  A);
				isFirstAppearanceTetromino = false;
			}	
			if (!pause)
			{
				rotate = bot.Get_isRotate();
				dx = bot.Get_dx();
			}
		}
		if(!pause && isGameActive)
		{

			time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time; mainTimer += time;
			statistics.SetStatistics(mainTimer, static_cast<int>(constants::Stat::TIME));
			A.updateDynamicDelay(mainTimer);
			if (pause)
				continue;
			if (isBot && bot.readyToFall())
				A.SetDelay(A.GetDelay() / std::pow(50, statistics.GetStatistics(static_cast<int>(constants::Stat::DIFFICULTY))));
			if(!isBot && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				A.SetDelay(A.GetDelay() / 10);
			//left and right moving
			currentTetromino.horizontalMoving(A, dx);

			//rotating
			if (rotate)
				currentTetromino.rotate(A);
			//fps counter

			//tick of timer
			if (timer > A.GetDelay())
			{
				if (currentTetromino.falling(A))
				{
					int numberOfLines = A.update();
					statistics.SetStatistics(statistics.GetStatistics(static_cast<int>(constants::Stat::SCORE)) + constants::score[numberOfLines], static_cast<int>(constants::Stat::SCORE));
					statistics.SetStatistics(statistics.GetStatistics(static_cast<int>(constants::Stat::LINES)) + numberOfLines, static_cast<int>(constants::Stat::LINES));
					if (A.isOver())
					{
						mainTimer = 0;
						time = 0;
						clock.restart();
						isGameActive = false;
						window.setFramerateLimit(maxFps);
					}
					
					currentTetromino = nextTetromino;
					nextTetromino.newTetromino(B);
					isFirstAppearanceTetromino = true;
				}

				timer = 0;
			}
			dx = 0; rotate = false;
			A.ResetDelay();
		}

		
		//drawing
		window.clear(sf::Color::Black);
		if (isGameActive)
		{
			currentTetromino.draw(window, cell, A);
			nextTetromino.draw(window, cell, B);
		}
		statistics.draw(window);
		A.draw(window, cell);
		B.draw(window, cell);
		if (dMenu)
			difficultMenu.draw(window);
		else
			menu.draw(window);
		window.display();
	}
	cerrFile.close();
	return 0;
}