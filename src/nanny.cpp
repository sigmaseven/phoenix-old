#include "./nanny.h"
#include "./util.h"
#include "./playermanager.h"
#include "./command.h"

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
	return NULL;
}

void Nanny::newPlayerMenu(int clientfd)
{
	std::string name = "";
	std::string password = "";
	int ret;

	Player *player = PlayerManager::findOpenPlayerSlot();
	player->setFileDescriptor(clientfd);

	Nanny::printBanner(clientfd);

	while(name.length() < 1)
	{
		name = Nanny::getPlayerName(player);
	}

	player->setName(name);

	while(password.length() < 1)
	{
		password = Nanny::getPlayerPassword(player);
	}

	player->setPassword(password);

	if(player)
	{
		PlayerManager::resetPlayer(player);
		player->setFileDescriptor(clientfd);

		if(name.size() > 0 && !PlayerManager::isPlayerOnline(name))
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

			if(player->setStrength(stats[0]) != SUCCESS)
			{
				Util::printError("Error setting player strength.");
			}

			if(player->setPerception(stats[1]))
			{
				Util::printError("Error setting player perception.");
			}

			if(player->setEndurance(stats[2]) != SUCCESS)
			{
				Util::printError("Error setting player endurance.");
			}

			if(player->setCharisma(stats[3]) != SUCCESS)
			{
				Util::printError("Error setting player charisma.");
			}

			if(player->setIntelligence(stats[4]) != SUCCESS)
			{
				Util::printError("Error setting player intelligence.");
			}

			if(player->setAgility(stats[5]) != SUCCESS)
			{
				Util::printError("Error setting player agility.");
			}

			if(player->setLuck(stats[6]) != SUCCESS)
			{
				Util::printError("Error setting player luck.");
			}

			if(player->setMaxHealth(player->getEndurance() * 10) != SUCCESS)
			{
				Util::printError("Error setting max player health.");
			}

			if(player->setHealth(player->getEndurance() * 10) != SUCCESS)
			{
				Util::printError("Error setting player health.");
			}

			if(player->setMovement(player->getAgility() * 20) != SUCCESS)
			{
				Util::printError("Error setting player movement.");
			}

			if(player->setMaxMovement(player->getAgility() * 20) != SUCCESS)
			{
				Util::printError("Error setting player max movement.");
			}

			if(player->setRoom(1) != SUCCESS)
			{
				Util::printError("Error setting player room.");
			}
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
	std::string banner_file;
	banner_file = Util::readFromFile("./banner.txt");
	std::string color = Util::getColorString(FG_YELLOW, banner_file);
	message << color;
	Util::sendToPlayer(clientfd, message.str());
}

std::string Nanny::getPlayerName(Player *player)
{
	int clientfd = player->getFileDescriptor();
	std::string message = Util::getColorString(FG_CYAN, "Hey there, who are you? ");
	Util::sendToPlayer(clientfd, message);

	std::vector<std::string> name = Util::getPlayerCommand(clientfd);

	if(name.size() > 0 && name[0].length() > 0)
	{
		return name[0];
	}
	return std::string("");
}

std::string Nanny::getPlayerPassword(Player *player)
{
	std::stringstream ss;
	int clientfd = player->getFileDescriptor();
	std::string message = Util::getColorString(FG_CYAN, "What's your password? ");
	Util::sendToPlayer(clientfd, message);

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
		message << "################################\n\n";
		std::string color = Util::getColorString(FG_GREY, message.str());
		std::string confirm = Util::getColorString(FG_CYAN, std::string("Are these stats OK? (y/N) "));
		Util::sendToPlayer(clientfd, message.str());
		Util::sendToPlayer(clientfd, confirm);
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
