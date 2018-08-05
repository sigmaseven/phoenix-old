#include "nanny.h"
#include "util.h"
#include "playermanager.h"
#include "command.h"

void *Nanny::greetPlayer(void *clientfd)
{
	int *fd = (int *)clientfd;

	if(fd > 0)
	{
		Nanny::newPlayerMenu(*fd);
	}
	else
	{
		Util::printError("Nanny received invalid client file descriptor!");
	}
}

void Nanny::newPlayerMenu(int clientfd)
{
	std::string name = "";
	std::string password = "";
	uint8_t strength, perception, endurance, charisma, intelligence, agility, luck;
	int ret;

	Nanny::printBanner(clientfd);

	while(name.length() < 1)
	{
		name = Nanny::getPlayerName(clientfd);

		if(fcntl(clientfd, F_GETFD) == -1)
			pthread_exit(&ret);
	}

	while(password.length() < 1)
	{
		password = Nanny::getPlayerPassword(clientfd);

		if(fcntl(clientfd, F_GETFD) == -1)
			pthread_exit(&ret);
	}

	Player *player = PlayerManager::findOpenPlayerSlot();

	if(player)
	{
		PlayerManager::resetPlayer(player);
		player->setFileDescriptor(clientfd);

		if(!PlayerManager::isPlayerOnline(name))
		{
			player->setName(name);
		}
		else
		{
			Util::sendToPlayer(clientfd, std::string("Player is already logged in.\n"));
			close(player->getFileDescriptor());
			PlayerManager::resetPlayer(player);
			pthread_exit(&ret);
		}

		if(PlayerManager::playerFileExists(name))
		{
			Util::printServer("Player file found!");
			PlayerManager::readPlayerFile(player, player->getName());

			if(password.compare(player->getPassword()) == 0)
			{
				player->setActive(true);
				Nanny::gameLoop(player);
			}
			else
			{
				Util::sendToPlayer(clientfd, std::string("Incorrect password.\n"));
				close(player->getFileDescriptor());
				PlayerManager::resetPlayer(player);
				pthread_exit(&ret);
			}
		}
		else
		{
			std::vector<int> stats = Nanny::rollStats(clientfd);
			PlayerManager::resetPlayer(player);

			player->setName(name);
			player->setPassword(password);
			player->setFileDescriptor(clientfd);

			player->setStrength(stats[0]);
			player->setPerception(stats[1]);
			player->setEndurance(stats[2]);
			player->setCharisma(stats[3]);
			player->setIntelligence(stats[4]);
			player->setAgility(stats[5]);
			player->setLuck(stats[6]);

			player->setMaxHealth(player->getEndurance() * 10);
			player->setHealth(player->getEndurance() * 10);
			player->setMovement(player->getAgility() * 20);
			player->setMaxMovement(player->getAgility() * 20);
			player->setActive(true);

			std::cout << "Creating new player " << name << " with password " << password << std::endl;
			PlayerManager::writePlayerFile(player);
			Nanny::gameLoop(player);
		}
	}
	else
	{
		Util::sendToPlayer(clientfd, std::string("Maximum number of players reached.\n"));
	}
}

void Nanny::printBanner(int clientfd)
{
	std::stringstream message;
	std::string color = Util::getColorString(31,std::string("INSERT BANNER HERE\n\n"));
	message << color;
	Util::sendToPlayer(clientfd, message.str());
}

std::string Nanny::getPlayerName(int clientfd)
{
	Util::sendToPlayer(clientfd, std::string("Hey there, who are you? "));

	std::vector<std::string> name = Util::getPlayerCommand(clientfd);
	if(name.size() > 0 && name[0].length() > 0)
	{
		return name[0];
	}
	return std::string("");
}

std::string Nanny::getPlayerPassword(int clientfd)
{
	unsigned char hash[SHA_DIGEST_LENGTH];
	std::stringstream ss;
	int x;

	Util::sendToPlayer(clientfd, std::string("What's your password? "));

	std::vector<std::string> password = Util::getPlayerCommand(clientfd);

	if(password.size() > 0 && password[0].length() > 0 && Util::validatePassword(password[0]))
	{
		return Util::hash(password[0]);
	}
	return std::string("");
}

