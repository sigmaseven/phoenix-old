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
	int ret;
	Player *player = PlayerManager::findPlayerByDescriptor(clientfd);

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
		close(clientfd);
		pthread_exit(&ret);
		//return received;
	}
	else if(status == 0) //player disconnected.
	{
		std::cout << "Player disconnected." << std::endl;
		PlayerManager::resetPlayer(player);
		close(clientfd);
		pthread_exit(&ret);
		//return std::string("");
	}

	std::string received(buffer);
	return received;
}

std::vector<std::string> Util::getPlayerCommand(Player *player)
{
	std::string line;
	std::vector<std::string> command;
	line = Util::readLineFromSocket(player->getFileDescriptor());

	command = Util::splitLine(line);
	return command;
}

std::vector<std::string> Util::getPlayerCommand(int clientfd)
{
	std::string line;
	std::vector<std::string> command;

	line = Util::readLineFromSocket(clientfd);

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

long Util::getCurrentTime()
{
	long time;
	struct timeval tp;
	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return time;
}
void Util::printError(const char *message)
{
	std::cerr << "[!] " << message << std::endl;
}

void Util::printServer(const char *message)
{
	std::cout << "[+] " << message << std::endl;
}

std::string Util::hash(std::string string)
{
	unsigned char hash[SHA_DIGEST_LENGTH];
	int x;

	memset(hash, 0, sizeof(hash));

	if(string.length() > 0)
	{
		char sha_hash[SHA_DIGEST_LENGTH * 2 + 1];
		memset(sha_hash, 0, sizeof(sha_hash));
		SHA1((const unsigned char *)string.c_str(), string.length(), hash);

		for(x = 0; x < SHA_DIGEST_LENGTH; x++)
		{
			sprintf(&sha_hash[x * 2], "%02x", (unsigned int)hash[x]);
		}
		return std::string(sha_hash);
	}
	return std::string("");
}

bool Util::validatePassword(std::string password)
{
	int x;

	for(x = 0; x < password.length(); x++)
	{
		char c = password[x];

		if(c < 32 || c > 126)
		{
			return false;
		}
	}

	return true;
}

std::string Util::getColorString(int foreground, std::string message)
{
	std::stringstream ss;
	ss << "\033[38;" << foreground << ";1m" << message << "\033[38;37;0m";
	return ss.str();
}

std::string Util::readFromFile(const char *filename)
{
	FILE *file;
	char *buffer = (char *)malloc(sizeof(char) * 1024);
	memset(buffer, 0, 1024);
	std::stringstream contents;

	if(!buffer)
	{
		Util::printError("Couldn't allocate file buffer!");
		return std::string("");
	}

	file = fopen(filename, "r");

	if(!file)
	{
		Util::printError("Error opening file!");
		return std::string("");
	}

	 while(fgets(buffer, 1024, file) > 0)
		contents << buffer;

	fclose(file);
	free(buffer);
	return contents.str();
}
