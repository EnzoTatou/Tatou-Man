#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Map.hpp"

#define DEATH_TIME 1.25f

typedef Dir PlayerDir;

enum PlayerState
{
	ALIVE,
	EAT_GUM,
	DEAD
};

struct PlayerKey
{
	sf::Keyboard::Key up = sf::Keyboard::Key::Up;
	sf::Keyboard::Key down = sf::Keyboard::Key::Down;
	sf::Keyboard::Key left = sf::Keyboard::Key::Left;
	sf::Keyboard::Key right = sf::Keyboard::Key::Right;
};

struct Player
{
	sf::Text scoreText;

	sf::Sprite walkSprite[4];
	sf::Sprite deathSprite[9];
	Animation walkAnimation;
	Animation deathAnimation;

	sf::Sound deathSounds[2];
	sf::Sound eatSounds[4];
	sf::Sound newLifeSound;

	PlayerKey key;

	int life = 3;
	int newLifeScore = 10000;
	int score = 0;
	float speed = 128;
	PlayerState state = ALIVE;
	float deadTimer = DEATH_TIME;

	sf::Vector2f oldPos = { 0.f, 0.f };
	sf::Vector2f currentPos = { 0.f, 0.f };
	PlayerDir currentDir = RIGHT;
	PlayerDir newDir = RIGHT;
};

void InitPlayer(Player& _player, MapArray& _mapArray, sf::Font& _font);
void ReloadPlayer(Player& _player, MapArray& _mapArray);
sf::FloatRect GetPlayerCollisionRect(Player& _player);
sf::FloatRect GetPlayerSpriteRect(Player& _player);
sf::Vector2i GetPlayerArrayIndex(Player _player);
void UpdatePlayerNewDir(Player&, KeyData&);
void UpdatePlayer(Player& _player, GameState& _gameState, MapData& _mapData, KeyData& _keyData, float _dt);
void DisplayPlayer(Player&, sf::RenderWindow&);
void DisplayPlayerHUD(Player& _player, MapArray& _mapArray, sf::RenderWindow& _window);

#endif