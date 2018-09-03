#pragma once
#include "./game.h"
#include "./playermanager.h"
#include "./areamanager.h"
#include "./item.h"
#include "./itemmanager.h"

class Commands
{
public:
	static std::vector<std::string> command_table; 
	static void parse(Player *player, std::vector<std::string> commands);
	static void prompt(Player *player);
	static void doChat(Player *player, std::string message);
	static void doSave(Player *player);
	static void doLook(Player *player);
	static void doWho(Player *player);
	static void doScore(Player *player);
	static void doUp(Player *player);
	static void doDown(Player *player);
	static void doNorth(Player *player);
	static void doSouth(Player *player);
	static void doEast(Player *player);
	static void doWest(Player *player);
	static void doMove(Player *player, Exit direction);
	static void doAutoDig(Player *player);
	static void doRStat(Player *player);
	static void doGoto(Player *player, std::vector<std::string> commands);
	static void doCreateObject(Player *player, std::vector<std::string> commands);
	static void doSaveObject(Player *player);
	static void doListObjects(Player *player);
	static void doQuit(Player *player);
	static void doObjectEdit(Player *player,  std::vector<std::string> commands);
	static void doObjectDelete(Player *player, std::vector<std::string> commands);
};
