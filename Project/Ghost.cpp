#include "Ghost.hpp"

void InitGhost(Ghost _ghosts[NUM_GHOST], MapArray& _mapArray, sf::Font& _font)
{
	_ghosts[BLINKY].pointText = CreateText(_font, "0", TILE_SIZE / 3, sf::Color::Cyan);
	_ghosts[PINKY].pointText = CreateText(_font, "0", TILE_SIZE / 3, sf::Color::Cyan);
	_ghosts[INKY].pointText = CreateText(_font, "0", TILE_SIZE / 3, sf::Color::Cyan);
	_ghosts[CLYDE].pointText = CreateText(_font, "0", TILE_SIZE / 3, sf::Color::Cyan);

	sf::Sprite ghostEyes[GHOST_EYE_SPRITE];
	ghostEyes[UP] = LoadSprite("Data/Sprite/Ghost/GhostEyeUp.png", false, { 2, 2 });
	ghostEyes[DOWN] = LoadSprite("Data/Sprite/Ghost/GhostEyeDown.png", false, { 2, 2 });
	ghostEyes[LEFT] = LoadSprite("Data/Sprite/Ghost/GhostEyeLeft.png", false, { 2, 2 });
	ghostEyes[RIGHT] = LoadSprite("Data/Sprite/Ghost/GhostEyeRight.png", false, { 2, 2 });
	ghostEyes[4] = LoadSprite("Data/Sprite/Ghost/GumEyes.png", false, { 2, 2 }); // gum eyes
	ghostEyes[5] = LoadSprite("Data/Sprite/Ghost/GumMouth.png", false, { 2, 2 }); // gum mouth

	sf::Sprite ghostMoves[5];
	ghostMoves[0] = LoadSprite("Data/Sprite/Ghost/GhostMove0.png", false, { 2, 2 });
	ghostMoves[1] = LoadSprite("Data/Sprite/Ghost/GhostMove1.png", false, { 2, 2 });
	ghostMoves[2] = LoadSprite("Data/Sprite/Ghost/GhostMove2.png", false, { 2, 2 });
	ghostMoves[3] = LoadSprite("Data/Sprite/Ghost/GhostMove3.png", false, { 2, 2 });
	ghostMoves[4] = LoadSprite("Data/Sprite/Ghost/GhostMove4.png", false, { 2, 2 });


	for (int i = 0; i < _mapArray.rows; i++)
	{
		for (int j = 0; j < _mapArray.cols; j++)
		{
			switch (_mapArray.data[i][j])
			{
			case(SPAWN_BLINKY):
				CreateGhost(_ghosts[BLINKY], BLINKY, ghostEyes, ghostMoves, {j, i});
				break;
			case(SPAWN_PINKY):
				CreateGhost(_ghosts[PINKY], PINKY, ghostEyes, ghostMoves, { j, i });
				break;
			case(SPAWN_INKY):
				CreateGhost(_ghosts[INKY], INKY, ghostEyes, ghostMoves, { j, i });
				break;
			case(SPAWN_CLYDE):
				CreateGhost(_ghosts[CLYDE], CLYDE, ghostEyes, ghostMoves, { j, i });
				break;
			}
		}
	}
}

void ReloadGhosts(Ghost _ghosts[NUM_GHOST])
{
	for (int i = 0; i < 4; i++)
	{
		_ghosts[i].state = SPAWN;
		_ghosts[i].speed = SCATTER_SPEED;
		_ghosts[i].chaseTimer = 0;
		_ghosts[i].scatterTimer = SCATTER_TIME;
		_ghosts[i].frightenedTimer = 0;
		_ghosts[i].oldPos = sf::Vector2f(_ghosts[i].spawnPos.x * TILE_SIZE + 16, _ghosts[i].spawnPos.y * TILE_SIZE + 16);
		_ghosts[i].currentPos = _ghosts[i].oldPos;
		_ghosts[i].currentDir = GhostDir(rand() % 4);
		_ghosts[i].newDir = GhostDir(rand() % 4);
	}
}

