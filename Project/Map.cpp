#include "Map.hpp"

void InitMap(MapData& _mapData, sf::Font& _font)
{
	_mapData.bonus.pointText = CreateText(_font, "0", TILE_SIZE / 3, sf::Color::Cyan);

	_mapData.dotSprite = LoadSprite("Data/Sprite/Map/Dot.png", false);
	_mapData.gumSprite = LoadSprite("Data/Sprite/Map/Gum.png", false);

	_mapData.wallSprites[WALL_DEFAULT] = LoadSprite("Data/Sprite/Map/Wall/Wall.png", false);

	_mapData.wallSprites[WALL_UP] = LoadSprite("Data/Sprite/Map/Wall/WallUp.png", false);
	_mapData.wallSprites[WALL_DOWN] = LoadSprite("Data/Sprite/Map/Wall/WallDown.png", false);
	_mapData.wallSprites[WALL_LEFT] = LoadSprite("Data/Sprite/Map/Wall/WallLeft.png", false);
	_mapData.wallSprites[WALL_RIGHT] = LoadSprite("Data/Sprite/Map/Wall/WallRight.png", false);

	_mapData.wallSprites[WALL_UP_DOWN] = LoadSprite("Data/Sprite/Map/Wall/WallUpDown.png", false);
	_mapData.wallSprites[WALL_UP_LEFT] = LoadSprite("Data/Sprite/Map/Wall/WallUpLeft.png", false);
	_mapData.wallSprites[WALL_UP_RIGHT] = LoadSprite("Data/Sprite/Map/Wall/WallUpRight.png", false);
	_mapData.wallSprites[WALL_DOWN_LEFT] = LoadSprite("Data/Sprite/Map/Wall/WallDownLeft.png", false);
	_mapData.wallSprites[WALL_DOWN_RIGHT] = LoadSprite("Data/Sprite/Map/Wall/WallDownRight.png", false);
	_mapData.wallSprites[WALL_LEFT_RIGHT] = LoadSprite("Data/Sprite/Map/Wall/WallLeftRight.png", false);

	_mapData.wallSprites[WALL_UP_RIGHT_LEFT] = LoadSprite("Data/Sprite/Map/Wall/WallUpRightLeft.png", false);
	_mapData.wallSprites[WALL_DOWN_RIGHT_LEFT] = LoadSprite("Data/Sprite/Map/Wall/WallDownRightLeft.png", false);
	_mapData.wallSprites[WALL_LEFT_UP_DOWN] = LoadSprite("Data/Sprite/Map/Wall/WallLeftUpDown.png", false);
	_mapData.wallSprites[WALLL_RIGHT_UP_DOWN] = LoadSprite("Data/Sprite/Map/Wall/WallRightUpDown.png", false);

	_mapData.wallSprites[WALL_UP_DOWN_LEFT_RIGHT] = LoadSprite("Data/Sprite/Map/Wall/WallDefault.png", false);

	_mapData.wallSprites[SPAWN_WALL_CORNER_LD] = LoadSprite("Data/Sprite/Map/SpawnWall/CornerSpawnWallLD.png", false);
	_mapData.wallSprites[SPAWN_WALL_CORNER_LU] = LoadSprite("Data/Sprite/Map/SpawnWall/CornerSpawnWallLU.png", false);
	_mapData.wallSprites[SPAWN_WALL_CORNER_RD] = LoadSprite("Data/Sprite/Map/SpawnWall/CornerSpawnWallRD.png", false);
	_mapData.wallSprites[SPAWN_WALL_CORNER_RU] = LoadSprite("Data/Sprite/Map/SpawnWall/CornerSpawnWallRU.png", false);

	_mapData.wallSprites[SPAWN_WALL_VERTICAL] = LoadSprite("Data/Sprite/Map/SpawnWall/VerticalSpawnWall.png", false);
	_mapData.wallSprites[SPAWN_WALL_HORIZONTAL] = LoadSprite("Data/Sprite/Map/SpawnWall/HorizontalSpawnWall.png", false);

	_mapData.wallSprites[SPAWN_WALL_GATE] = LoadSprite("Data/Sprite/Map/SpawnWall/GateWall.png", false);

	_mapData.bonusSprites[CHERRIES] = LoadSprite("Data/Sprite/Map/Bonus/Cherries.png", false);
	_mapData.bonusSprites[STRAWBERRY] = LoadSprite("Data/Sprite/Map/Bonus/Strawberry.png", false);
	_mapData.bonusSprites[APPLE] = LoadSprite("Data/Sprite/Map/Bonus/Apple.png", false);
	_mapData.bonusSprites[ORANGE] = LoadSprite("Data/Sprite/Map/Bonus/Orange.png", false);
	_mapData.bonusSprites[WATERMELON] = LoadSprite("Data/Sprite/Map/Bonus/Watermelon.png", false);

	_mapData.arr = CreateMapArray("Data/File/Map.txt");
	ReadMapArray(_mapData);
}

