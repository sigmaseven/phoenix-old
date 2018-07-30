#pragma once
#include "game.h"
#include "server.h"
#include "nanny.h"
#include "playermanager.h"

class Util
{
public:
	static int sendToPlayer(int fd, std::string message);
	static std::string recvFromPlayer(int fd, int length);
	static std::string getPlayerCommand(Player *player);
	static std::string readLineFromSocket(int fd);
	static std::string getPlayerCommand(int clientfd);
};
