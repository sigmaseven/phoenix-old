#pragma once
#include "./game.h"

enum ItemType
{
	ITEM_JUNK,
	ITEM_WEAPON,
	ITEM_ARMOR
};

class Item
{
	uint32_t id;
	bool active;
	ItemType type;
	std::string short_description;
	std::string long_description;

public:
	uint32_t getID();
	bool getActive();
	std::string getShortDescription();
	std::string getLongDescription();

	bool setID(uint32_t new_id);
	bool setActive(bool option);
	void setShortDescription(std::string short_desc);
	void setLongDescription(std::string long_desc);
};