void CreateGhostAnimations(GhostAnimation& _ghostAnimation, sf::Sprite _ghostEyes[GHOST_EYE_SPRITE], sf::Sprite _ghostMoves[GHOST_MOVE_SPRITE], sf::Color _ghostColor)
{
	for (int i = 0; i < GHOST_MOVE_SPRITE; i++) // EATEN SPRITES
	{
		_ghostAnimation.sprites[5][i] = _ghostEyes[i];
		sf::Vector2f tempOrigin = sf::Vector2f(16 / 2, 16 / 2);
		_ghostAnimation.sprites[5][i].setOrigin(tempOrigin); // set the origin at the center of the sprite
	}

	// set color of sprites
	for (int i = 0; i < GHOST_MOVE_SPRITE; i++)
	{
		_ghostMoves[i].setColor(_ghostColor);
	}

	for (int i = 0; i < GHOST_EYE_SPRITE - 2; i++) // WALKING ANIMATION : MOVE SPRITES
	{
		sf::RenderTexture* render[GHOST_MOVE_SPRITE] = { new sf::RenderTexture, new sf::RenderTexture, new sf::RenderTexture, new sf::RenderTexture, new sf::RenderTexture };
		for (int j = 0; j < GHOST_MOVE_SPRITE; j++)
		{
			render[j]->create(32, 32);

			render[j]->clear(sf::Color(0, 0, 0, 0)); // if not called texture can have noise pixels
			render[j]->draw(_ghostMoves[j]);
			render[j]->draw(_ghostEyes[i]);
			render[j]->display();

			_ghostAnimation.sprites[i][j].setTexture(render[j]->getTexture());

			sf::Vector2u tempTaille = render[j]->getTexture().getSize();
			sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x / 2, tempTaille.y / 2);
			_ghostAnimation.sprites[i][j].setOrigin(tempOrigin); // set the origin at the center of the sprite
		}

		_ghostAnimation.walking[i] = CreateAnimation(GHOST_MOVE_SPRITE, 0.25f, _ghostAnimation.sprites[i]);
	}

	for (int i = 0; i < GHOST_MOVE_SPRITE; i++)
	{
		_ghostMoves[i].setColor(sf::Color::Blue);
	}

	_ghostEyes[4].setColor(sf::Color::White);
	_ghostEyes[5].setColor(sf::Color::White);
	for (int k = 0; k < 2; k++) // frightened animation : MOVE SPRITES (animation one index 4 and second 6)
	{
		int indexAnimation = 4 + (k * 2);
		sf::RenderTexture* render[GHOST_MOVE_SPRITE] = { new sf::RenderTexture, new sf::RenderTexture, new sf::RenderTexture, new sf::RenderTexture, new sf::RenderTexture };
		for (int j = 0; j < GHOST_MOVE_SPRITE; j++)
		{
			render[j]->create(32, 32);

			render[j]->clear(sf::Color(0, 0, 0, 0)); // if not called texture can have noise pixels
			render[j]->draw(_ghostMoves[j]);
			render[j]->draw(_ghostEyes[4]);
			render[j]->draw(_ghostEyes[5]);
			render[j]->display();

			_ghostAnimation.sprites[indexAnimation][j].setTexture(render[j]->getTexture());

			sf::Vector2u tempTaille = render[j]->getTexture().getSize();
			sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x / 2, tempTaille.y / 2);
			_ghostAnimation.sprites[indexAnimation][j].setOrigin(tempOrigin); // set the origin at the center of the sprite
		}
		_ghostAnimation.frightened[k] = CreateAnimation(GHOST_MOVE_SPRITE, 0.25f, _ghostAnimation.sprites[indexAnimation]);

		// change sprite color for second frightened animation
		for (int i = 0; i < GHOST_MOVE_SPRITE; i++)
		{
			_ghostMoves[i].setColor(sf::Color::White);
		}

		_ghostEyes[4].setColor(sf::Color::Red);
		_ghostEyes[5].setColor(sf::Color::Red);
	}
}

void CreateGhost(Ghost& _ghost, GhostType _type, sf::Sprite _ghostEyes[GHOST_EYE_SPRITE], sf::Sprite _ghostMoves[GHOST_MOVE_SPRITE], sf::Vector2i _tilePos)
{
	_ghost.type = _type;

	sf::Color ghostColor;
	switch (_ghost.type)
	{
	case(BLINKY):
		ghostColor = sf::Color::Red;
		break;
	case(PINKY):
		ghostColor = sf::Color(255, 184, 255);
		break;
	case(INKY):
		ghostColor = sf::Color(0, 255, 255);
		break;
	case(CLYDE):
		ghostColor = sf::Color(255, 184, 82);
		break;
	}

	CreateGhostAnimations(_ghost.animation, _ghostEyes, _ghostMoves, ghostColor);
	_ghost.spawnPos = _tilePos;
	_ghost.oldPos = sf::Vector2f(_ghost.spawnPos.x * TILE_SIZE + 16, _ghost.spawnPos.y * TILE_SIZE + 16);
	_ghost.currentPos = _ghost.oldPos;
	_ghost.currentDir = GhostDir(rand() % 4);
}

