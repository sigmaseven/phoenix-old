#pragma once
#include "./game.h"

class Server
{
	int sockfd;
	struct addrinfo host;
	struct addrinfo *server_info;


public:
	void setup();
	void acceptConnections();
};
