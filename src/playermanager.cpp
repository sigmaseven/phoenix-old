#include "playermanager.h"

std::vector<Player *> PlayerManager::players;

void PlayerManager::init()
{
	int x;

	std::cout << "Initializing player pool." << std::endl;

	for(x = 0; x < MAX_PLAYERS; x++)
	{
		Player *player = new Player();
		player->setActive(false);
		players.push_back(player);
	}
}

Player *PlayerManager::findOpenPlayerSlot()
{
	int x;

	for(x = 0; x < MAX_PLAYERS; x++)
	{
		Player *player = players[x];

		if(!player->getActive())
		{
			return player;
		}
	}

	return NULL;
}