bool IsGhostCollideWall(Ghost& _ghost, std::vector<Wall> _walls)
{
	bool collision = false;
	sf::FloatRect ghostRectangle = { _ghost.currentPos.x - 16, _ghost.currentPos.y - 16, 32, 32 };
	for (int i = 0; i < _walls.size(); i++)
	{
		// ghost can go through wall gate only from the bottom
		// so we check first if this case is true or false
		// if false we check collision else we do nothing
		if (!(_walls[i].type == SPAWN_WALL_GATE && _ghost.currentDir == UP) &&
			!(_walls[i].type == SPAWN_WALL_GATE && _ghost.currentDir == DOWN && _ghost.state == EATEN))
		{
			sf::FloatRect wallRectangle = { _walls[i].pos.x, _walls[i].pos.y, 32, 32 };
			if (IsCollidingRectangles(ghostRectangle, wallRectangle))
			{
				collision = true;
			}
		}
	}

	return collision;
}

sf::Vector2i GetGhostArrayIndex(Ghost _ghost)
{
	sf::Vector2i arrayIndex;

	arrayIndex.x = int(_ghost.currentPos.x) / 32;
	arrayIndex.y = int(_ghost.currentPos.y) / 32;

	return arrayIndex;
}

void CheckGhostNotTrapped(Ghost& _ghost, MapArray& _mapArray)
{
	sf::Vector2i ghostIndex = GetGhostArrayIndex(_ghost);
	TileType* tiles = GetTilesAround(ghostIndex, _mapArray);

	if (_ghost.currentDir == UP)
	{
		// check if ghost is trapped between there 3 possible dir
		if ((tiles[UP] == WALL || tiles[UP] == WALL_SPAWN) &&
			(tiles[LEFT] == WALL || tiles[LEFT] == WALL_SPAWN) &&
			(tiles[RIGHT] == WALL || tiles[RIGHT] == WALL_SPAWN))
		{
			_ghost.newDir = DOWN; // make the ghost turn away
			_ghost.currentDir = DOWN; // make the ghost turn away
		}
	}
	else if (_ghost.currentDir == DOWN)
	{
		if ((tiles[DOWN] == WALL || tiles[DOWN] == WALL_SPAWN) &&
			(tiles[LEFT] == WALL || tiles[LEFT] == WALL_SPAWN) &&
			(tiles[RIGHT] == WALL || tiles[RIGHT] == WALL_SPAWN))
		{
			_ghost.newDir = UP;
			_ghost.currentDir = UP;
		}
	}
	else if (_ghost.currentDir == LEFT)
	{
		if ((tiles[UP] == WALL || tiles[UP] == WALL_SPAWN) &&
			(tiles[DOWN] == WALL || tiles[DOWN] == WALL_SPAWN) &&
			(tiles[LEFT] == WALL || tiles[LEFT] == WALL_SPAWN))
		{
			_ghost.newDir = RIGHT;
			_ghost.currentDir = RIGHT;
		}
	}
	else if (_ghost.currentDir == RIGHT)
	{
		if ((tiles[UP] == WALL || tiles[UP] == WALL_SPAWN) &&
			(tiles[DOWN] == WALL || tiles[DOWN] == WALL_SPAWN) &&
			(tiles[RIGHT] == WALL || tiles[RIGHT] == WALL_SPAWN))
		{
			_ghost.newDir = LEFT;
			_ghost.currentDir = LEFT;
		}
	}
}

void RevertDirGhost(Ghost& _ghost, MapArray& _mapArray)
{
	sf::Vector2i ghostIndex = GetGhostArrayIndex(_ghost);
	TileType* tiles = GetTilesAround(ghostIndex, _mapArray);

	switch (_ghost.currentDir)
	{
	case(UP):
		if (IsTileTraversable(tiles[DOWN]))
		{
			_ghost.currentDir = DOWN;
			_ghost.newDir = DOWN;
		}
		break;
	case(DOWN):
		if (IsTileTraversable(tiles[UP]))
		{
			_ghost.currentDir = UP;
			_ghost.newDir = UP;
		}
		break;
	case(LEFT):
		if (IsTileTraversable(tiles[RIGHT]))
		{
			_ghost.currentDir = RIGHT;
			_ghost.newDir = RIGHT;
		}
		break;
	case(RIGHT):
		if (IsTileTraversable(tiles[LEFT]))
		{
			_ghost.currentDir = LEFT;
			_ghost.newDir = LEFT;
		}
		break;
	}
}

