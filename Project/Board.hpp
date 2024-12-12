#ifndef BOARD_H
#define BOARD_H

#include "Definition.hpp"
#include "River.hpp"
#include "Effects.hpp"
#include "Competences.hpp"

#define PoEarnTurn 2

enum BoardState
{
	PURCHASE_TURN,
	END_PURCHASE,
	ATTACK_TURN,

	END_TURN /// << THE LAST STATE BEFORE ANOTHER TURN BEGIN
};

struct BoardStruct
{
	sf::Text turnText;
	sf::Texture skipButtonTexture;
	sf::Texture skipButtonHoverTexture;
	Button skipButton;

	sf::Texture texture;
	sf::Sprite sprite;
	BoardState state;
	Hero* heroTurn;
	Hero* heroStart;

	std::deque<Card> cardsPack;
	std::deque<Card> cardsGraveyard;
	RiverStruct river;

	Card* cardHolding = 0;

	int turn = 0;
	Hero player;
	Hero enemy;
}; 

void InitBoard(BoardStruct&, sf::Font&, sf::RenderWindow&);
void PollEventBoard(BoardStruct&, MouseData&, sf::Event&);
void UpdateBoard(BoardStruct&, MouseData&, float);

// Display everything on board, players decks, river, heros ect..
void DisplayBoard(BoardStruct&, sf::RenderWindow&);

Hero* GetHeroNotPlaying(BoardStruct&);
// Change the board state to the next logical state depending on the hero turn ect..
void SetNextBoardState(BoardStruct&);
// Change the heroTurn ptr to point to the other hero.
void SwapHeroTurn(BoardStruct&);
// Change the heroStart ptr to point to the other hero.
void SwapHeroStart(BoardStruct&);

// Search if a card in a deck is shield.
bool GetIfShildCard(Card[5]);
bool IsBoardEmpty(BoardStruct&);
#endif