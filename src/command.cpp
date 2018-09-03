#include "./command.h"

std::vector<std::string> Commands::command_table = { "chat", "look", "north", "south", "east",
						     "west", "up", "down", "save", "who", "score",
						     "autodig", "rstat", "goto", "ocreate", "oedit",
						     "osave", "olist", "quit", "odelete" };

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
	uint32_t x;
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
		if(found_commands[0] == "up") { Commands::doMove(player, EXIT_UP); }
		if(found_commands[0] == "down") { Commands::doMove(player, EXIT_DOWN); }
		if(found_commands[0] == "north") { Commands::doMove(player, EXIT_NORTH); }
		if(found_commands[0] == "south") { Commands::doMove(player, EXIT_SOUTH); }
		if(found_commands[0] == "east") { Commands::doMove(player, EXIT_EAST); }
		if(found_commands[0] == "west") { Commands::doMove(player, EXIT_WEST); }
		if(found_commands[0] == "score") { Commands::doScore(player); }
		if(found_commands[0] == "autodig") { Commands::doAutoDig(player); }
		if(found_commands[0] == "rstat") { Commands::doRStat(player); }
		if(found_commands[0] == "goto") { Commands::doGoto(player, commands); }
		if(found_commands[0] == "ocreate") { Commands::doCreateObject(player, commands); }
		if(found_commands[0] == "osave") { Commands::doSaveObject(player); }
		if(found_commands[0] == "olist") { Commands::doListObjects(player); }
		if(found_commands[0] == "quit") { Commands::doQuit(player); }
		if(found_commands[0] == "oedit") { Commands::doObjectEdit(player, commands); }
		if(found_commands[0] == "odelete") { Commands::doObjectDelete(player, commands); }
	}
}

void Commands::doChat(Player *player, std::string message)
{
	uint32_t x;
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
	title << "\n=" << Util::getColorString(FG_BLUE, room->getTitle()) << "[" << room->getID() << "]=" << std::endl;
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
	uint32_t x;

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

	Util::sendToPlayer(player, message.str());
}

void Commands::doMove(Player *player, Exit direction)
{
	Room *room = AreaManager::findRoom(player->getRoom());
	Room *new_room;

	switch(direction)
	{
		default:
			break;

		case EXIT_UP:
			if(!room->exit_up && !player->getAutoDig())
			{
				std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
				Util::sendToPlayer(player, error);
				return;
			}
			else if(!room->exit_up && player->getAutoDig())
			{
				new_room = AreaManager::findAvailableRoom();
				AreaManager::createExit(room->getID(), new_room->getID(), EXIT_UP);
				player->moveToRoom(room->room_up, EXIT_UP);
				Commands::doLook(player);
			}
			else
			{
				player->moveToRoom(room->room_up, EXIT_UP);
				Commands::doLook(player);
			}
			break;

		case EXIT_DOWN:
			if(!room->exit_down && !player->getAutoDig())
			{
				std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
				Util::sendToPlayer(player, error);
				return;
			}
			else if(!room->exit_down && player->getAutoDig())
			{
				new_room = AreaManager::findAvailableRoom();
				AreaManager::createExit(room->getID(), new_room->getID(), EXIT_DOWN);
				player->moveToRoom(room->room_down, EXIT_DOWN);
				Commands::doLook(player);
			}
			else
			{
				player->moveToRoom(room->room_down, EXIT_DOWN);
				Commands::doLook(player);
			}
			break;

		case EXIT_NORTH:
			if(!room->exit_north && !player->getAutoDig())
			{
				std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
				Util::sendToPlayer(player, error);
				return;
			}
			else if(!room->exit_north && player->getAutoDig())
			{
				new_room = AreaManager::findAvailableRoom();
				AreaManager::createExit(room->getID(), new_room->getID(), EXIT_NORTH);
				player->moveToRoom(room->room_north, EXIT_NORTH);
				Commands::doLook(player);
			}
			else
			{
				player->moveToRoom(room->room_north, EXIT_NORTH);
				Commands::doLook(player);
			}
			break;

		case EXIT_SOUTH:
			if(!room->exit_south && !player->getAutoDig())
			{
				std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
				Util::sendToPlayer(player, error);
				return;
			}
			else if(!room->exit_south && player->getAutoDig())
			{
				new_room = AreaManager::findAvailableRoom();
				AreaManager::createExit(room->getID(), new_room->getID(), EXIT_SOUTH);
				player->moveToRoom(room->room_south, EXIT_SOUTH);
				Commands::doLook(player);
			}
			else
			{
				player->moveToRoom(room->room_south, EXIT_SOUTH);
				Commands::doLook(player);
			}
			break;

		case EXIT_EAST:
			Util::printServer("Exiting east");
			if(!room->exit_east && !player->getAutoDig())
			{
				std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
				Util::sendToPlayer(player, error);
				return;
			}
			else if(!room->exit_east && player->getAutoDig())
			{
				new_room = AreaManager::findAvailableRoom();
				AreaManager::createExit(room->getID(), new_room->getID(), EXIT_EAST);
				player->moveToRoom(room->room_east, EXIT_EAST);
				Commands::doLook(player);
			}
			else
			{
				player->moveToRoom(room->room_east, EXIT_EAST);
				Commands::doLook(player);
			}
			break;

		case EXIT_WEST:
			Util::printServer("Exiting west");
			if(!room->exit_west && !player->getAutoDig())
			{
				std::string error = Util::getColorString(FG_RED, "You can't go that way.\n");
				Util::sendToPlayer(player, error);
				return;
			}
			else if(!room->exit_west && player->getAutoDig())
			{
				new_room = AreaManager::findAvailableRoom();
				AreaManager::createExit(room->getID(), new_room->getID(), EXIT_WEST);
				player->moveToRoom(room->room_west, EXIT_WEST);
				Commands::doLook(player);
			}
			else
			{
				player->moveToRoom(room->room_west, EXIT_WEST);
				Commands::doLook(player);
			}
			break;
	}
}