void ChangeGhostState(Ghost& _ghost, MapArray& _mapArray, GhostState _newState)
{
	// ghost don't revert is direction when is state/new state is eaten/spawn
	if (_ghost.state != SPAWN && 
		_ghost.state != EATEN && 
		_newState != EATEN && 
		_newState != SPAWN && 
		_ghost.state != _newState) // don't change dir if ghost is already in this state
	{
		RevertDirGhost(_ghost, _mapArray); // revert ghost dir when they change state
	}

	_ghost.state = _newState;

	switch (_ghost.state)
	{
	case SPAWN:
		_ghost.speed = SCATTER_SPEED;
		break;

	case CHASE:
		_ghost.speed = CHASE_SPEED;
		break;

	case SCATTER:
		_ghost.speed = SCATTER_SPEED;
		break;

	case FRIGHTENED:
		_ghost.frightenedTimer = FRIGHTENED_TIME;
		_ghost.speed = FRIGHTENED_SPEED;
		break;

	case EATEN:
		_ghost.speed = EATEN_SPEED;
		break;

	default:
		std::cerr << "Couldn't find ghost state in ChangeGhostState" << std::endl;
		break;
	}
}

void UpdateGhostNewDir(Ghost& _ghost, std::vector<Wall> _walls, float _dt)
{
	if (_ghost.currentDir == UP || _ghost.currentDir == DOWN)
	{
		float diffY = _ghost.currentPos.y - _ghost.oldPos.y; // offset (because of speed)
		diffY *= diffY;
		diffY = sqrt(diffY); // make the offset positif
		int posY = int(_ghost.currentPos.y) % TILE_SIZE;

		if (_ghost.newDir == UP || _ghost.newDir == DOWN)
		{
			_ghost.currentDir = _ghost.newDir;
		}
		else if (posY >= TILE_SIZE / 2 - diffY && posY <= TILE_SIZE / 2 + diffY)
		{
			sf::Vector2f currentPos = _ghost.currentPos;
			if (_ghost.newDir == LEFT)
			{
				_ghost.currentPos.x -= _ghost.speed * _dt;
			}
			else if (_ghost.newDir == RIGHT)
			{
				_ghost.currentPos.x += _ghost.speed * _dt;
			}
			_ghost.currentPos.y = int(_ghost.currentPos.y) + TILE_SIZE / 2 - int(_ghost.currentPos.y) % TILE_SIZE; // set the ghost in the right position

			if (!IsGhostCollideWall(_ghost, _walls))
			{
				_ghost.currentDir = _ghost.newDir;
			}
			else
			{
				_ghost.currentPos = currentPos;
			}
		}
	}
	else if (_ghost.currentDir == LEFT || _ghost.currentDir == RIGHT)
	{
		float diffX = _ghost.currentPos.x - _ghost.oldPos.x;
		diffX *= diffX;
		diffX = sqrt(diffX);
		int posX = int(_ghost.currentPos.x) % TILE_SIZE;

		if (_ghost.newDir == LEFT || _ghost.newDir == RIGHT) // don't need anything to check
		{
			_ghost.currentDir = _ghost.newDir;
		}
		else if (posX >= TILE_SIZE / 2 - diffX && posX <= TILE_SIZE / 2 + diffX)
		{
			sf::Vector2f currentPos = _ghost.currentPos;
			GhostDir oldDir = _ghost.currentDir;
			if (_ghost.newDir == UP)
			{
				_ghost.currentPos.y -= _ghost.speed * _dt;
			}
			else if (_ghost.newDir == DOWN)
			{
				_ghost.currentPos.y += _ghost.speed * _dt;
			}
			_ghost.currentPos.x = int(_ghost.currentPos.x) + TILE_SIZE / 2 - int(_ghost.currentPos.x) % TILE_SIZE; // set the ghost in the right position

			_ghost.currentDir = _ghost.newDir;
			if (!IsGhostCollideWall(_ghost, _walls))
			{
				_ghost.currentDir = _ghost.newDir;
			}
			else
			{
				_ghost.currentDir = oldDir;
				_ghost.currentPos = currentPos;
			}
		}
	}
}

