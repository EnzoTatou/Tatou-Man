#ifndef GAME_HPP
#define GAME_HPP

#include "Ghost.hpp"

#define NEW_GAME_TIME 4.5f

struct GameData
{
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Event event;
	sf::Font font;

	float newGameTimer = NEW_GAME_TIME;
	sf::Sound gameStartSound;
	sf::Sound eatenSound;
	sf::Sound scatterSound;
	sf::Sound chaseSound;
	sf::Sound frightenedSound;

	KeyData keyData;
	GameState gameState;

	MapData mapData;

	Player player;
	Ghost enemies[NUM_GHOST];
};

#endif