TileType** Create2DTileArray(const int _cols, const int _rows)
{
	TileType** arrayTile = new TileType* [_rows];

	for (int i = 0; i < _rows; i++)
	{
		arrayTile[i] = new TileType[_cols];
	}

	return arrayTile;
}

MapArray CreateMapArray(const std::string _filePath)
{
	MapArray newMapArray;
	std::vector<std::string> lines = readFile(_filePath); // get every line of map txt file

	newMapArray.rows = lines.size(); // set how many rows (lines) there is (map height)
	newMapArray.cols = lines[0].size(); // set how many cols (char) there is (map widht)
	newMapArray.data = Create2DTileArray(newMapArray.cols, newMapArray.rows);

	for (int i = 0; i < lines.size(); i++) // for each line
	{
		for (int j = 0; j < lines[i].size(); j++) // for each char
		{
			int num = (int)lines[i][j] - 48; // get ascii num and substract 48 to get real number value
			newMapArray.data[i][j] = (TileType)num; // transform num into TileType and put it in map array
		}
	}

	return newMapArray;
}

Wall CreateWall(sf::Vector2i _tilePos, MapArray& _mapArray)
{
	Wall newWall;
	std::vector<int> wallNeighbours;
	unsigned char wallType = 0b0000;

	// check if tilePos get out of bounds
	if (_tilePos.y - 1 < 0)
	{
		wallNeighbours.push_back(WALL); // if there is no tile put a wall
	}
	else
	{
		wallNeighbours.push_back(_mapArray.data[_tilePos.y - 1][_tilePos.x]);
	}

	if (_tilePos.x + 1 >= _mapArray.cols)
	{
		wallNeighbours.push_back(WALL);
	}
	else
	{
		wallNeighbours.push_back(_mapArray.data[_tilePos.y][_tilePos.x + 1]);
	}

	if (_tilePos.y + 1 >= _mapArray.rows)
	{
		wallNeighbours.push_back(WALL);
	}
	else
	{
		wallNeighbours.push_back(_mapArray.data[_tilePos.y + 1][_tilePos.x]);
	}

	if (_tilePos.x - 1 < 0)
	{
		wallNeighbours.push_back(WALL);
	}
	else
	{
		wallNeighbours.push_back(_mapArray.data[_tilePos.y][_tilePos.x - 1]);
	}

	for (int i = 0; i < wallNeighbours.size(); i++)
	{
		if (wallNeighbours[i] == WALL)
		{
			// each tile cost 2^i so we can have each different possibilities of wallType
			SET_BINARY(wallType, i);
		}
	}

	newWall.type = (WallType)wallType;
	newWall.pos = sf::Vector2f(_tilePos.x * TILE_SIZE, _tilePos.y * TILE_SIZE);

	return newWall;
}

