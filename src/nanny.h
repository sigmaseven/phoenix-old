#pragma once
#include "./game.h"
#include "./server.h"

class Player;

class Nanny
{
public:
	static void *greetPlayer(void *clientfd);
	static void newPlayerMenu(int clientfd);
	static std::string getPlayerName(Player *player);
	static std::string getPlayerPassword(Player *player);
	static void printBanner(int clientfd);
	static std::vector<int> rollStats(int clientfd);
	static void gameLoop(Player *player);
};
