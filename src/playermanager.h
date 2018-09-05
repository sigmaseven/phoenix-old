#pragma once
#include "./game.h"
#include "./server.h"
#include "./nanny.h"
#include "./util.h"
#include "./areamanager.h"
#include "./player.h"

class PlayerManager
{
	static std::vector<Player *> players;
public:
	static long update_timestamp;
	static void init();
	static Player *findOpenPlayerSlot();
	static void writePlayerFile(Player *player);
	static bool playerFileExists(std::string name);
	static void resetPlayer(Player *player);
	static void readPlayerFile(Player *player, std::string name);
	static void *update(void *cmd);
	static std::vector<Player *> getActivePlayers();
	static long getLastUpdate(){ return PlayerManager::update_timestamp; }
	static void setLastUpdate(long timestamp){ PlayerManager::update_timestamp = timestamp; }
	static bool isPlayerOnline(std::string name);
	static Player *findPlayerByDescriptor(int fd);
	static void broadcast(std::string message);
};
