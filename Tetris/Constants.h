#pragma once
/// <summary>
/// Namespace with all constants of this project
/// </summary>
namespace constants
{
	//fps limit
	constexpr unsigned int maxFps = 60, maxBotFps = 240;
	constexpr double fpsCounterDelay = 0.5;
	//cells
	constexpr int SizeOfSquare = 30, CellOutlines = 1;

	//field
	constexpr int heightBlocks = 28, widthBlocks = 10, borderThickness = 1, height = 8;
	constexpr double delayEasy = 0.7, delayMedium = 0.3, delayHard = 0.15;
	constexpr int mainFieldOffsetX = constants::widthBlocks * constants::SizeOfSquare + constants::borderThickness;
	constexpr int additionalFieldOffsetY = constants::heightBlocks / 2 * constants::SizeOfSquare;
	constexpr int additonalFieldHeight = constants::heightBlocks / 6;
	//window
	constexpr int windowWidth = 2 * widthBlocks * SizeOfSquare + 3 * borderThickness;
	constexpr int windowHeight = heightBlocks * SizeOfSquare + 2 * borderThickness;

	//tetromino + cell
	constexpr int MAX_NUMBER_COLORS = 7, NUMBER_TYPES_TETROMINO = 7;
	constexpr int figures[NUMBER_TYPES_TETROMINO][4] =
	{
		{1,3,5,7}, //I
		{2,4,5,7}, //S
		{3,5,4,6}, //Z
		{3,5,4,7}, //T
		{3,5,7,2}, //L
		//{2,4,6,7}, //L
		{3,5,7,6}, //J
		//{2,4,6,3},//J
		{2,3,4,5}  //O
	};
	enum class TetrominoType
	{
		I,
		S,
		Z,
		T,
		L,
		J,
		O,
	};
	constexpr int rgb[MAX_NUMBER_COLORS][3] =
	{
		{153, 0,   153},//purple
		{204, 0,   0  },//red
		{0,   204, 0  },//green
		{230, 215, 0  },//dark yellow
		{0,   255, 255},//light blue
		{255, 128, 0  },//orange
		{0,	 0,	  204 } //blue
	};
	// font
	const std::string fontFile = "../font/arial.ttf";

	//menu
	constexpr float menuWidth = constants::widthBlocks * constants::SizeOfSquare;
	constexpr float menuHeight = constants::heightBlocks / 2 * constants::SizeOfSquare;
	constexpr int MAX_NUMBER_OPTIONS_MAIN_MENU = 5;
	constexpr int MAX_NUMBER_OPTIONS_DIFFICULTY_MENU = 5;
	const std::string mainMenu[MAX_NUMBER_OPTIONS_MAIN_MENU] =
	{
		"New game",
		"Pause",
		"Stop game",
		"Choose Difficulty",
		"Bot"
	};
	const std::string difficultyMenu[MAX_NUMBER_OPTIONS_DIFFICULTY_MENU] =
	{
		"Easy",
		"Medium",
		"Hard",
		"Dynamic",
		"Back"
	};
	//statistics
	constexpr float statBoxWidth = constants::widthBlocks * constants::SizeOfSquare;
	constexpr float statBoxHeight = constants::heightBlocks / 3 * constants::SizeOfSquare;
	constexpr int statBoxPosY = constants::heightBlocks * 2 / 3 * constants::SizeOfSquare;
	constexpr long long score[5] = {//score for clearing lines 
		0   ,//no lines
		40 ,//1 line
		100 ,//2 lines
		300 ,//3 lines
		1200 //4 lines
	};
	constexpr int MAX_NUMBER_OF_STATISTICS_ITEMS = 6;
	const std::string statisticsText[MAX_NUMBER_OF_STATISTICS_ITEMS] =
	{
		"Difficulty:\t",
		"Score:\t",
		"Lines:\t",
		"Time:\t",
		"Bot:\t",
		"FPS:\t"
	};
	enum class Stat
	{
		DIFFICULTY,
		SCORE,
		LINES,
		TIME,
		BOT,
		FPS,
	};
	enum class Difficulty
	{
		EASY = 1,
		MEDIUM = 2,
		HARD,
		DYNAMIC,
	};

	//Bot
	constexpr int BestState = 100000000, isOver = -100000000;

	
}