void CreateDots(std::vector<sf::Vector2f>& _dotsPos, sf::Vector2i _tilePos, MapArray& _mapArray)
{
	sf::Vector2f dotPos = sf::Vector2f(_tilePos.x * TILE_SIZE, _tilePos.y* TILE_SIZE);
	_dotsPos.push_back(dotPos);

	// check if tilePos don't go out of bounds
	if (_tilePos.y - 1 >= 0)
	{
		TileType tileUp = _mapArray.data[_tilePos.y - 1][_tilePos.x]; // get tile type neighbour
		// put dot between neighbour dot/gum and original dot
		if (tileUp == DOT || tileUp == GUM)
		{
			sf::Vector2f dotNeighbourPos = sf::Vector2f(_tilePos.x * TILE_SIZE, (_tilePos.y - 0.5) * TILE_SIZE);
			_dotsPos.push_back(dotNeighbourPos);
		}
	}
	if (_tilePos.x - 1 >= 0)
	{
		TileType tileLeft = _mapArray.data[_tilePos.y][_tilePos.x - 1];
		if (tileLeft == DOT || tileLeft == GUM)
		{
			sf::Vector2f dotNeighbourPos = sf::Vector2f((_tilePos.x - 0.5) * TILE_SIZE, _tilePos.y* TILE_SIZE);
			_dotsPos.push_back(dotNeighbourPos);
		}
	}

	// Special gum cases
	if (_tilePos.y + 1 < _mapArray.rows)
	{
		TileType tileDown = _mapArray.data[_tilePos.y + 1][_tilePos.x];
		// just check gum because gum don't create dot in their down neighbour and their left neighbour
		// dot already created neighbour dot in this case (if their is a neighbour)
		if (tileDown == GUM)
		{
			sf::Vector2f dotNeighbourPos = sf::Vector2f(_tilePos.x * TILE_SIZE, (_tilePos.y + 0.5) * TILE_SIZE);
			_dotsPos.push_back(dotNeighbourPos);
		}
	}
	if (_tilePos.x + 1 < _mapArray.cols)
	{
		TileType tileRight = _mapArray.data[_tilePos.y][_tilePos.x + 1];
		if (tileRight == GUM)
		{
			sf::Vector2f dotNeighbourPos = sf::Vector2f((_tilePos.x + 0.5) * TILE_SIZE, _tilePos.y * TILE_SIZE);
			_dotsPos.push_back(dotNeighbourPos);
		}
	}
}

Wall CreateSpawnWall(const sf::Vector2i _tilePos, MapArray& _mapArray)
{
	Wall newWall;
	int wallSpawn = 0;

	if (_tilePos.y - 1 >= 0)
	{
		if (_mapArray.data[_tilePos.y - 1][_tilePos.x] == WALL_SPAWN)
		{
			wallSpawn += 1;
		}
	}

	if (_tilePos.y + 1 < _mapArray.rows)
	{
		if (_mapArray.data[_tilePos.y + 1][_tilePos.x] == WALL_SPAWN)
		{
			wallSpawn += 2;
		}
	}

	if (_tilePos.x - 1 >= 0)
	{
		if (_mapArray.data[_tilePos.y][_tilePos.x - 1] == WALL_SPAWN)
		{
			wallSpawn += 4;
		}
	}

	if (_tilePos.x + 1 < _mapArray.cols)
	{
		if (_mapArray.data[_tilePos.y][_tilePos.x + 1] == WALL_SPAWN)
		{
			wallSpawn += 8;
		}
	}

	if (wallSpawn == 1 || wallSpawn == 2 || wallSpawn == 3)
	{
		newWall.type = SPAWN_WALL_VERTICAL;
	}
	else if (wallSpawn == 4 || wallSpawn == 8 || wallSpawn == 12)
	{
		newWall.type = SPAWN_WALL_HORIZONTAL;
	}
	else if (wallSpawn == 5)
	{
		newWall.type = SPAWN_WALL_CORNER_LU;
	}
	else if (wallSpawn == 6)
	{
		newWall.type = SPAWN_WALL_CORNER_LD;
	}
	else if (wallSpawn == 9)
	{
		newWall.type = SPAWN_WALL_CORNER_RU;
	}
	else if (wallSpawn == 10)
	{
		newWall.type = SPAWN_WALL_CORNER_RD;
	}

	newWall.pos = sf::Vector2f(_tilePos.x * TILE_SIZE, _tilePos.y * TILE_SIZE);

	return newWall;
}

