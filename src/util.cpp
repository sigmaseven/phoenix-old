#include "util.h"

int32_t Util::sendToPlayer(int clientfd, std::string message)
{
	int status;
	if(clientfd < 0)
	{
		std::cerr << "Util::sendToPlayer - Received invalid client descriptor" << std::endl;
		return -1;
	}
	status = send(clientfd, message.c_str(), message.length(),0);
	return status;
}

std::string Util::recvFromPlayer(int clientfd, int length)
{
	char buffer[MAX_INPUT + 1];
	int status;

	if(clientfd < 0)
	{
		std::cerr << "Util::recvFromPlayer - Received invalid client descriptor" << std::endl;
		return std::string("");
	}

	memset(&buffer, 0, sizeof(buffer));

	status = recv(clientfd, &buffer, length, 0);

	if(status < 0)
	{
		std::cerr << "Error retrieving input from player!" << std::endl;
		std::string received("");
		perror("recv");
		return received;
	}

	std::string received(buffer);
	return received;
}

std::string Util::getPlayerCommand(Player *player)
{
	std::string command;
	command = Util::readLineFromSocket(player->getFileDescriptor());
	std::cout << "Command received: " << command << std::endl;
	return command;
}

std::string Util::getPlayerCommand(int clientfd)
{
	std::string command;
	command = Util::readLineFromSocket(clientfd);
	std::cout << "Command received: " << command << std::endl;
	return command;
}

std::string Util::readLineFromSocket(int clientfd)
{
	std::string line;
	std::string part;

	part = Util::recvFromPlayer(clientfd, 1);
	std::cout << "getting player command" << std::endl;

	while(part.length() > 0 && part != "\n")
	{
		if(part != "\r")
		{
			std::cout << "byte received: " << part << std::endl;
			line += part;
		}
		else
		{
		}
		part = Util::recvFromPlayer(clientfd, 1);
	}
	return line;
}