std::vector<int> Nanny::rollStats(int clientfd)
{
	bool accepted = false;
	int strength, perception, endurance, charisma, intelligence, agility, luck;
	std::vector<int> stats;

	struct timeval tp;
	gettimeofday(&tp, NULL);
	unsigned int seed = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	int ret;

	while(!accepted)
	{
		int total_stat_points = 0;

		strength     = Util::rollDice(1, 5);
		perception   = Util::rollDice(1, 5);
		endurance    = Util::rollDice(1, 5);
		charisma     = Util::rollDice(1, 5);
		intelligence = Util::rollDice(1, 5);
		agility      = Util::rollDice(1, 5);
		luck         = Util::rollDice(1, 5);

		if(strength == 0)
			strength = 1;
		if(perception == 0)
			perception = 1;
		if(endurance == 0)
			endurance = 1;
		if(charisma == 0)
			charisma = 1;
		if(intelligence == 0)
			intelligence = 1;
		if(agility == 0)
			agility = 1;
		if(luck == 0)
			luck = 1;

		total_stat_points = strength + perception + endurance + charisma + intelligence + agility + luck;

		while(total_stat_points < 40)
		{
			int roll_stat = rand_r(&seed) % 6;
			switch(roll_stat)
			{
				case 0:
					if(strength < 10)
					{
						strength++;
						total_stat_points++;
					}
					break;
				case 1:
					if(perception < 10)
					{
						perception++;
						total_stat_points++;
					}
					break;
				case 2:
					if(endurance < 10)
					{
						endurance++;
						total_stat_points++;
					}
					break;
				case 3:
					if(charisma < 10)
					{
						charisma++;
						total_stat_points++;
					}
					break;
				case 4:
					if(intelligence < 10)
					{
						intelligence++;
						total_stat_points++;
					}
					break;
				case 5:
					if(agility < 10)
					{
						agility++;
						total_stat_points++;
					}
					break;

				case 6:
					if(luck < 10)
					{
						luck++;
						total_stat_points++;
					}
					break;
				default:
					std::cerr << "Invalid stat roll " << roll_stat << std::endl;
					break;
			}
		}
		std::stringstream message;
		message << "\n####### Rolling stats... #######\n\n\tStrength:\t" << strength << "\n\tPerception:\t" << perception << "\n\tEndurance:\t" << endurance << "\n\tCharisma:\t" << charisma << "\n\tIntelligence:\t" << intelligence << "\n\tAgility\t\t" << agility << "\n\tLuck:\t\t" << luck << "\n\n";
		Util::sendToPlayer(clientfd, message.str());
		Util::sendToPlayer(clientfd, std::string("################################\n\n"));
		Util::sendToPlayer(clientfd, std::string("Are these stats OK? (y/n) "));
		std::vector<std::string> command = Util::getPlayerCommand(clientfd);

		if(command.size() > 0)
		{
			if(command[0] == "y" || command[0] == "Y" || command[0] == "yes" || command[0] == "YES")
			{
				accepted = true;
			}
		}
		else
		{
			Util::printServer("Player disconnected");
			pthread_exit(&ret);
		}
	}
	Util::sendToPlayer(clientfd, std::string("Ok.\n"));
	std::cout << "Final stat roll: " << strength << " " << perception << " " << endurance << " " << charisma << " " << intelligence << " " << agility << " " << luck  << std::endl;

	stats.push_back(strength);
	stats.push_back(perception);
	stats.push_back(endurance);
	stats.push_back(charisma);
	stats.push_back(intelligence);
	stats.push_back(agility);
	stats.push_back(luck);
	return stats;
}

void Nanny::gameLoop(Player *player)
{
	int ret;

	while(player->getActive())
	{
		std::stringstream prompt;
		std::vector<std::string> command;
		//prompt << std::endl << "HP <" << player->getHealth() << "/" << player->getMaxHealth() << "> Movement <" << player->getMovement() << "/" << player->getMaxMovement() << "> ";
		//Util::sendToPlayer(player->getFileDescriptor(), prompt.str());
		Commands::prompt(player);
		command = Util::getPlayerCommand(player->getFileDescriptor());
		Commands::parse(player, command);
	}
}
