#include "Update.hpp"

void PauseSounds(GameData& _gameData)
{
	_gameData.scatterSound.pause();
	_gameData.chaseSound.pause();
	_gameData.frightenedSound.pause();
	_gameData.eatenSound.pause();
}

void UpdateSounds(GameData& _gameData)
{
	// play frightenedSound if one of the ghost is frightened else we stop the sound and play the chase one to replace it
	if ((_gameData.enemies[BLINKY].state == EATEN ||
		_gameData.enemies[PINKY].state == EATEN ||
		_gameData.enemies[INKY].state == EATEN ||
		_gameData.enemies[CLYDE].state == EATEN) && _gameData.newGameTimer <= 0 && _gameData.player.state != DEAD)
	{
		PlaySoundOnRepeat(_gameData.eatenSound);
		_gameData.scatterSound.stop();
		_gameData.chaseSound.stop();
		_gameData.frightenedSound.stop();
	}
	else if ((_gameData.enemies[BLINKY].state == FRIGHTENED ||
		_gameData.enemies[PINKY].state == FRIGHTENED ||
		_gameData.enemies[INKY].state == FRIGHTENED ||
		_gameData.enemies[CLYDE].state == FRIGHTENED) && _gameData.newGameTimer <= 0 && _gameData.player.state != DEAD)
	{
		PlaySoundOnRepeat(_gameData.frightenedSound);
		_gameData.scatterSound.stop();
		_gameData.chaseSound.stop();
		_gameData.eatenSound.stop();
	}
	else if ((_gameData.enemies[BLINKY].state == CHASE ||
		_gameData.enemies[PINKY].state == CHASE ||
		_gameData.enemies[INKY].state == CHASE ||
		_gameData.enemies[CLYDE].state == CHASE) && _gameData.newGameTimer <= 0 && _gameData.player.state != DEAD)
	{
		PlaySoundOnRepeat(_gameData.chaseSound);
		_gameData.scatterSound.stop();
		_gameData.frightenedSound.stop();
		_gameData.eatenSound.stop();
	}
	else if (_gameData.newGameTimer <= 0 && _gameData.player.state != DEAD)
	{
		PlaySoundOnRepeat(_gameData.scatterSound);
		_gameData.chaseSound.stop();
		_gameData.frightenedSound.stop();
		_gameData.eatenSound.stop();
	}
	else
	{
		_gameData.scatterSound.stop();
		_gameData.chaseSound.stop();
		_gameData.frightenedSound.stop();
		_gameData.eatenSound.stop();
	}
}

void Update(GameData& _gameData)
{
	float dt = _gameData.clock.restart().asSeconds();
	if (dt >= 0.1)
	{
		dt = 0.1;	// if deltaTime is too big the game let the ghost past trough the wall
	}

	UpdateKeyData(_gameData.keyData);

	switch (_gameData.gameState)
	{
	case(CLOSE):
		_gameData.window.close(); // close the game
		break;

	case(GAME):
		// stoped the game when player eat a ghost (the eating sound is the "timer" for this condition)
		if (_gameData.newGameTimer <= 0 && _gameData.player.eatSounds[2].getStatus() == STOPPED)
		{
			UpdatePlayer(_gameData.player, _gameData.gameState, _gameData.mapData, _gameData.keyData, dt);
			if (_gameData.player.state != DEAD)
			{
				UpdateGhost(_gameData.enemies[BLINKY], _gameData.enemies[BLINKY], _gameData.player, _gameData.mapData, dt);
				UpdateGhost(_gameData.enemies[CLYDE], _gameData.enemies[BLINKY], _gameData.player, _gameData.mapData, dt);
				UpdateGhost(_gameData.enemies[INKY], _gameData.enemies[BLINKY], _gameData.player, _gameData.mapData, dt);
				UpdateGhost(_gameData.enemies[PINKY], _gameData.enemies[BLINKY], _gameData.player, _gameData.mapData, dt);

				UpdateMap(_gameData.mapData, _gameData.gameState, dt);
			}
		}
		else
		{
			_gameData.newGameTimer -= dt;
		}

		UpdateSounds(_gameData);

		break;

	case(GAME_PAUSE):
		PauseSounds(_gameData);
		break;

	default:
		break;
	}
}