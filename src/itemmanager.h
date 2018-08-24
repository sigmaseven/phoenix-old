#pragma once
#include "./game.h"
#include "./item.h"

class ItemManager
{
	static std::vector<Item *> items;
public:
	static void init();

	static Item *findItem(uint32_t id);
	static Item *findAvailableItem();
};
