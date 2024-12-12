#include "Event.hpp"

void Event(GameData& _gameData)
{
	while (_gameData.window.pollEvent(_gameData.event))
	{
		// Event that play whatever the state of the game
		switch (_gameData.event.type)
		{
		case(sf::Event::Closed):
			_gameData.gameState = CLOSE;
			break;
		case(sf::Event::MouseMoved):
			break;
		default:
			break;
		}

		switch (_gameData.gameState)
		{
		case GAME:
			switch (_gameData.event.type)
			{
			case(sf::Event::KeyPressed):
				if (_gameData.event.key.code == sf::Keyboard::Escape)
				{
					if (_gameData.newGameTimer <= 0 && _gameData.player.eatSounds[2].getStatus() == STOPPED && _gameData.player.state != DEAD)
					{
						_gameData.gameState = GAME_PAUSE;
					}
				}
				break;
			default:
				break;
			}
			break;

		case GAME_PAUSE:
			switch (_gameData.event.type)
			{
			case(sf::Event::KeyPressed):
				if (_gameData.event.key.code == sf::Keyboard::Escape)
				{
					_gameData.gameState = GAME;
				}
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}