#pragma once
#include "game.h"
#include "server.h"

class Player;

enum NewPlayerMenuState
{
	NEW_CONNECTION,
	GET_PLAYER_NAME,
	GET_PLAYER_PASSWORD,
	GET_PLAYER_STATS
};

class Nanny
{
public:
	static void *greetPlayer(void *clientfd);
	static void newPlayerMenu(int clientfd);
	static std::string getPlayerName(int clientfd);
	static std::string getPlayerPassword(int clientfd);
	static void printBanner(int clientfd);
	static std::vector<int> rollStats(int clientfd);
	static void gameLoop(Player *player);
};
