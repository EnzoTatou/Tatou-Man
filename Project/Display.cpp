#include "Display.hpp"

void Display(GameData& _gameData)
{
	_gameData.window.clear(sf::Color::Black);

	switch (_gameData.gameState)
	{
	case(GAME):
		DisplayMap(_gameData.mapData, _gameData.window);
		DisplayPlayer(_gameData.player, _gameData.window);
		if (_gameData.newGameTimer <= 0 && _gameData.player.state != DEAD)
		{
			DisplayGhost(_gameData.enemies[BLINKY], _gameData.window);
			DisplayGhost(_gameData.enemies[CLYDE], _gameData.window);
			DisplayGhost(_gameData.enemies[INKY], _gameData.window);
			DisplayGhost(_gameData.enemies[PINKY], _gameData.window);
		}
		DisplayPlayerHUD(_gameData.player, _gameData.mapData.arr, _gameData.window);
		break;

	case(GAME_PAUSE):
		DisplayMap(_gameData.mapData, _gameData.window);
		DisplayPlayer(_gameData.player, _gameData.window);
		break;

	case(INIT_GAME):
		DisplayMap(_gameData.mapData, _gameData.window);
		DisplayPlayerHUD(_gameData.player, _gameData.mapData.arr, _gameData.window);
		break;

	default:
		break;
	}

	_gameData.window.display();
}