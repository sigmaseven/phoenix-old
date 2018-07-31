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

void PlayerManager::writePlayerFile(Player *player)
{
	nlohmann::json j;

	j["name"] = player->getName();
	j["password"] = player->getPassword();
	j["health"] = player->getHealth();
	j["max_health"] = player->getMaxHealth();
	j["movement"] = player->getMovement();
	j["max_movement"] = player->getMaxMovement();
	j["stats"]["strength"] = player->getStrength();
	j["stats"]["perception"] = player->getPerception();
	j["stats"]["endurance"] = player->getEndurance();
	j["stats"]["charisma"] = player->getCharisma();
	j["stats"]["intelligence"] = player->getIntelligence();
	j["stats"]["agility"] = player->getAgility();
	j["stats"]["luck"] = player->getLuck();

	std::cout << j.dump() << std::endl;
}
