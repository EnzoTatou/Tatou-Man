#ifndef GHOST_HPP
#define GHOST_HPP
#include "Player.hpp"

#define GHOST_EYE_SPRITE 6
#define GHOST_MOVE_SPRITE 5

#define CLYDE_RADIUS_CHASE 4

#define CHASE_TIME 20.f // time it takes the state to change from chase to scatter
#define SCATTER_TIME 8.f // time it takes the state to change from scatter to chase
#define FRIGHTENED_TIME 10.f // time it takes the state to change from frightened to scatter

#define CHASE_SPEED 130.f // goes 2 pixel per second faster than player
#define SCATTER_SPEED 128.f
#define EATEN_SPEED SCATTER_SPEED * 2
#define FRIGHTENED_SPEED SCATTER_SPEED / 2

#define NUM_GHOST 4

typedef Dir GhostDir;

enum GhostType
{
	BLINKY,		// Red ghost
	PINKY,		// Pink ghost
	INKY,		// Lite blue ghost
	CLYDE		// Orange ghost
};

enum GhostState
{
	SPAWN,
	CHASE, // go to player
	SCATTER, // go to scatter
	FRIGHTENED, // panic mode
	EATEN // go back to spawn
};

struct GhostAnimation
{
	sf::Sprite sprites[7][5]; // 7 animation containing 5 sprites

	Animation walking[5]; // 5 normal animation
	Animation frightened[2]; // 2 special animation
};

struct Ghost
{
	GhostType type = PINKY;
	GhostState state = SPAWN;
	GhostAnimation animation;

	sf::Text pointText;

	float speed = SCATTER_SPEED;

	float chaseTimer = 0;
	float scatterTimer = SCATTER_TIME;
	float frightenedTimer = 0;

	sf::Vector2i spawnPos = { 0, 0 };
	sf::Vector2f oldPos = { 0.f, 0.f };
	sf::Vector2f currentPos = { 0.f, 0.f };

	GhostDir currentDir = GhostDir(rand() % 4);
	GhostDir newDir = GhostDir(rand() % 4);
};

void InitGhost(Ghost [NUM_GHOST], MapArray&, sf::Font& _font);

void ReloadGhosts(Ghost [NUM_GHOST]);

void CreateGhostAnimations(GhostAnimation&, sf::Sprite[GHOST_EYE_SPRITE], sf::Sprite[GHOST_MOVE_SPRITE], sf::Color);

void CreateGhost(Ghost&, GhostType, sf::Sprite[GHOST_EYE_SPRITE], sf::Sprite[GHOST_MOVE_SPRITE], sf::Vector2i);

bool IsGhostCollideWall(Ghost&, std::vector<Wall>);

void UpdateGhostTimers(Ghost& _ghost, float _dt);

void UpdateGhost(Ghost&, Ghost&, Player&, MapData&, float);

void DisplayGhost(Ghost&, sf::RenderWindow&);

#endif //GHOST_HPP