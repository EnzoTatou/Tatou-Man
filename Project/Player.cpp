#include "Player.hpp"

void InitPlayer(Player& _player, MapArray& _mapArray, sf::Font& _font)
{
	_player.scoreText = CreateText(_font, "score 0", 14, sf::Color::White);
	_player.scoreText.setPosition(1.f, 4.f);

	_player.walkSprite[0] = LoadSprite("Data/Sprite/Tatou/Tatou0.png", true);
	_player.walkSprite[1] = LoadSprite("Data/Sprite/Tatou/Tatou1.png", true);
	_player.walkSprite[2] = LoadSprite("Data/Sprite/Tatou/Tatou2.png", true);
	_player.walkSprite[3] = _player.walkSprite[0];

	_player.walkAnimation = CreateAnimation(4, 0.25f, _player.walkSprite);

	_player.deathSprite[0] = _player.walkSprite[2];
	_player.deathSprite[1] = LoadSprite("Data/Sprite/Tatou/Tatou3.png", true);
	_player.deathSprite[2] = LoadSprite("Data/Sprite/Tatou/Tatou4.png", true);
	_player.deathSprite[3] = LoadSprite("Data/Sprite/Tatou/Tatou5.png", true);
	_player.deathSprite[4] = LoadSprite("Data/Sprite/Tatou/Tatou6.png", true);
	_player.deathSprite[5] = LoadSprite("Data/Sprite/Tatou/Tatou7.png", true);
	_player.deathSprite[6] = LoadSprite("Data/Sprite/Tatou/Tatou8.png", true);
	_player.deathSprite[7] = LoadSprite("Data/Sprite/Tatou/Tatou9.png", true);
	_player.deathSprite[8] = LoadSprite("Data/Sprite/Tatou/Tatou10.png", true);

	_player.deathAnimation = CreateAnimation(9, 1.25f, _player.deathSprite);

	_player.deathSounds[0] = CreateSound("Data/Sound/TatouMan/Death0.wav");
	_player.deathSounds[1] = CreateSound("Data/Sound/TatouMan/Death1.wav");

	_player.eatSounds[0] = CreateSound("Data/Sound/TatouMan/Munch0.wav");
	_player.eatSounds[1] = CreateSound("Data/Sound/TatouMan/Munch1.wav");
	_player.eatSounds[2] = CreateSound("Data/Sound/TatouMan/EatGhost.wav");
	_player.eatSounds[3] = CreateSound("Data/Sound/TatouMan/EatFruit.wav");

	_player.newLifeSound = CreateSound("Data/Sound/TatouMan/Extend.wav");

	for (int i = 0; i < _mapArray.rows; i++)
	{
		for (int j = 0; j < _mapArray.cols; j++)
		{
			if (_mapArray.data[i][j] == SPAWN_TATOU)
			{
				sf::Vector2f spawnPos = { (float)j * TILE_SIZE + 16.f, (float)i * TILE_SIZE + 16.f };
				_player.oldPos = spawnPos;
				_player.currentPos = spawnPos;
			}
		}
	}
}

void ReloadPlayer(Player& _player, MapArray& _mapArray)
{
	for (int i = 0; i < _mapArray.rows; i++)
	{
		for (int j = 0; j < _mapArray.cols; j++)
		{
			if (_mapArray.data[i][j] == SPAWN_TATOU)
			{
				sf::Vector2f spawnPos = { (float)j * TILE_SIZE + TILE_SIZE / 2, (float)i * TILE_SIZE + TILE_SIZE / 2 };
				
				_player.oldPos = spawnPos;
				_player.currentPos = spawnPos;
			}
		}
	}

	_player.walkAnimation.currentSprite = &_player.walkAnimation.spriteArray[1];
	_player.deadTimer = DEATH_TIME;

	_player.newDir = RIGHT;
	_player.currentDir = RIGHT;

	_player.state = ALIVE;
}

sf::FloatRect GetPlayerCollisionRect(Player& _player)
{
	return { _player.currentPos.x - 8, _player.currentPos.y - 8, 16, 16 };
}

bool IsCollidingPlayer(Player& _player, sf::FloatRect _obj)
{
	sf::FloatRect playerRect = GetPlayerCollisionRect(_player);

	return IsCollidingRectangles(playerRect, _obj);
}

sf::FloatRect GetPlayerSpriteRect(Player& _player)
{
	return { _player.currentPos.x - 16, _player.currentPos.y - 16, 32, 32 };
}

sf::Vector2i GetPlayerArrayIndex(Player _player)
{
	sf::Vector2i arrayIndex;

	arrayIndex.x = int(_player.currentPos.x) / TILE_SIZE;
	arrayIndex.y = int(_player.currentPos.y) / TILE_SIZE;

	return arrayIndex;
}

bool IsPlayerCollideWall(Player& _player, std::vector<Wall> _walls)
{
	bool collision = false;
	sf::FloatRect playerRectangle = GetPlayerSpriteRect(_player);

	for (int i = 0; i < _walls.size(); i++)
	{
		sf::FloatRect wallRectangle = { _walls[i].pos.x, _walls[i].pos.y, 32, 32 };
		if (IsCollidingRectangles(playerRectangle, wallRectangle))
		{
			collision = true;
		}
	}

	return collision;
}