void Commands::doAutoDig(Player *player)
{
	if(!player->getAutoDig())
	{
		std::string message = Util::getColorString(FG_YELLOW, "Autodig enabled.\n");
		Util::sendToPlayer(player, message);
		player->setAutoDig(true);
	}
	else
	{
		std::string message = Util::getColorString(FG_YELLOW, "Autodig disabled.\n");
		Util::sendToPlayer(player, message);
		player->setAutoDig(false);
	}
}

void Commands::doRStat(Player *player)
{
	std::stringstream message;
	Room *room = AreaManager::findRoom(player->getRoom());

	message << std::endl;
	message << "ID:\t\t" << room->getID() << std::endl;
	message << "Title:\t" << room->getTitle() << std::endl;
	message << "Description:\t" << room->getDescription() << std::endl;
	message << "Exit North:\t" << room->exit_north << " - " << room->room_north << std::endl;
	message << "Exit South:\t" << room->exit_south << " - " << room->room_south << std::endl;
	message << "Exit East:\t" << room->exit_east << " - " << room->room_east << std::endl;
	message << "Exit West:\t" << room->exit_west << " - " << room->room_west << std::endl;
	message << "Exit Up:\t\t" << room->exit_up << " - " << room->room_up << std::endl;
	message << "Exit Down:\t" << room->exit_down << " - " << room->room_down << std::endl;

	Util::sendToPlayer(player, message.str());
}

void Commands::doGoto(Player *player, std::vector<std::string> commands)
{
	int room = std::atoi(commands[1].c_str());
	player->moveToRoom(room, EXIT_TELEPORT);
	Commands::doLook(player);
}

void Commands::doCreateObject(Player *player, std::vector<std::string> commands)
{
	uint32_t x;
	std::stringstream short_description;
	std::stringstream usage;
	std::stringstream tmp;
	std::string message;
	Item *item;

	usage << "Usage: ocreate [short description]" << std::endl;
	std::cout << "command size: " << commands.size() << std::endl;
	if(commands.size() < 2)
	{
		Util::sendToPlayer(player, usage.str());
		return;
	}

	for(x = 1; x < commands.size(); x++)
	{
		short_description << commands[x];

		if(x < commands.size() -1)
		{
			short_description << " ";
		}
	}

	item = ItemManager::findAvailableItemIndex();

	if(!item)
	{
		Util::printError("doCreateObject: Error allocating item!");
		return;
	}

	item->setShortDescription(short_description.str());
	item->setActive(true);

	tmp << short_description.str() << " created with item ID " << item->getID() << std::endl;
	message = Util::getColorString(FG_YELLOW, tmp.str());
	Util::sendToPlayer(player, message);
	return;
}

void Commands::doSaveObject(Player *player)
{
	ItemManager::writeToFile();
}

void Commands::doListObjects(Player *player)
{
	ItemManager::listItemIndex(player);
}

void Commands::doQuit(Player *player)
{
	int ret;

	close(player->getFileDescriptor());
	PlayerManager::resetPlayer(player);
	pthread_exit(&ret);
}

void Commands::doObjectEdit(Player *player, std::vector<std::string> commands)
{
	ItemManager::editItemIndex(player, commands);
}

void Commands::doObjectDelete(Player *player, std::vector<std::string> commands)
{

}
