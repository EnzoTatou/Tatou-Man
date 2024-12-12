#ifndef DEFINITION__HPP
#define DEFINITION__HPP
// visual studio lib
#include <iostream>
#include <time.h>
#include <vector>
// SFML lib
#include "SFML/Network.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/Audio.hpp"
// Utilities librairies
#include "FileReader.hpp"

#include "Sound.hpp"
#include "Sprite.hpp"
#include "Key.hpp"

#include "Animation.hpp"

#define DEFAULT_SIZE_TEXT 24
#define TILE_SIZE 32

#define GET_BINARY(var, n) ((1 << n) & var)
#define SET_BINARY(var, n) (var |= 1 << n)
#define UNSET_BINARY(var, n) (var &= ~(1 << n))

enum Dir
{
	RIGHT,
	DOWN,
	LEFT,
	UP
};

enum GameState
{
	CLOSE,
	GAME,
	GAME_PAUSE,

	// Init state are states that load data before going into the original 
	// state so we can easily load everything in CheckInitState().
	// Only use those states for reloading a state!!!

	INIT_GAME,
	INIT_WIN_GAME
};

void InitWindow(sf::RenderWindow&, sf::Vector2u);

sf::Text CreateText(sf::Font&, const sf::String = "", int = DEFAULT_SIZE_TEXT, sf::Color = sf::Color::White);

void SetCenteredString(sf::Text& _text, const sf::String _string);

void SetWindowIcon(sf::RenderWindow&, const std::string&);

// Collision Rectangle non orienté/Dot.
bool IsCollidingRectanglePoint(sf::FloatRect, sf::Vector2f);

/// <summary>
/// Check if two rectangle are colliding each other
/// </summary>
/// <param name="_rectA"> First rectangle</param>
/// <param name="_rectB"> Second rectangle</param>
/// <returns> true if one of the rect overlay the other rect</returns>
bool IsCollidingRectangles(sf::FloatRect, sf::FloatRect);
#endif