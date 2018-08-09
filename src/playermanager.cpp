#include "./playermanager.h"

std::vector<Player *> PlayerManager::players;
long PlayerManager::update_timestamp;

void PlayerManager::init()
{
	int x;

	Util::printServer("Initializing player pool.");

	for(x = 0; x < MAX_PLAYERS; x++)
	{
		Player *player = new Player();
		player->setActive(false);
		player->setRoom(1);
		players.push_back(player);
	}

	PlayerManager::update_timestamp = Util::getCurrentTime();
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
	std::ofstream file;
	DIR *directory;

	j["name"] = player->getName();
	j["password"] = player->getPassword();
	j["health"] = player->getHealth();
	j["max_health"] = player->getMaxHealth();
	j["movement"] = player->getMovement();
	j["max_movement"] = player->getMaxMovement();
	j["room"] = player->getRoom();
	j["stats"]["strength"] = player->getStrength();
	j["stats"]["perception"] = player->getPerception();
	j["stats"]["endurance"] = player->getEndurance();
	j["stats"]["charisma"] = player->getCharisma();
	j["stats"]["intelligence"] = player->getIntelligence();
	j["stats"]["agility"] = player->getAgility();
	j["stats"]["luck"] = player->getLuck();
	std::cout << j.dump() << std::endl;
	directory = opendir("players");
	if(!directory)
	{
		mkdir("players", 0700);
	}
	file.open("players/" + player->getName() + ".json");
	if(file.is_open())
	{
		file << j.dump();
		file.close();
	}
	else
	{
		Util::printError("Couldn't open player file for writing!");
	}
}

void PlayerManager::readPlayerFile(Player *player, std::string name)
{
	DIR *directory;
	FILE *file;
	std::string filename("players/" + name + ".json");
	char *buffer = (char *)malloc(sizeof(char) * 32);

	memset(buffer, 0, 32);

	std::stringstream contents;

	directory = opendir("players");

	if(!directory)
	{
		mkdir("players", 0700);
	}

	file = fopen(filename.c_str(), "r");

	if(!file)
	{
		Util::printError("Error opening player file!");
		return;
	}
	else
	{
		while(fgets(buffer, 32, file) > 0)
			contents << buffer;
	}
	fclose(file);
	free(buffer);
	Util::printServer(contents.str().c_str());
	auto j = nlohmann::json::parse(contents.str().c_str());

	player->setHealth(j["health"]);
	player->setMaxHealth(j["max_health"]);
	//player->setMana(j["mana"]);
	//player->setMaxMana(j["max_mana"]);
	player->setRoom(j["room"]);
	player->setMovement(j["movement"]);
	player->setMaxMovement(j["max_movement"]);
	player->setPassword(j["password"]);
	player->setStrength(j["stats"]["strength"]);
	player->setPerception(j["stats"]["perception"]);
	player->setEndurance(j["stats"]["endurance"]);
	player->setCharisma(j["stats"]["charisma"]);
	player->setIntelligence(j["stats"]["intelligence"]);
	player->setAgility(j["stats"]["agility"]);
	player->setLuck(j["stats"]["luck"]);

	player->setActive(true);
}

bool PlayerManager::playerFileExists(std::string name)
{
	DIR *directory;
	FILE *file;
	std::string filename("players/" + name + ".json");

	directory = opendir("players");

	if(!directory)
	{
		mkdir("players", 0700);
	}

	file = fopen(filename.c_str(), "r");

	if(file)
	{
		fclose(file);
		return true;
	}
	return false;
}

void PlayerManager::resetPlayer(Player *player)
{
	if(player)
	{
		player->getName().clear();
		player->getPassword().clear();
		player->setFileDescriptor(-1);

		player->setHealth(0);
		player->setMaxHealth(0);
		player->setMana(0);
		player->setMaxMana(0);
		player->setMovement(0);
		player->setMaxMovement(0);
		player->setStrength(0);
		player->setPerception(0);
		player->setEndurance(0);
		player->setCharisma(0);
		player->setIntelligence(0);
		player->setAgility(0);
		player->setLuck(0);
		player->setRoom(1);
		player->setActive(false);
	}
}

std::vector<Player *> PlayerManager::getActivePlayers()
{
	int x;
	std::vector<Player *> found;

	for(x = 0; x < players.size(); x++)
	{
		if(players[x]->getActive())
		{
			found.push_back(players[x]);
		}
	}
	return found;
}

void *PlayerManager::update(void *cmd)
{
	for(;;)
	{
		int x;

		std::vector<Player *> players = PlayerManager::getActivePlayers();

		for(x = 0; x < players.size(); x++)
		{
			Util::sendToPlayer(players[x]->getFileDescriptor(), std::string("\nPING!\n"));
		}
		sleep(60);
	}
}

bool PlayerManager::isPlayerOnline(std::string name)
{
	std::vector<Player *> active_players = PlayerManager::getActivePlayers();
	int x;
	for(x = 0; x < active_players.size(); x++)
	{
		std::string player_name = active_players[x]->getName();
		if(player_name.compare(name) == 0)
		{
			return true;
		}
	}
	return false;
}

Player *PlayerManager::findPlayerByDescriptor(int fd)
{
	std::vector<Player *> active_players = PlayerManager::getActivePlayers();

	int x;
	for(x = 0; x < active_players.size(); x++)
	{
		if(active_players[x]->getFileDescriptor() == fd)
		{
			return active_players[x];
		}
	}
	return NULL;
}

void Player::moveToRoom(uint32_t room_number, Exit direction)
{
	std::cout << "moving to room number " << room_number << std::endl;
	if(room_number > 0)
	{
		this->room = room_number;
	}
}
