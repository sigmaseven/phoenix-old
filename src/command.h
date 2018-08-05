#pragma once
#include "game.h"
#include "playermanager.h"

class Commands
{
public:
	static std::vector<std::string> command_table; 
	static void parse(Player *player, std::vector<std::string> commands);
	static void prompt(Player *player);
	static void doChat(Player *player, std::string message);
};