sf::Vector2i GetTargetFrightened(Ghost& _ghost, MapArray& _mapArray)
{
	sf::Vector2i ghostIndex = GetGhostArrayIndex(_ghost);
	TileType* tiles = GetTilesAround(ghostIndex, _mapArray);
	std::vector<PlayerDir> newDirVector;
	int indexVector;

	sf::Vector2i targetIndex;
	GhostDir newDir;

	// put the direction in vector if the wall is traversable and the ghost is not in the opposite dir
	if (_ghost.currentDir != DOWN && IsTileTraversable(tiles[UP]))
	{
		newDirVector.push_back(UP);
	}
	if (_ghost.currentDir != UP && IsTileTraversable(tiles[DOWN]))
	{
		newDirVector.push_back(DOWN);
	}

	if (_ghost.currentDir != RIGHT && IsTileTraversable(tiles[LEFT]))
	{
		newDirVector.push_back(LEFT);
	}
	if (_ghost.currentDir != LEFT && IsTileTraversable(tiles[RIGHT]))
	{
		newDirVector.push_back(RIGHT);
	}

	// get a random dir and change the target pos
	indexVector = rand() % newDirVector.size();
	switch (newDirVector[indexVector])
	{
	case(UP):
		targetIndex.x = ghostIndex.x;
		targetIndex.y = ghostIndex.y - 1;
		break;
	case(DOWN):
		targetIndex.x = ghostIndex.x;
		targetIndex.y = ghostIndex.y + 1;
		break;
	case(LEFT):
		targetIndex.x = ghostIndex.x - 1;
		targetIndex.y = ghostIndex.y;
		break;
	case(RIGHT):
		targetIndex.x = ghostIndex.x + 1;
		targetIndex.y = ghostIndex.y;
		break;
	}

	// exemple de suppression dans un vector
	// ne sert pas vraiment à grand chose dans cette fonction..
	newDirVector.erase(newDirVector.begin() + indexVector);

	return targetIndex;
}

sf::Vector2i GetTargetPinky(Ghost& _ghost, Player& _player, MapArray& _mapArray)
{
	sf::Vector2i ghostIndex = GetGhostArrayIndex(_ghost);
	sf::Vector2i playerIndex = GetPlayerArrayIndex(_player);

	sf::Vector2i targetIndex;

	switch (_ghost.state)
	{
	case(SPAWN):
		targetIndex = { _ghost.spawnPos.x, _ghost.spawnPos.y - 1 };
		break;

	case(CHASE):
		switch (_player.currentDir)
		{
		case(UP):
			targetIndex.y = playerIndex.y - 2;
			targetIndex.x = playerIndex.x - 2; // reproduit le bug dans pac-man
			break;

		case(DOWN):
			targetIndex.y = playerIndex.y + 2;
			targetIndex.x = playerIndex.x;
			break;

		case(LEFT):
			targetIndex.y = playerIndex.y;
			targetIndex.x = playerIndex.x - 2;
			break;

		case(RIGHT):
			targetIndex.y = playerIndex.y;
			targetIndex.x = playerIndex.x + 2;
			break;

		default:
			std::cerr << "No direction found for player in GetTargetPinky function" << std::endl;
			break;
		}
		break;

	case(SCATTER):
		targetIndex = { 0, 0 };
		break;

	case(FRIGHTENED):
		targetIndex = GetTargetFrightened(_ghost, _mapArray);
		break;

	case(EATEN):
		targetIndex = { _ghost.spawnPos.x, _ghost.spawnPos.y };
		break;

	default:
		std::cerr << "Couldn't find Clyde state" << std::endl;
		break;
	}
	
	return targetIndex;
}

sf::Vector2i GetTargetInky(Ghost& _ghost, Ghost& _Blinky, Player& _player, MapArray& _mapArray)
{
	sf::Vector2i playerIndex = GetPlayerArrayIndex(_player);
	sf::Vector2i offSet = playerIndex;
	sf::Vector2i BlinkyIndex = GetGhostArrayIndex(_Blinky);

	sf::Vector2i targetIndex;

	switch (_ghost.state)
	{
	case(SPAWN):
		targetIndex = { _ghost.spawnPos.x + 2, _ghost.spawnPos.y - 1 };
		break;

	case(CHASE):
		switch (_player.currentDir)
		{
		case(UP):
			offSet.y = playerIndex.y - 1;
			offSet.x = playerIndex.x - 1; // reproduit le bug dans pac-man
			break;

		case(DOWN):
			offSet.y = playerIndex.y + 1;
			break;

		case(LEFT):
			offSet.x = playerIndex.x - 1;
			break;

		case(RIGHT):
			offSet.x = playerIndex.x + 1;
			break;
		}

		targetIndex.x = offSet.x + offSet.x - BlinkyIndex.x;
		targetIndex.y = offSet.y + offSet.y - BlinkyIndex.y;
		break;

	case(SCATTER):
		targetIndex = { _mapArray.cols, _mapArray.rows };
		break;

	case(FRIGHTENED):
		targetIndex = GetTargetFrightened(_ghost, _mapArray);
		break;

	case(EATEN):
		targetIndex = { _ghost.spawnPos.x, _ghost.spawnPos.y };
		break;

	default:
		std::cerr << "Couldn't find Clyde state" << std::endl;
		break;
	}

	return targetIndex;
}