void ChangePlayerDir(Player& _player, std::vector<Wall> _walls, float _dt)
{
	if (_player.currentDir == UP || _player.currentDir == DOWN)
	{
		float diffY = _player.currentPos.y - _player.oldPos.y; // offset (because of speed)
		diffY *= diffY;
		diffY = sqrt(diffY); // make the offset positif
		int posY = int(_player.currentPos.y) % TILE_SIZE;

		if (_player.newDir == UP || _player.newDir == DOWN)
		{
			_player.currentDir = _player.newDir;
		}
		else if (posY >= TILE_SIZE / 2 - diffY && posY <= TILE_SIZE / 2 + diffY)
		{
			sf::Vector2f currentPos = _player.currentPos;
			if (_player.newDir == LEFT)
			{
				_player.currentPos.x -= _player.speed * _dt;
			}
			else if (_player.newDir == RIGHT)
			{
				_player.currentPos.x += _player.speed * _dt;
			}
			_player.currentPos.y = int(_player.currentPos.y) + TILE_SIZE / 2 - int(_player.currentPos.y) % TILE_SIZE; // set the player in the right position

			if (!IsPlayerCollideWall(_player, _walls))
			{
				_player.currentDir = _player.newDir;
			}
			else
			{
				_player.currentPos = currentPos;
			}
		}
	}
	else if (_player.currentDir == LEFT || _player.currentDir == RIGHT)
	{
		float diffX = _player.currentPos.x - _player.oldPos.x;
		diffX *= diffX;
		diffX = sqrt(diffX);
		int posX = int(_player.currentPos.x) % TILE_SIZE;

		if (_player.newDir == LEFT || _player.newDir == RIGHT)
		{
			_player.currentDir = _player.newDir;
		}
		else if (posX >= TILE_SIZE / 2 - diffX && posX <= TILE_SIZE / 2 + diffX)
		{ 
			sf::Vector2f currentPos = _player.currentPos;
			if (_player.newDir == UP)
			{
				_player.currentPos.y -= _player.speed * _dt;
			}
			else if (_player.newDir == DOWN)
			{
				_player.currentPos.y += _player.speed * _dt;
			}
			_player.currentPos.x = int(_player.currentPos.x) + TILE_SIZE / 2 - int(_player.currentPos.x) % TILE_SIZE; // set the player in the right position

			if (!IsPlayerCollideWall(_player, _walls))
			{
				_player.currentDir = _player.newDir;
			}
			else
			{
				_player.currentPos = currentPos;
			}
		}
	}
}

void UpdatePlayerNewDir(Player& _player, std::vector<Wall> _walls, KeyData& _keyData, float _dt)
{
	if (IsKeyPressed(_player.key.up, _keyData))
	{
		_player.newDir = UP;
	}
	else if (IsKeyPressed(_player.key.down, _keyData))
	{
		_player.newDir = DOWN;
	}
	else if (IsKeyPressed(_player.key.left, _keyData))
	{
		_player.newDir = LEFT;
	}
	else if (IsKeyPressed(_player.key.right, _keyData))
	{
		_player.newDir = RIGHT;
	}

	ChangePlayerDir(_player, _walls, _dt);
}

void CheckPlayerOutOfBounds(Player& _player, MapArray& _mapArray)
{
	if (_player.currentPos.x > _mapArray.cols * TILE_SIZE)
	{
		_player.currentPos.x = 1;
		_player.currentDir = RIGHT;
		_player.newDir = RIGHT;
	}
	else if (_player.currentPos.x < 0)
	{
		_player.currentPos.x = _mapArray.cols * TILE_SIZE - 1;
		_player.currentDir = LEFT;
		_player.newDir = LEFT;
	}
}

void CheckPlayerCollideWalls(Player& _player, std::vector<Wall> _walls)
{
	if (IsPlayerCollideWall(_player, _walls))
	{
		if (_player.currentDir == UP)
		{
			_player.currentPos.y = int(_player.currentPos.y) + TILE_SIZE / 2 - int(_player.currentPos.y) % TILE_SIZE;
		}
		else if (_player.currentDir == DOWN)
		{
			_player.currentPos.y = int(_player.currentPos.y) + TILE_SIZE / 2 - int(_player.currentPos.y) % TILE_SIZE;
		}
		else if (_player.currentDir == LEFT)
		{
			_player.currentPos.x = int(_player.currentPos.x) + TILE_SIZE / 2 - int(_player.currentPos.x) % TILE_SIZE;
		}
		else if (_player.currentDir == RIGHT)
		{
			_player.currentPos.x = int(_player.currentPos.x) + TILE_SIZE / 2 - int(_player.currentPos.x) % TILE_SIZE;
		}
	}
}

