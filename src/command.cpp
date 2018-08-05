#include "command.h"

std::vector<std::string> Commands::command_table = { "chat", "look", "north", "south", "east", "west" };

void Commands::prompt(Player *player)
{
	std::stringstream ss;
	ss << Util::getColorString(FG_BLUE, "[ ");
	ss << Util::getColorString(FG_GREY, "HP ");
	float health_ratio = player->getHealth() / player->getMaxHealth();
	float movement_ratio = player->getMovement() / player->getMaxMovement();
	std::stringstream health;
	std::stringstream movement;

	health << "<" << player->getHealth() << "/" << player->getMaxHealth() << "> ";
	movement << "<" << player->getMovement() << "/" << player->getMaxMovement() << "> ";

	if(health_ratio > 0.66f)
	{
		ss << Util::getColorString(FG_GREEN, health.str());
	}
	else if(health_ratio > 0.33f)
	{
		ss << Util::getColorString(FG_YELLOW, health.str());
	}
	else
	{
		ss << Util::getColorString(FG_RED, health.str());
	}

	ss << Util::getColorString(FG_GREY, "Movement ");
	if(movement_ratio > 0.66f)
	{
		ss << Util::getColorString(FG_GREEN, movement.str());
	}
	else if(movement_ratio > 0.33f)
	{
		ss << Util::getColorString(FG_YELLOW, movement.str());
	}
	else
	{
		ss << Util::getColorString(FG_RED, movement.str());
	}

	ss << Util::getColorString(FG_BLUE, "] ");
	Util::sendToPlayer(player->getFileDescriptor(), ss.str());
}

void Commands::parse(Player *player, std::vector<std::string> commands)
{
	int x;
	int count = 0;
	std::vector<std::string> found_commands;

	if(commands.size() <= 0)
	{
		return;
	}
	for(x = 0; x < Commands::command_table.size(); x++)
	{
		if(Commands::command_table[x].compare(0, commands[0].size(), commands[0]) == 0)
		{
			count++;
			found_commands.push_back(Commands::command_table[x]);
		}
	}

	if(found_commands.size() <= 0)
	{
		Util::sendToPlayer(player->getFileDescriptor(), std::string("\nHuh?\n"));
		return;
	}
	else
	{
		if(found_commands[0] == "chat")
		{
			std::stringstream message;
			for(x = 1; x < commands.size(); x++)
			{
				message << commands[x];
				if(x < commands.size() -1)
					message << " ";
			}
			Commands::doChat(player, message.str());
		}
	}
}

void Commands::doChat(Player *player, std::string message)
{
	int x;
	std::string name = player->getName();
	std::vector<Player *> players = PlayerManager::getActivePlayers();
	std::stringstream ss;

	ss << std::endl << std::endl;
	ss << Util::getColorString(FG_GREEN, "[");
	ss << Util::getColorString(FG_GREY, "Chat");
	ss << Util::getColorString(FG_GREEN, "] ");
	ss << Util::getColorString(FG_YELLOW, name) << " ";
	ss << message << std::endl;

	for(x = 0; x < players.size(); x++)
	{
		Util::sendToPlayer(players[x]->getFileDescriptor(), ss.str());
	}
}