sf::Vector2i GetTargetClyde(Ghost& _ghost, Player& _player, MapArray& _mapArray)
{
	sf::Vector2i ghostIndex = GetGhostArrayIndex(_ghost);
	sf::Vector2i playerIndex = GetPlayerArrayIndex(_player);

	sf::Vector2i vector;
	int dist;

	sf::Vector2i targetIndex;

	switch (_ghost.state)
	{

	case(SPAWN):
		targetIndex = { _ghost.spawnPos.x - 2, _ghost.spawnPos.y - 1 };
		break;

	case(CHASE):
		vector.x = (ghostIndex.x - playerIndex.x) * (ghostIndex.x - playerIndex.x);
		vector.y = (ghostIndex.y - playerIndex.y) * (ghostIndex.y - playerIndex.y);
		dist = sqrt(vector.x + vector.y);

		if (dist > CLYDE_RADIUS_CHASE)
		{
			targetIndex = playerIndex;
		}
		else
		{
			targetIndex = { 0, _mapArray.rows };
		}
		break;

	case(SCATTER):
		targetIndex = { 0, _mapArray.rows };
		break;

	case(FRIGHTENED):
		targetIndex = GetTargetFrightened(_ghost, _mapArray);
		break;

	case(EATEN):
		targetIndex = { _ghost.spawnPos.x, _ghost.spawnPos.y };
		break;

	default:
		std::cerr << "Couldn't find Clyde state" << std::endl;
		break;
	}

	return targetIndex;
}

sf::Vector2i GetTargetAI(Ghost& _ghost, Ghost& _blinky, Player& _player, MapArray& _mapArray)
{
	sf::Vector2i ghostIndex = GetGhostArrayIndex(_ghost);
	sf::Vector2i target;

	switch (_ghost.type)
	{
	case(BLINKY):
		if (_ghost.state == EATEN)
		{
			target = { _ghost.spawnPos.x, _ghost.spawnPos.y - 1 };
		}
		else if (_ghost.state == SPAWN)
		{
			target = _ghost.spawnPos;
		}
		else if (_ghost.state == CHASE)
		{
			target = GetPlayerArrayIndex(_player);
		}
		else if (_ghost.state == SCATTER)
		{
			target = { _mapArray.cols, 0 };
		}
		else if (_ghost.state == FRIGHTENED)
		{
			target = GetTargetFrightened(_ghost, _mapArray);
		}
		break;

	case(PINKY):
		target = GetTargetPinky(_ghost, _player, _mapArray);
		break;

	case(INKY):
		target = GetTargetInky(_ghost, _blinky, _player, _mapArray);
		break;

	case(CLYDE):
		target = GetTargetClyde(_ghost, _player, _mapArray);
		break;
	}

	return target;
}

GhostDir GetNewAIDir(int* _costDir)
{
	GhostDir dir;

	if (_costDir[UP] <= _costDir[DOWN] && _costDir[UP] <= _costDir[LEFT] && _costDir[UP] <= _costDir[RIGHT])
	{
		dir = UP;
	}
	else if (_costDir[DOWN] <= _costDir[UP] && _costDir[DOWN] <= _costDir[LEFT] && _costDir[DOWN] <= _costDir[RIGHT])
	{
		dir = DOWN;
	}
	else if (_costDir[LEFT] <= _costDir[UP] && _costDir[LEFT] <= _costDir[DOWN] && _costDir[LEFT] <= _costDir[RIGHT])
	{
		dir = LEFT;
	}
	else
	{
		dir = RIGHT;
	}

	return dir;
}

void UpdateAIGhost(Ghost& _ghost, Ghost& _blinky, Player& _player, MapArray& _mapArray)
{
	sf::Vector2i targetIndex = GetTargetAI(_ghost, _blinky, _player, _mapArray);
	sf::Vector2i ghostIndex = GetGhostArrayIndex(_ghost);
	int* costDir = GetCostDir(ghostIndex, targetIndex, _mapArray);

	// ghost can't turn back so we set the cost of their back to 10000
	if (_ghost.currentDir == UP)
	{
		costDir[DOWN] = 10000;
	}
	else if (_ghost.currentDir == DOWN)
	{
		costDir[UP] = 10000;
	}
	else if (_ghost.currentDir == LEFT)
	{
		costDir[RIGHT] = 10000;
	}
	else if (_ghost.currentDir == RIGHT)
	{
		costDir[LEFT] = 10000;
	}

	_ghost.newDir = GetNewAIDir(costDir); // set the newDir to the dir with the lowest cost
}

