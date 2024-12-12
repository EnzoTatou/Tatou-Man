#include "Init.hpp"

void Init(GameData& _gameData)
{
	srand((unsigned int)time(NULL)); // init random

	_gameData.font.loadFromFile("Data/File/Font.ttf");

	InitMap(_gameData.mapData, _gameData.font);

	sf::Vector2u windowSize = { (unsigned int)_gameData.mapData.arr.cols * TILE_SIZE, (unsigned int)_gameData.mapData.arr.rows * TILE_SIZE };
	InitWindow(_gameData.window, windowSize);

	InitPlayer(_gameData.player, _gameData.mapData.arr, _gameData.font);
	InitGhost(_gameData.enemies, _gameData.mapData.arr, _gameData.font);

	_gameData.gameStartSound = CreateSound("Data/Sound/GameStart.wav");
	_gameData.gameStartSound.play();

	_gameData.eatenSound = CreateSound("Data/Sound/Retreating.wav");
	_gameData.scatterSound = CreateSound("Data/Sound/Scatter.wav");
	_gameData.chaseSound = CreateSound("Data/Sound/Chase.wav");
	_gameData.frightenedSound = CreateSound("Data/Sound/PowerPallet.wav");

	_gameData.gameState = GAME;
}

void CheckInitState(GameData& _gameData)
{
	switch (_gameData.gameState)
	{
	case INIT_GAME:
		_gameData.newGameTimer = NEW_GAME_TIME;
		ReloadPlayer(_gameData.player, _gameData.mapData.arr);

		ReloadGhosts(_gameData.enemies);

		_gameData.mapData.bonus.textTimer = 0;
		_gameData.mapData.bonus.timer = GET_BONUS_TIME(_gameData.mapData.bonus.type);
		_gameData.mapData.bonus.visible = false;

		_gameData.gameState = GAME;
		break;
	case INIT_WIN_GAME:
		_gameData.gameStartSound.play();
		ReadMapArray(_gameData.mapData);
		_gameData.gameState = INIT_GAME;
		break;
	default:
		break;
	}
}