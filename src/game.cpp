#include "game.h"
#include "server.h"
#include "playermanager.h"

int main(int argc, char *argv[])
{
	PlayerManager::init();
	Server *server = new Server();
	server->setup();

	delete(server);
	return(0);
}