void UpdateGhostDir(Ghost& _ghost, Ghost& _Blinky, Player& _player, MapData& _mapData, float _dt)
{
	UpdateAIGhost(_ghost, _Blinky, _player, _mapData.arr);
	UpdateGhostNewDir(_ghost, _mapData.walls, _dt);
	CheckGhostNotTrapped(_ghost, _mapData.arr);
}

void MoveGhost(Ghost& _ghost, MapData& _mapData, float _dt)
{
	_ghost.oldPos = _ghost.currentPos;

	if (_ghost.currentDir == UP)
	{
		// move ghost
		_ghost.currentPos.y -= _ghost.speed * _dt;
		if (IsGhostCollideWall(_ghost, _mapData.walls))
		{
			// put the ghost out of the wall
			_ghost.currentPos.y = int(_ghost.currentPos.y) + TILE_SIZE / 2 - int(_ghost.currentPos.y) % TILE_SIZE;
		}
	}
	else if (_ghost.currentDir == DOWN)
	{
		_ghost.currentPos.y += _ghost.speed * _dt;
		if (IsGhostCollideWall(_ghost, _mapData.walls))
		{
			_ghost.currentPos.y = int(_ghost.currentPos.y) + TILE_SIZE / 2 - int(_ghost.currentPos.y) % TILE_SIZE;
		}
	}
	else if (_ghost.currentDir == LEFT)
	{
		_ghost.currentPos.x -= _ghost.speed * _dt;
		if (IsGhostCollideWall(_ghost, _mapData.walls))
		{
			_ghost.currentPos.x = int(_ghost.currentPos.x) + TILE_SIZE / 2 - int(_ghost.currentPos.x) % TILE_SIZE;
		}
	}
	else if (_ghost.currentDir == RIGHT)
	{
		_ghost.currentPos.x += _ghost.speed * _dt;
		if (IsGhostCollideWall(_ghost, _mapData.walls))
		{
			_ghost.currentPos.x = int(_ghost.currentPos.x) + TILE_SIZE / 2 - int(_ghost.currentPos.x) % TILE_SIZE;
		}
	}
	else
	{
		std::cerr << "no direction found for ghost." << std::endl;
	}

	// faire fonction propre à elle
	// check if ghost out of bounds
	if (_ghost.currentPos.x > _mapData.arr.cols * TILE_SIZE)
	{
		_ghost.currentPos.x = 1;
		_ghost.currentDir = RIGHT;
		_ghost.newDir = RIGHT;
	}
	else if (_ghost.currentPos.x < 0)
	{
		_ghost.currentPos.x = _mapData.arr.cols * TILE_SIZE - 1;
		_ghost.currentDir = LEFT;
		_ghost.newDir = LEFT;
	}
}

int GetEatenPoint(int _numGhostEat)
{
	int point = 200;

	for (int i = 1; i < _numGhostEat; i++)
	{
		point *= 2;
	}

	return point;
}

void UpdateFrightenedState(Ghost& _ghost, Player& _player, MapArray& _mapArray, int& _numGhostEat)
{
	sf::FloatRect playerRectangle = GetPlayerCollisionRect(_player);
	sf::FloatRect ghostRectangle = { _ghost.currentPos.x - 8, _ghost.currentPos.y - 8, 16, 16 };
	if (IsCollidingRectangles(playerRectangle, ghostRectangle))
	{
		std::string tempString;
		_numGhostEat++;
		_player.score += GetEatenPoint(_numGhostEat);

		tempString = std::to_string(GetEatenPoint(_numGhostEat));
		SetCenteredString(_ghost.pointText, tempString);
		_ghost.pointText.setPosition(_ghost.currentPos);

		_player.eatSounds[2].play();
		ChangeGhostState(_ghost, _mapArray, EATEN);

		if (_numGhostEat >= 4)
		{
			_numGhostEat = 0;
		}
	}

	if (_ghost.frightenedTimer <= 0)
	{
		ChangeGhostState(_ghost, _mapArray, SCATTER);
		_numGhostEat = 0;
	}
}

