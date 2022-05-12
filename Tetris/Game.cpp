#include "Game.h"
Game::Game() :
	mainField(constants::heightBlocks, constants::widthBlocks, constants::height, constants::delayEasy, constants::mainFieldOffsetX, 0),
	additionalField(constants::additonalFieldHeight, constants::widthBlocks, 0, 0, 0, constants::additionalFieldOffsetY),// static field
	currentTetromino(mainField), nextTetromino(additionalField),
	menu(constants::menuWidth, constants::menuHeight, constants::MAX_NUMBER_OPTIONS_MAIN_MENU, constants::mainMenu),
	difficultMenu(constants::menuWidth, constants::menuHeight, constants::MAX_NUMBER_OPTIONS_DIFFICULTY_MENU, constants::difficultyMenu),
	statistics(constants::statBoxWidth, constants::statBoxHeight, 0, constants::statBoxPosY),
	window(sf::VideoMode(constants::windowWidth, constants::windowHeight), "Tetris", sf::Style::Titlebar | sf::Style::Close)
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

Game::~Game()
{
}

int Game::start()
{
	while (window.isOpen())
	{
		//fps counter
		this->FPSCounter();

		this->eventListener();

		if (isBot && isGameActive){
			if (isFirstAppearanceTetromino){
				bot.analysis(currentTetromino, nextTetromino, mainField);
				isFirstAppearanceTetromino = false;
			}
			if (!pause){
				rotate = bot.Get_isRotate();
				dx = bot.Get_dx();
			}
		}
		if (!pause && isGameActive)
			mainUpdate();
		this->draw();
	}
	return 0;
}

void Game::eventListener()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::LostFocus)
			pause = true;
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			this->UIMenu();
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
}

void Game::FPSCounter()
{
	fpsTimer += fpsClock.getElapsedTime().asMilliseconds();
	fpsClock.restart().asMilliseconds(); static unsigned int numOfTicks = 0;
	numOfTicks++;
	if (fpsTimer / 1000 > constants::fpsCounterDelay)
	{
		statistics.SetStatistics(numOfTicks * 1.0 / (fpsTimer / 1000), static_cast<int>(constants::Stat::FPS));
		numOfTicks = 0;
		fpsTimer = 0;
	}
}

void Game::mainUpdate()
{
	time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timer += time; mainTimer += time;
	statistics.SetStatistics(mainTimer, static_cast<int>(constants::Stat::TIME));
	mainField.updateDynamicDelay(mainTimer);
	if (isBot && bot.readyToFall())
		mainField.SetDelay(mainField.GetDelay() / std::pow(50, statistics.GetStatistics(static_cast<int>(constants::Stat::DIFFICULTY))));
	if (!isBot && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		mainField.SetDelay(mainField.GetDelay() / 10);
	//left and right moving
	currentTetromino.horizontalMoving(dx);

	//rotating
	if (rotate)
		currentTetromino.rotate();
	//fps counter

	//tick of timer
	if (timer > mainField.GetDelay())
		this->tickOfTimer();
	dx = 0; rotate = false;
	mainField.ResetDelay();
}

void Game::draw()
{
	window.clear(sf::Color::Black);
	if (isGameActive)
	{
		currentTetromino.draw(window, cell);
		nextTetromino.draw(window, cell);
	}
	statistics.draw(window);
	mainField.draw(window, cell);
	additionalField.draw(window, cell);
	if (dMenu)
		difficultMenu.draw(window);
	else
		menu.draw(window);
	window.display();
}

void Game::tickOfTimer()
{
	if (currentTetromino.falling())
	{
		int numberOfLines = mainField.update();
		statistics.SetStatistics(statistics.GetStatistics(static_cast<int>(constants::Stat::SCORE)) + constants::score[numberOfLines], static_cast<int>(constants::Stat::SCORE));
		statistics.SetStatistics(statistics.GetStatistics(static_cast<int>(constants::Stat::LINES)) + numberOfLines, static_cast<int>(constants::Stat::LINES));
		if (mainField.isOver())
		{
			mainTimer = 0;
			time = 0;
			clock.restart();
			isGameActive = false;
			window.setFramerateLimit(constants::maxFps);
		}

		currentTetromino = nextTetromino;
		nextTetromino.newTetromino(additionalField);
		isFirstAppearanceTetromino = true;
	}

	timer = 0;
}

void Game::UIMenu()
{
	int x = sf::Mouse::getPosition(window).x, y = sf::Mouse::getPosition(window).y;
	if (!dMenu)
		this->mainMenuChoose(menu.choose(x, y));
	else
		this->difficultMenuChoose(difficultMenu.choose(x, y));		
}

void Game::mainMenuChoose(int key)
{
	switch (key)
	{
	case 0://new game
		isGameActive = true;
		clock.restart();
		timer = 0; mainTimer = 0, time = 0;
		pause = false;
		mainField.clearField();
		statistics.SetStatistics(0, static_cast<int>(constants::Stat::SCORE));
		statistics.SetStatistics(0, static_cast<int>(constants::Stat::LINES));
		statistics.SetStatistics(0, static_cast<int>(constants::Stat::TIME));
		currentTetromino.newTetromino(mainField);
		nextTetromino.newTetromino(additionalField);
		if (isBot)
			window.setFramerateLimit(constants::maxBotFps);
		break;
	case 1://pause
		if (isGameActive)
			pause = !pause;
		break;
	case 2://stop
		isGameActive = false;
		break;
	case 3://difficulty
		pause = true;
		dMenu = true;
		break;
	case 4://bot
		isBot = !isBot;
		if (isBot)
			window.setFramerateLimit(constants::maxBotFps);
		else
			window.setFramerateLimit(constants::maxFps);
		if (isGameActive)
			bot.analysis(currentTetromino, nextTetromino, mainField);
		if (isBot)
			statistics.SetStatistics(1, static_cast<int>(constants::Stat::BOT));
		else
			statistics.SetStatistics(0, static_cast<int>(constants::Stat::BOT));
		break;
	default:
		//std::cout << "Something wrong with mouse coordinate\n";
		break;
	}
}

void Game::difficultMenuChoose(int key)
{
	switch (key)
	{
	case 4://back to main menu
		dMenu = false;
		break;
		isGameActive = false;
	case 0://easy
		mainField.SetDefaultDelay(constants::delayEasy);
		statistics.SetStatistics(static_cast<int>(constants::Difficulty::EASY), static_cast<int>(constants::Stat::DIFFICULTY));
		break;
	case 1://medium
		mainField.SetDefaultDelay(constants::delayMedium);
		statistics.SetStatistics(static_cast<int>(constants::Difficulty::MEDIUM), static_cast<int>(constants::Stat::DIFFICULTY));
		break;
	case 2://hard
		mainField.SetDefaultDelay(constants::delayHard);
		statistics.SetStatistics(static_cast<int>(constants::Difficulty::HARD), static_cast<int>(constants::Stat::DIFFICULTY));
		break;
	case 3://dynamic
		mainField.setDynamicDelay();
		statistics.SetStatistics(static_cast<int>(constants::Difficulty::DYNAMIC), static_cast<int>(constants::Stat::DIFFICULTY));
		break;
	}
}