void MovePlayer(Player& _player, float _dt)
{
	_player.oldPos = _player.currentPos;

	if (_player.currentDir == UP)
	{
		_player.currentPos.y -= _player.speed * _dt;
	}
	else if (_player.currentDir == DOWN)
	{
		_player.currentPos.y += _player.speed * _dt;
	}
	else if (_player.currentDir == LEFT)
	{
		_player.currentPos.x -= _player.speed * _dt;
	}
	else if (_player.currentDir == RIGHT)
	{
		_player.currentPos.x += _player.speed * _dt;
	}
	else
	{
		std::cerr << "no direction found for player." << std::endl;
	}
}

void UpdatePlayerAnimation(Player& _player, float _dt)
{
	if (_player.oldPos != _player.currentPos)
	{
		UpdateAnimation(_player.walkAnimation, _dt);
	}
	else
	{
		_player.walkAnimation.currentSprite = &_player.walkAnimation.spriteArray[2]; // set "idle" sprite
	}
}

void CheckPlayerTouchDot(Player& _player, std::vector<sf::Vector2f>& _dotsPos)
{
	sf::FloatRect playerRectangle = GetPlayerCollisionRect(_player); // get player rectangle
	for (int i = 0; i < _dotsPos.size(); i++)
	{
		sf::Vector2f dotPosition = { _dotsPos[i].x + TILE_SIZE / 2, _dotsPos[i].y + TILE_SIZE / 2 };
		if (IsCollidingRectanglePoint(playerRectangle, dotPosition))
		{
			_player.score += 10; // update score
			_dotsPos.erase(_dotsPos.begin() + i); // erase dot from vector
			// if the sound play everytime we eat a dot we can dotNum % 2 to play the correct sound
			_player.eatSounds[_dotsPos.size() % 2].play();
		}
	}
}

void CheckPlayerTouchGum(Player& _player, std::vector<sf::Vector2f>& _gumsPos)
{
	sf::FloatRect playerRectangle = GetPlayerCollisionRect(_player); // get player rectangle
	for (int i = 0; i < _gumsPos.size(); i++)
	{
		sf::Vector2f dotPosition = { _gumsPos[i].x + TILE_SIZE / 2, _gumsPos[i].y + TILE_SIZE / 2 };
		if (IsCollidingRectanglePoint(playerRectangle, dotPosition))
		{
			_player.state = EAT_GUM;
			_player.score += 50; // update score
			_gumsPos.erase(_gumsPos.begin() + i); // erase gum from vector
			_player.eatSounds[0].play(); // play eat sound
		}
	}
}

void CheckPlayerTouchBonus(Player& _player, Bonus& _bonus)
{
	if (_bonus.visible)
	{
		sf::FloatRect playerRect = GetPlayerCollisionRect(_player);
		sf::FloatRect bonusRect = GetBonusRect(_bonus);
		if (IsCollidingRectangles(playerRect, bonusRect))
		{
			_player.score += GetBonusPoint(_bonus); // update score
			EatBonus(_bonus); // set the new bonus
			_player.eatSounds[3].play();
		}
	}
}

void UpdatePlayer(Player& _player, GameState& _gameState, MapData& _mapData, KeyData& _keyData, float _dt)
{
	if (_player.state == DEAD)
	{
		if (_player.deadTimer > 0)
		{
			_player.deadTimer -= _dt;
			UpdateAnimation(_player.deathAnimation, _dt);
		}
		else if (_player.life > 0)
		{
			_player.deathSounds[0].stop();
			_player.deathSounds[1].play(); // play end death sound
			_player.life--;
			_gameState = INIT_GAME; // set the game state to initialise the new game loop
		}
	}
	else
	{
		if (_player.state == EAT_GUM)
		{
			_player.state = ALIVE;
		}

		if (_player.score > _player.newLifeScore)
		{
			_player.newLifeScore += 10000;
			_player.life++;
			_player.newLifeSound.play();
		}

		UpdatePlayerNewDir(_player, _mapData.walls, _keyData, _dt);
		MovePlayer(_player, _dt);
		CheckPlayerCollideWalls(_player, _mapData.walls);
		CheckPlayerOutOfBounds(_player, _mapData.arr);
		UpdatePlayerAnimation(_player, _dt);

		CheckPlayerTouchDot(_player, _mapData.dotsPos);
		CheckPlayerTouchGum(_player, _mapData.gumsPos);
		CheckPlayerTouchBonus(_player, _mapData.bonus);

		_player.scoreText.setString("Score " + std::to_string(_player.score)); // update the score string to corespond player score
	}
}

void DisplayPlayer(Player& _player, sf::RenderWindow& _window)
{
	if (_player.state == DEAD)
	{
		DisplayAnimation(_player.deathAnimation, _player.currentPos, UP * 90.f, _window);
	}
	else
	{
		DisplayAnimation(_player.walkAnimation, _player.currentPos, _player.currentDir * 90.f, _window);
	}
}

void DisplayPlayerHUD(Player& _player, MapArray& _mapArray, sf::RenderWindow& _window)
{
	_window.draw(_player.scoreText);

	for (int i = 0; i < _player.life; i++)
	{
		sf::Vector2f lifePos = { TILE_SIZE * (float)i + TILE_SIZE / 2, TILE_SIZE * (float)(_mapArray.rows - 1) + TILE_SIZE / 2 };
		BlitSprite(_player.walkAnimation.spriteArray[1], _window, lifePos);
	}
}