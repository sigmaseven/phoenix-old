#include "nanny.h"
#include "util.h"
#include "playermanager.h"

void *Nanny::greetPlayer(void *clientfd)
{
	int *fd = (int *)clientfd;

	if(fd > 0)
	{
		Nanny::newPlayerMenu(*fd);
	}
	else
	{
		std::cerr << "Nanny received invalid client file descriptor!" << std::endl;
	}
}

void Nanny::newPlayerMenu(int clientfd)
{
	std::string name;
	std::string password;

	Nanny::printBanner(clientfd);
	name = Nanny::getPlayerName(clientfd);
	password = Nanny::getPlayerPassword(clientfd);

	std::cout << "Creating new player " << name << " with password " << password << std::endl;
	Player *player = PlayerManager::findOpenPlayerSlot();

	if(player)
	{
		player->setName(name);
		player->setPassword(password);
		player->setActive(true);
		player->setFileDescriptor(clientfd);
	}
	else
	{
		std::cerr << "Reached maximum amount of players." << std::endl;
		Util::sendToPlayer(clientfd, std::string("Maximum number of players reached.\n"));
	}
}

void Nanny::printBanner(int clientfd)
{
	Util::sendToPlayer(clientfd, std::string("INSERT BANNER HERE\n\n"));
}

std::string Nanny::getPlayerName(int clientfd)
{
	Util::sendToPlayer(clientfd, std::string("Hey there, who are you? "));

	std::string name = Util::getPlayerCommand(clientfd);
	return name;
}

std::string Nanny::getPlayerPassword(int clientfd)
{
	Util::sendToPlayer(clientfd, std::string("What's your password? "));

	std::string password = Util::getPlayerCommand(clientfd);
	return password;
}