void ReadMapArray(MapData& _mapData)
{
	for (int i = 0; i < _mapData.arr.rows; i++)
	{
		for (int j = 0; j < _mapData.arr.cols; j++)
		{
			Wall gateSpawn;
			Wall wall;
			Wall spawnWall;
			sf::Vector2f gumPos;

			switch (_mapData.arr.data[i][j])
			{
			case GATE_SPAWN:
				gateSpawn = { SPAWN_WALL_GATE, sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE) };
				_mapData.walls.push_back(gateSpawn);
				break;
			case WALL:
				wall = CreateWall(sf::Vector2i(j, i), _mapData.arr);
				_mapData.walls.push_back(wall);
				break;
			case DOT:
				CreateDots(_mapData.dotsPos, sf::Vector2i(j, i), _mapData.arr);
				break;
			case GUM:
				gumPos = { (float)j * TILE_SIZE, (float)i * TILE_SIZE };
				_mapData.gumsPos.push_back(gumPos);
				break;
			case WALL_SPAWN:
				spawnWall = CreateSpawnWall(sf::Vector2i(j, i), _mapData.arr);
				_mapData.walls.push_back(spawnWall);
				break;
			case BONUS_SPAWN:
				_mapData.bonus.pos = { (float)j * TILE_SIZE, (float)i * TILE_SIZE };
				_mapData.bonus.pointText.setPosition(_mapData.bonus.pos.x + 16.f, _mapData.bonus.pos.y + 16.f);
				break;
			default:
				break;
			}
		}
	}
}

TileType* GetTilesAround(const sf::Vector2i _index, MapArray& _mapArray)
{
	TileType tiles[4] = { EMPTY, EMPTY, EMPTY, EMPTY }; // If there is no data the default value is EMPTY (-1)
	
	sf::Vector2i upIndex = { _index.x, _index.y - 1 };
	sf::Vector2i downIndex = { _index.x, _index.y + 1 };
	sf::Vector2i leftIndex = { _index.x - 1, _index.y };
	sf::Vector2i rightIndex = { _index.x + 1, _index.y };

	// check if index out of bounds
	if (upIndex.y >= 0)
	{
		tiles[UP] = _mapArray.data[upIndex.y][upIndex.x]; // set tileType
	}

	if (downIndex.y < _mapArray.rows)
	{
		tiles[DOWN] = _mapArray.data[downIndex.y][downIndex.x];
	}

	if (leftIndex.x >= 0)
	{
		tiles[LEFT] = _mapArray.data[leftIndex.y][leftIndex.x];
	}

	if (rightIndex.x < _mapArray.cols)
	{
		tiles[RIGHT] = _mapArray.data[rightIndex.y][rightIndex.x];
	}

	return tiles;
}

bool IsTileTraversable(const TileType _tile, const bool _gateSpawnTraversable)
{
	bool traversable;
	if (_gateSpawnTraversable)
	{
		traversable = (_tile != WALL && _tile != WALL_SPAWN);
	}
	else
	{
		traversable = (_tile != WALL && _tile != WALL_SPAWN && _tile != GATE_SPAWN);
	}

	return traversable;
}

int GetCost(const sf::Vector2i _pos1, const sf::Vector2i _pos2)
{
	sf::Vector2i cost;
	cost.x = (_pos1.x - _pos2.x) * (_pos1.x - _pos2.x);
	cost.y = (_pos1.y - _pos2.y) * (_pos1.y - _pos2.y);

	return cost.x + cost.y;
}

int* GetCostDir(const sf::Vector2i _objIndex, const sf::Vector2i _targetIndex, MapArray& _mapArray)
{
	int costDir[4] = { 10000, 10000, 10000, 10000 };
	
	TileType* tiles = GetTilesAround(_objIndex, _mapArray);

	sf::Vector2i upIndex = { _objIndex.x, _objIndex.y - 1 };
	sf::Vector2i downIndex = { _objIndex.x, _objIndex.y + 1 };
	sf::Vector2i leftIndex = { _objIndex.x - 1, _objIndex.y };
	sf::Vector2i rightIndex = { _objIndex.x + 1, _objIndex.y };
	if (IsTileTraversable(tiles[UP], true))
	{
		costDir[UP] = GetCost(upIndex, _targetIndex);
	}
	if (IsTileTraversable(tiles[DOWN], true))
	{
		costDir[DOWN] = GetCost(downIndex, _targetIndex);
	}
	if (IsTileTraversable(tiles[LEFT], true))
	{
		costDir[LEFT] = GetCost(leftIndex, _targetIndex);
	}
	if (IsTileTraversable(tiles[RIGHT], true))
	{
		costDir[RIGHT] = GetCost(rightIndex, _targetIndex);
	}

	return costDir;
}

