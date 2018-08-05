#pragma once
#include "game.h"
#include "server.h"
#include "nanny.h"
#include "playermanager.h"

class Player;

class Util
{
	static unsigned int seed;
public:
	static int sendToPlayer(int fd, std::string message);
	static std::string recvFromPlayer(int fd, int length);
	static std::vector<std::string> getPlayerCommand(Player *player);
	static std::string readLineFromSocket(int fd);
	static std::vector<std::string> getPlayerCommand(int clientfd);
	static std::vector<std::string> splitLine(std::string line);
	static int rollDice(int number, int size);
	static void printError(const char *message);
	static void printServer(const char *message);
	static std::string hash(std::string string);
	static bool validatePassword(std::string password);
	static long getCurrentTime();
	static std::string getColorString(int forground, std::string message);
};
