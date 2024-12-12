#include "Init.hpp"
#include "Event.hpp"
#include "Update.hpp"
#include "Display.hpp"

int main()
{
	GameData* gameData = new GameData(); // create gameData in the heap
	Init(*gameData);

	while (gameData->window.isOpen())
	{
		CheckInitState(*gameData);
		Event(*gameData);
		Update(*gameData);
		Display(*gameData);
	}

	delete gameData; // delete gameData from the heap
	return 0;
}