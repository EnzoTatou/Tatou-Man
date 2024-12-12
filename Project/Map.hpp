#ifndef MAP__HPP
#define MAP__HPP
#include "Definition.hpp"
#include <sstream>

#define BONUS_TIME 15
#define BONUS_VISIBLE_TIME 10.f
#define BONUS_TEXT_TIME 2.f

// time taken to make a bonus appear
#define GET_BONUS_TIME(type) (BONUS_TIME * (type + 1))
// time the bonus will be visible
#define GET_BONUS_VISIBLE_TIME(type) (BONUS_VISIBLE_TIME - type)

enum TileType
{
	EMPTY = -1, // special tile for emptying one 
	GATE_SPAWN, // spawn door 

	WALL,
	DOT,
	GUM,

	SPAWN_TATOU, // where tatou-man respawn 

	SPAWN_INKY, // where inky respawn and calculate their SPAWN target
	SPAWN_PINKY,
	SPAWN_CLYDE,
	SPAWN_BLINKY,

	WALL_SPAWN, // special wall for ghost spawn

	BONUS_SPAWN
};

enum WallType
{
	WALL_DEFAULT,

	WALL_DOWN_RIGHT_LEFT,
	WALL_LEFT_UP_DOWN,
	WALL_DOWN_LEFT,
	WALL_UP_RIGHT_LEFT,
	WALL_LEFT_RIGHT,
	WALL_UP_LEFT,
	WALL_LEFT,
	WALLL_RIGHT_UP_DOWN,
	WALL_DOWN_RIGHT,
	WALL_UP_DOWN,
	WALL_DOWN,
	WALL_UP_RIGHT,
	WALL_RIGHT,
	WALL_UP,
	WALL_UP_DOWN_LEFT_RIGHT,


	SPAWN_WALL_CORNER_LD,
	SPAWN_WALL_CORNER_LU,
	SPAWN_WALL_CORNER_RD,
	SPAWN_WALL_CORNER_RU,

	SPAWN_WALL_VERTICAL,
	SPAWN_WALL_HORIZONTAL,

	SPAWN_WALL_GATE,

	NUM_WALL_TYPE
};

enum BonusType
{
	CHERRIES,
	STRAWBERRY,
	ORANGE,
	APPLE,
	WATERMELON,

	NUM_BONUS_TYPE
};

struct Wall
{
	WallType type = WALL_DEFAULT;
	sf::Vector2f pos = { 0, 0 };
};

struct Bonus
{
	BonusType type = CHERRIES;
	sf::Vector2f pos = { 0, 0 };

	float textTimer = 0.f;
	sf::Text pointText;

	float timer = BONUS_TIME * (type + 1);
	bool visible = false;
};

struct MapArray
{
	TileType** data; // 2D array containing every tile
	int rows; // map height
	int cols; // map width
};

struct MapData
{
	float timer = 0.f;
	MapArray arr;

	sf::Sprite wallSprites[NUM_WALL_TYPE];
	sf::Sprite dotSprite;
	sf::Sprite gumSprite;
	sf::Sprite bonusSprites[NUM_BONUS_TYPE];

	std::vector<Wall> walls;
	std::vector<sf::Vector2f> dotsPos;
	std::vector<sf::Vector2f> gumsPos;
	Bonus bonus;
};

void InitMap(MapData& _mapData, sf::Font& _font);

// Small function returning a 2D array ptr of TileType
TileType** Create2DTileArray(const int _cols, const int _rows);

// Create map from txt
// Each rows has to be the exact same width !!!
MapArray CreateMapArray(const std::string _filePath);

Wall CreateWall(sf::Vector2i _tilePos, MapArray& _mapArray);
void CreateDots(std::vector<sf::Vector2f>& _dotsPos, sf::Vector2i _tilePos, MapArray& _mapArray);
Wall CreateSpawnWall(const sf::Vector2i _tilePos, MapArray& _mapArray);

void ReadMapArray(MapData& _mapData);

/// <summary>
/// Return a list of all the neighbour wall type. 
/// If a neighbour don't exist there value is empty.
/// </summary>
/// <param name="_index"> : Original tile pos</param>
/// <param name="_mapArray"> : 2D array to check pos</param>
/// <returns>List of all the neighbour wall type</returns>
TileType* GetTilesAround(const sf::Vector2i _index, MapArray& _mapArray);
bool IsTileTraversable(const TileType _tile, const bool _gateSpawnTraversable = false);

int GetCost(const sf::Vector2i _pos1, const sf::Vector2i _pos2);
int* GetCostDir(const sf::Vector2i _objIndex, const sf::Vector2i _targetIndex, MapArray& _mapArray);

int GetBonusPoint(Bonus& _bonus);
sf::FloatRect GetBonusRect(Bonus& _bonus);
void ChangeToNextBonusType(Bonus& _bonus);
void EatBonus(Bonus& _bonus);

void UpdateMap(MapData& _mapData, GameState& _gameState, float _dt);
void DisplayMap(MapData& _mapData, sf::RenderWindow& _window);

#endif //MAP__HPP