int GetBonusPoint(Bonus& _bonus)
{
	int point = 0;
	switch (_bonus.type)
	{
	case CHERRIES:
		point = 300;
		break;
	case STRAWBERRY:
		point = 500;
		break;
	case ORANGE:
		point = 700;
		break;
	case APPLE:
		point = 1000;
		break;
	case WATERMELON:
		point = 2000;
		break;
	default:
		std::cerr << "BonusType not found in GetBonusPoint" << std::endl;
		break;
	}

	return point;
}

sf::FloatRect GetBonusRect(Bonus& _bonus)
{
	sf::FloatRect rect;
	rect.left = _bonus.pos.x + TILE_SIZE / 2;
	rect.top = _bonus.pos.y + TILE_SIZE / 2;
	rect.width = TILE_SIZE / 2;
	rect.height = TILE_SIZE / 2;

	return rect;
}

void ChangeToPastBonusType(Bonus& _bonus)
{
	if (_bonus.type - 1 < 0)
	{
		_bonus.type = CHERRIES;
	}
	else
	{
		_bonus.type = BonusType(_bonus.type - 1);
	}
}

void ChangeToNextBonusType(Bonus& _bonus)
{
	if (_bonus.type + 1 >= NUM_BONUS_TYPE)
	{
		_bonus.type = CHERRIES;
	}
	else
	{
		_bonus.type = BonusType(_bonus.type + 1);
	}
}

void EatBonus(Bonus& _bonus)
{
	std::string tempString = std::to_string(GetBonusPoint(_bonus));
	SetCenteredString(_bonus.pointText, tempString);
	_bonus.textTimer = BONUS_TEXT_TIME;

	ChangeToNextBonusType(_bonus);
	_bonus.visible = false;
	_bonus.timer = GET_BONUS_TIME(_bonus.type);
}

void UpdateMap(MapData& _mapData, GameState& _gameState, float _dt)
{
	_mapData.timer += _dt;
	_mapData.bonus.timer -= _dt;
	_mapData.bonus.textTimer -= _dt;

	if (_mapData.dotsPos.size() == 0 && _mapData.gumsPos.size() == 0)
	{
		_gameState = INIT_WIN_GAME;
	}

	if (_mapData.bonus.timer <= 0)
	{
		if (_mapData.bonus.visible)
		{
			_mapData.bonus.visible = false;
			ChangeToPastBonusType(_mapData.bonus);
			_mapData.bonus.timer += GET_BONUS_TIME(_mapData.bonus.type);
		}
		else
		{
			_mapData.bonus.visible = true;
			_mapData.bonus.timer += GET_BONUS_VISIBLE_TIME(_mapData.bonus.type);
		}
	}
}

void DisplayMap(MapData& _mapData, sf::RenderWindow& _window)
{
	int gumVisible = (int)(_mapData.timer * 2) % 2;
	if (gumVisible)
	{
		for (int i = 0; i < _mapData.gumsPos.size(); i++)
		{
			BlitSprite(_mapData.gumSprite, _window, _mapData.gumsPos[i]);
		}
	}

	for (int i = 0; i < _mapData.walls.size(); i++)
	{
		BlitSprite(_mapData.wallSprites[_mapData.walls[i].type], _window, _mapData.walls[i].pos);
	}

	for (int i = 0; i < _mapData.dotsPos.size(); i++)
	{
		BlitSprite(_mapData.dotSprite, _window, _mapData.dotsPos[i]);
	}

	if (_mapData.bonus.visible)
	{
		BlitSprite(_mapData.bonusSprites[_mapData.bonus.type], _window, _mapData.bonus.pos);
	}
	else if (_mapData.bonus.textTimer > 0)
	{
		_window.draw(_mapData.bonus.pointText);
	}
}