#include "game.h"
#include "server.h"
#include "playermanager.h"
#include "util.h"
#include "command.h"

int main(int argc, char *argv[])
{
	pthread_t player_manager_thread;
	void *blank_thread_command;

	PlayerManager::init();
	pthread_create(&player_manager_thread, NULL, &PlayerManager::update, blank_thread_command);
	Server *server = new Server();
	server->setup();

	delete(server);
	return(0);
}
