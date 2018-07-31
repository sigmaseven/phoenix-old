#include "util.h"

unsigned int Util::seed = 0;

int32_t Util::sendToPlayer(int clientfd, std::string message)
{
	int status;
	if(clientfd < 0)
	{
		std::cerr << "Util::sendToPlayer - Received invalid client descriptor" << std::endl;
		return -1;
	}
	if(fcntl(clientfd, F_GETFD) != -1)
	{
		status = send(clientfd, message.c_str(), message.length(), MSG_NOSIGNAL);
	}
	return status;
}

std::string Util::recvFromPlayer(int clientfd, int length)
{
	char buffer[MAX_INPUT_SIZE + 1];
	int status;

	if(clientfd < 0)
	{
		std::cerr << "Util::recvFromPlayer - Received invalid client descriptor" << std::endl;
		return std::string("");
	}
	if(fcntl(clientfd, F_GETFD) != -1)
	{
		memset(&buffer, 0, sizeof(buffer));

		status = recv(clientfd, &buffer, length, 0);
	}

	if(status < 0)
	{
		std::cerr << "Error retrieving input from player!" << std::endl;
		std::string received("");
		perror("recv");
		return received;
	}
	else if(status == 0) //player disconnected.
	{
		std::cout << "Player disconnected." << std::endl;
		//PlayerManager::resetPlayer(int clientfd);
		close(clientfd);
		return std::string("");
	}

	std::string received(buffer);
	return received;
}

std::vector<std::string> Util::getPlayerCommand(Player *player)
{
	std::string line;
	std::vector<std::string> command;
	line = Util::readLineFromSocket(player->getFileDescriptor());
	//std::cout << "Command received: " << line << std::endl;
	command = Util::splitLine(line);
	return command;
}

std::vector<std::string> Util::getPlayerCommand(int clientfd)
{
	std::string line;
	std::vector<std::string> command;

	line = Util::readLineFromSocket(clientfd);
	//std::cout << "Command received: " << line << std::endl;

	command = Util::splitLine(line);
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
		if(part != "\r" && part != "\t")
		{
			line += part;
		}
		else
		{
		}
		part = Util::recvFromPlayer(clientfd, 1);
	}
	return line;
}

std::vector<std::string> Util::splitLine(std::string line)
{
	std::stringstream ss(line);
	std::string item;
	std::vector<std::string> commands;

	while(std::getline(ss, item, ' '))
	{
		commands.push_back(item);
	}
	return commands;
}

int Util::rollDice(int number, int size)
{
	int total = 0;
	int x;

	if(seed == 0)
	{
		struct timeval tp;
		gettimeofday(&tp, NULL);
		seed = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	}

	for(x = 0; x < number; x++)
	{
		int roll = rand_r(&seed) % size;

		if(roll == 0)
			roll = 1;

		total += roll;
	}

	return total;
}