void UpdateState(Ghost& _ghost, Ghost& _blinky, Player& _player, MapArray& _mapArray)
{
	static int numGhostEat = 0; // num of ghost eaten for the current gum

	if (_player.state == EAT_GUM)
	{
		if (_ghost.state != EATEN && _ghost.state != SPAWN)
		{
			ChangeGhostState(_ghost, _mapArray, FRIGHTENED);
		}

		numGhostEat = 0; // init num of ghost eaten since player eat a gum
	}

	switch (_ghost.state)
	{
	case(SPAWN):
		if (GetGhostArrayIndex(_ghost) == _blinky.spawnPos)
		{
			if (_ghost.chaseTimer <= 0)
			{
				ChangeGhostState(_ghost, _mapArray, SCATTER);
			}
			else if (_ghost.scatterTimer <= 0)
			{
				ChangeGhostState(_ghost, _mapArray, CHASE);
			}
		}
		break;

	case(CHASE):
		if (_ghost.chaseTimer <= 0)
		{
			ChangeGhostState(_ghost, _mapArray, SCATTER);
		}
		break;

	case(SCATTER):
		if (_ghost.scatterTimer <= 0)
		{
			ChangeGhostState(_ghost, _mapArray, CHASE);
		}
		break;

	case(FRIGHTENED):
		UpdateFrightenedState(_ghost, _player, _mapArray, numGhostEat);
		break;

	case(EATEN):
		if (GetGhostArrayIndex(_ghost) == _ghost.spawnPos)
		{
			ChangeGhostState(_ghost, _mapArray, SPAWN);
		}
		break;
	}
}

void UpdateGhostTimers(Ghost& _ghost, float _dt)
{
	if (_ghost.chaseTimer > 0)
	{
		_ghost.chaseTimer -= _dt;
		if (_ghost.chaseTimer <= 0)
		{
			_ghost.scatterTimer = SCATTER_TIME;
		}
	}
	else if (_ghost.scatterTimer > 0)
	{
		_ghost.scatterTimer -= _dt;
		if (_ghost.scatterTimer <= 0)
		{
			_ghost.chaseTimer = CHASE_TIME;
		}
	}


	if (_ghost.frightenedTimer > 0)
	{
		_ghost.frightenedTimer -= _dt;
		if (_ghost.frightenedTimer <= 0)
		{
			_ghost.frightenedTimer = 0;
		}
	}
}

void UpdateGhost(Ghost& _ghost, Ghost& _blinky, Player& _player, MapData& _mapData, float _dt)
{
	UpdateGhostTimers(_ghost, _dt);
	UpdateState(_ghost, _blinky, _player, _mapData.arr);

	UpdateGhostDir(_ghost, _blinky, _player, _mapData, _dt);
	MoveGhost(_ghost, _mapData, _dt);

	sf::FloatRect playerRectangle = GetPlayerCollisionRect(_player);
	sf::FloatRect ghostRectangle = { _ghost.currentPos.x - 8, _ghost.currentPos.y - 8, 16, 16 };
	if (IsCollidingRectangles(playerRectangle, ghostRectangle) && _ghost.state != FRIGHTENED && _ghost.state != EATEN)
	{
		_player.state = DEAD;
		if (_player.deathSounds[0].getStatus() == STOPPED)
		{
			PlaySoundOnRepeat(_player.deathSounds[0]);
		}
	}

	if (_ghost.state == FRIGHTENED)
	{
		UpdateAnimation(_ghost.animation.frightened[0], _dt);
		UpdateAnimation(_ghost.animation.frightened[1], _dt);
	}
	else
	{
		UpdateAnimation(_ghost.animation.walking[_ghost.currentDir], _dt);
	}
}

void DisplayGhost(Ghost& _ghost, sf::RenderWindow& _window)
{
	if (_ghost.state == FRIGHTENED)
	{
		if (_ghost.frightenedTimer < 1.5f)
		{
			int animation = (int)(_ghost.frightenedTimer * 5) % 2;
			DisplayAnimation(_ghost.animation.frightened[animation], _ghost.currentPos, 0.f, _window);
		}
		else
		{
			DisplayAnimation(_ghost.animation.frightened[0], _ghost.currentPos, 0.f, _window);
		}
	}
	else if (_ghost.state == EATEN)
	{
		BlitSprite(_ghost.animation.sprites[5][_ghost.currentDir], _window, _ghost.currentPos);
		_window.draw(_ghost.pointText);
	}
	else
	{
		DisplayAnimation(_ghost.animation.walking[_ghost.currentDir], _ghost.currentPos, 0.f, _window);
	}
}