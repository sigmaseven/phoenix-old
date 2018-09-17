#pragma once
#include "./game.h"
#include "./util.h"
#include "./nanny.h"

enum ServerType
{
	SERVER_TEXT,
	SERVER_PACKET
};

class Server
{
	int sockfd;
	int port;
	bool encrypted;
	ServerType type;
	struct addrinfo host;
	struct addrinfo *server_info;
	SSL_CTX *ssl_context;
	SSL_METHOD *ssl_method;
	SSL *ssl;

public:
	void setup();
	void setupTLS();
	void acceptConnections();

	int getPort();

	ErrorCode setPort(int port);
	ErrorCode setEncryption(bool option);
};
