#pragma once
#include "./game.h"
#include "./item.h"
#include "./util.h"

class ItemManager
{
	static std::vector<Item *> items;
	static std::vector<Item *> item_index;

public:
	static void init();

	static Item *findItemIndex(uint32_t id);
	static Item *findAvailableItemIndex();
	static std::vector<Item *> findActiveItemsIndex();
	static void loadFromFile(std::string filename);
	static void writeToFile();
	static void listItemIndex(Player *player);
	static void editItemIndex(Player *player, std::vector<std::string> commands);
	static void resetItemIndex(Item *item);
	static void deleteItemIndex(Player *player, uint32_t index);
	static ItemType getItemType(std::string type);
	static std::string getItemTypeString(ItemType type);
};
