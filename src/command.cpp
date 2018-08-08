#include "./command.h"

std::vector<std::string> Commands::command_table = { "chat", "look", "north", "south", "east", "west", "up", "down", "save", "who", "score" };

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
		if(found_commands[0] == "look") { Commands::doLook(player); }
		if(found_commands[0] == "save") { Commands::doSave(player); }
		if(found_commands[0] == "who") { Commands::doWho(player); }
		if(found_commands[0] == "up") { Commands::doUp(player); }
		if(found_commands[0] == "down") { Commands::doDown(player); }
		if(found_commands[0] == "north") { Commands::doNorth(player); }
		if(found_commands[0] == "south") { Commands::doSouth(player); }
		if(found_commands[0] == "east") { Commands::doEast(player); }
		if(found_commands[0] == "west") { Commands::doWest(player); }
		if(found_commands[0] == "score") { Commands::doScore(player); }
	}
}

void Commands::doChat(Player *player, std::string message)
{
	int x;
	std::string name = player->getName();
	std::vector<Player *> players = PlayerManager::getActivePlayers();
	std::stringstream ss;

	ss << std::endl;
	ss << Util::getColorString(FG_GREEN, "[");
	ss << Util::getColorString(FG_GREY, "Chat");
	ss << Util::getColorString(FG_GREEN, "] ");
	ss << Util::getColorString(FG_GREEN, "[");
	ss << Util::getColorString(FG_YELLOW, name);
	ss << Util::getColorString(FG_GREEN, "] ");
	ss << message << std::endl << std::endl;

	for(x = 0; x < players.size(); x++)
	{
		Util::sendToPlayer(players[x]->getFileDescriptor(), ss.str());
	}
}

void Commands::doSave(Player *player)
{
	std::string message = Util::getColorString(FG_YELLOW, std::string("Saving...\n"));
	std::string confirm = Util::getColorString(FG_GREY, std::string("Save successful.\n"));
	Util::sendToPlayer(player, message);
	PlayerManager::writePlayerFile(player);
	Util::sendToPlayer(player, confirm);
}

void Commands::doLook(Player *player)
{
	uint32_t room_number = player->getRoom();
	Room *room = AreaManager::findRoom(room_number);

	if(!room)
	{
		Util::printError("doLook: invalid room number");
		return;
	}
	std::stringstream title;
	title << "\n=" << Util::getColorString(FG_BLUE, room->getTitle()) << "=" << std::endl;
	std::string desc = Util::getColorString(FG_GREEN, room->getDescription()) + "\n";

	Util::sendToPlayer(player, title.str());
	Util::sendToPlayer(player, desc);
	Util::sendToPlayer(player, Util::getColorString(FG_YELLOW, std::string("Exits:\n")));
	if(!room->exit_north && !room->exit_south && !room->exit_east && !room->exit_west && !room->exit_up && !room->exit_down)
	{
		Util::sendToPlayer(player, std::string("None.\n\n"));
	}
	if(room->exit_north)
	{
		Util::sendToPlayer(player, std::string("North\n"));
	}
	if(room->exit_south)
	{
		Util::sendToPlayer(player, std::string("South\n"));
	}
	if(room->exit_east)
	{
		Util::sendToPlayer(player, std::string("East\n"));
	}
	if(room->exit_west)
	{
		Util::sendToPlayer(player, std::string("West\n"));
	}
	if(room->exit_up)
	{
		Util::sendToPlayer(player, std::string("Up\n"));
	}
	if(room->exit_down)
	{
		Util::sendToPlayer(player, std::string("Down\n"));
	}
}

void Commands::doWho(Player *player)
{
	std::stringstream message;
	std::vector<Player *> active_players = PlayerManager::getActivePlayers();
	int x;

	message << std::endl;
	message << Util::getColorString(FG_CYAN, std::string(" ----------------------------------------------------------------------------- ")) << std::endl;
	message << Util::getColorString(FG_CYAN, std::string("|                             PLAYERS ONLINE                                  |")) << std::endl;
	message << Util::getColorString(FG_CYAN, std::string(" ----------------------------------------------------------------------------- ")) << std::endl;

	for(x = 0; x < active_players.size(); x++)
	{
		message << "   " << active_players[x]->getName() << std:: endl;
	}

	message << std::endl << active_players.size() << " players online." << std::endl;
	message << std::endl;

	Util::sendToPlayer(player, message.str());
}

void Commands::doScore(Player *player)
{
	std::stringstream message;
	std::string name = player->getName();
	std::string strength = std::to_string(player->getStrength());
	std::string perception = std::to_string(player->getPerception());
	std::string endurance = std::to_string(player->getEndurance());
	std::string charisma = std::to_string(player->getCharisma());
	std::string intelligence = std::to_string(player->getIntelligence());
	std::string agility = std::to_string(player->getAgility());
	std::string luck = std::to_string(player->getLuck());

	message << "Name:\t\t" << name << std::endl;
	message << "Strength:\t" << strength << std::endl;
	message << "Perception:\t" << perception << std::endl;
	message << "Endurance:\t" << endurance << std::endl;
	message << "Charisma:\t" << charisma << std::endl;
	message << "Intelligence:\t" << intelligence << std::endl;
	message << "Agility:\t" << agility << std::endl;
	message << "Luck:\t\t" << luck << std::endl;
	//std:: string color = Util::getColorString(FG_CYAN, message.str());

	Util::sendToPlayer(player, message.str());
}

void Commands::doUp(Player *player)
{
	Room *room = AreaManager::findRoom(player->getRoom());
	if(!room->exit_up)
	{
		std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
		Util::sendToPlayer(player, error);
		return;
	}

	player->moveToRoom(room->room_up, EXIT_UP);
	Commands::doLook(player);
}

void Commands::doDown(Player *player)
{
	Room *room = AreaManager::findRoom(player->getRoom());
	if(!room->exit_down)
	{
		std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
		Util::sendToPlayer(player, error);
		return;
	}

	player->moveToRoom(room->room_down, EXIT_DOWN);
	Commands::doLook(player);
}

void Commands::doNorth(Player *player)
{
	Room *room = AreaManager::findRoom(player->getRoom());
	if(!room->exit_north)
	{
		std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
		Util::sendToPlayer(player, error);
		return;
	}

	player->moveToRoom(room->room_north, EXIT_NORTH);
	Commands::doLook(player);
}

void Commands::doSouth(Player *player)
{
	Room *room = AreaManager::findRoom(player->getRoom());
	if(!room->exit_south)
	{
		std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
		Util::sendToPlayer(player, error);
		return;
	}

	player->moveToRoom(room->room_south, EXIT_SOUTH);
	Commands::doLook(player);
}

void Commands::doEast(Player *player)
{
	Room *room = AreaManager::findRoom(player->getRoom());
	if(!room->exit_east)
	{
		std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
		Util::sendToPlayer(player, error);
		return;
	}

	player->moveToRoom(room->room_east, EXIT_EAST);
	Commands::doLook(player);
}

void Commands::doWest(Player *player)
{
	Room *room = AreaManager::findRoom(player->getRoom());
	if(!room->exit_west)
	{
		std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
		Util::sendToPlayer(player, error);
		return;
	}

	player->moveToRoom(room->room_west, EXIT_WEST);
	Commands::doLook(player);
}
