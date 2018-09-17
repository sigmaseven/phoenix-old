#include "./itemmanager.h"

std::vector<Item *> ItemManager::items;
std::vector<Item *> ItemManager::item_index;

void ItemManager::init()
{
	uint32_t x;

	for(x = 0; x < MAX_ITEMS; x++)
	{
		Item *item = new Item();
		item->setID(x);
		item->setActive(false);
		item_index.push_back(item);
	}

	loadFromFile("items/items.json");
}

Item *ItemManager::findAvailableItemIndex()
{
	uint32_t x;

	for(x = 0; x < MAX_ITEMS; x++)
	{
		Item *item = item_index[x];

		if(!item->getActive())
		{
			return item;
		}
	}

	return NULL;
}

std::vector<Item *> ItemManager::findActiveItemsIndex()
{
	uint32_t x;
	std::vector<Item *> active_items;

	for(x = 0; x < active_items.size(); x++)
	{
		if(item_index[x]->getActive())
		{
			active_items.push_back(item_index[x]);
		}
	}

	return active_items;
}

Item *ItemManager::findItemIndex(uint32_t id)
{
	if(id > MAX_ITEMS)
	{
		return NULL;
	}

	return item_index[id];
}

void ItemManager::writeToFile()
{
	uint32_t x;
	nlohmann::json j;

	j["items"] = nlohmann::json::array();

	if(!Util::checkDirectory("items"))
	{
		Util::printError("Unable to locate or create the items directory.");
		return;
	}

	for(x = 0; x < MAX_ITEMS; x++)
	{
		Item *item;
		nlohmann::json object = nlohmann::json::object();

		item = ItemManager::findItemIndex(x);

		if(!item)
		{
			Util::printError("Unable to locate item.");
			return;
		}

		if(item->getActive())
		{
			std::string type = ItemManager::getItemTypeString(item->getType());

			object["id"]         = item->getID();
			object["type"]       = type;
			object["level"]      = item->getLevel();
			object["damage"]     = item->getDamage();
			object["min_damage"] = item->getMinimumDamage();
			object["short"]      = item->getShortDescription();
			object["long"]       = item->getLongDescription();

			j["items"].push_back(object);
		}
	}

	Util::writeToFile("items/items.json", j.dump());

	return;
}

void ItemManager::loadFromFile(std::string filename)
{
	std::string content;
	nlohmann::json j;
	nlohmann::json::iterator i;

	content = Util::readFromFile(filename.c_str());

	if(content.length() > 0)
	{
		j = nlohmann::json::parse(content.c_str());

		for(i = j["items"].begin(); i != j["items"].end(); i++)
		{
			nlohmann::json json_item = *i;
			uint32_t id = json_item["id"];

			Item *item = ItemManager::findItemIndex(id);

			if(!json_item["level"].is_null())
			{
				item->setLevel(json_item["level"]);
			}

			if(!json_item["type"].is_null())
			{
				item->setType(ItemManager::getItemType(json_item["type"]));
			}

			if(!json_item["damage"].is_null())
			{
				item->setDamage(json_item["damage"]);
			}

			if(!json_item["min_damage"].is_null())
			{
				item->setMinimumDamage(json_item["min_damage"]);
			}

			item->setShortDescription(json_item["short"]);
			item->setLongDescription(json_item["long"]);
			item->setActive(true);
		}
	}
}

void ItemManager::listItemIndex(Player *player)
{
	uint32_t x;

	for(x = 0; x < MAX_ITEMS; x++)
	{
		Item *item = ItemManager::findItemIndex(x);

		if(item->getActive())
		{
			std::stringstream line;
			line << "[" << item->getID() << "] " << item->getShortDescription() << std::endl;
			Util::sendToPlayer(player, line.str());
		}
	}
}

void ItemManager::editItemIndex(Player *player, std::vector<std::string> commands)
{
	uint32_t id;
	Item *item;

	try
	{
		id = std::stoi(commands[1]);
	}
	catch(const std::out_of_range &exception)
	{
		std::stringstream error;
		error << "editItem: invalid ID - " << exception.what() << std::endl;
		Util::printError(error.str());
		return;
	}

	item = ItemManager::findItemIndex(id);

	if(!item)
	{
		Util::printError("editItem: couldn't find item id");
		return;
	}

	if(Util::partialMatch("level", commands[2]))
	{
		uint32_t level;

		try
		{
			level = std::stoi(commands[3]);
		}
		catch(const std::out_of_range &exception)
		{
			std::stringstream error;
			error << "editItem: invalid level - " << exception.what() << std::endl;
			Util::printError(error.str());
			return;
		}

		item->setLevel(level);
	}

	if(Util::partialMatch("short", commands[2]))
	{
		uint32_t x;
		std::stringstream short_desc;

		for(x = 3; x < commands.size(); x++)
		{
			short_desc << commands[x];

			if(x < commands.size() -1)
			{
				short_desc << " ";
			}
		}

		item->setShortDescription(short_desc.str());
	}

	if(Util::partialMatch("damage", commands[2]))
	{
		uint32_t damage;

		damage = Util::stringToInteger(commands[3]);

		if(damage > 0)
		{
			item->setDamage(damage);
		}
		else
		{
			return;
		}
	}

	if(Util::partialMatch("min_damage", commands[2]))
	{
		uint32_t min_damage;

		min_damage = Util::stringToInteger(commands[3]);

		if(min_damage > 0)
		{
			item->setMinimumDamage(min_damage);
		}
		else
		{
			return;
		}
	}

	if(Util::partialMatch("ammo", commands[2]))
	{
		uint32_t ammo;

		ammo = Util::stringToInteger(commands[3]);

		if(ammo > 0)
		{
			item->setAmmoID(ammo);
		}
		else
		{
			return;
		}
	}

	if(Util::partialMatch("type", commands[2]))
	{
		ItemType item_type = ItemManager::getItemType(commands[3]);

		switch(item_type)
		{

			case ITEM_NULL:
				item->setType(ITEM_NULL);
				break;

			case ITEM_JUNK:
				item->setType(ITEM_JUNK);
				break;

			case ITEM_MELEE:
				item->setType(ITEM_MELEE);
				break;

			case ITEM_UNARMED:
				item->setType(ITEM_UNARMED);
				break;

			case ITEM_PISTOL:
				item->setType(ITEM_PISTOL);
				break;

			case ITEM_RIFLE:
				item->setType(ITEM_RIFLE);
				break;

			case ITEM_SMG:
				item->setType(ITEM_SMG);
				break;

			case ITEM_SHOTGUN:
				item->setType(ITEM_SHOTGUN);
				break;

			case ITEM_GRENADE:
				item->setType(ITEM_GRENADE);
				break;

			case ITEM_SNIPER:
				item->setType(ITEM_SNIPER);
				break;

			case ITEM_LASER_PISTOL:
				item->setType(ITEM_LASER_PISTOL);
				break;

			case ITEM_LASER_RIFLE:
				item->setType(ITEM_LASER_RIFLE);
				break;

			case ITEM_GAUSS_PISTOL:
				item->setType(ITEM_GAUSS_PISTOL);
				break;

			case ITEM_GAUSS_RIFLE:
				item->setType(ITEM_GAUSS_RIFLE);
				break;

			case ITEM_HEAVY_WEAPON:
				item->setType(ITEM_HEAVY_WEAPON);
				break;

			case ITEM_ARMOR:
				item->setType(ITEM_ARMOR);
				break;

			case ITEM_CLOTHING:
				item->setType(ITEM_CLOTHING);
				break;

			case ITEM_FOOD:
				item->setType(ITEM_FOOD);
				break;

			case ITEM_WATER:
				item->setType(ITEM_WATER);
				break;

			case ITEM_ALCOHOL:
				item->setType(ITEM_ALCOHOL);
				break;

			case ITEM_MEDKIT:
				item->setType(ITEM_MEDKIT);
				break;

			case ITEM_STIMPACK:
				item->setType(ITEM_STIMPACK);
				break;

			case ITEM_MEDICINE:
				item->setType(ITEM_MEDICINE);
				break;

			case ITEM_AMMO_223:
				item->setType(ITEM_AMMO_223);
				break;

			case ITEM_AMMO_10MM:
				item->setType(ITEM_AMMO_10MM);
				break;

			case ITEM_AMMO_45:
				item->setType(ITEM_AMMO_45);
				break;

			case ITEM_AMMO_GAUSS:
				item->setType(ITEM_AMMO_GAUSS);
				break;

			case ITEM_AMMO_LASER:
				item->setType(ITEM_AMMO_LASER);
				break;
		}
	}
}

void ItemManager::resetItemIndex(Item *item)
{
	item->setLevel(1);
	item->setShortDescription("");
	item->setLongDescription("");
	item->setDamage(1);
	item->setMinimumDamage(1);
	item->setType(ITEM_JUNK);
	item->setActive(false);
}

void ItemManager::deleteItemIndex(Player *player, uint32_t index)
{
	Item *item = ItemManager::findItemIndex(index);

	if(!item)
	{
		Util::printError("deleteItem: Error finding item index");
		return;
	}

	ItemManager::resetItemIndex(item);
	return;
}

ItemType ItemManager::getItemType(std::string type)
{
//	std::cout << "comparing partial string: " << type;

	if(Util::partialMatch("melee", type))
	{
		return ITEM_MELEE;
	}

	if(Util::partialMatch("unarmed", type))
	{
		return ITEM_UNARMED;
	}

	if(Util::partialMatch("pistol", type))
	{
		return ITEM_PISTOL;
	}

	if(Util::partialMatch("rifle", type))
	{
		return ITEM_RIFLE;
	}

	if(Util::partialMatch("smg", type))
	{
		return ITEM_SMG;
	}

	if(Util::partialMatch("laser_pistol", type))
	{
		return ITEM_LASER_PISTOL;
	}

	if(Util::partialMatch("laser_rifle", type))
	{
		return ITEM_LASER_RIFLE;
	}

	if(Util::partialMatch("gauss_pistol", type))
	{
		return ITEM_GAUSS_PISTOL;
	}

	if(Util::partialMatch("gauss_rifle", type))
	{
		return ITEM_GAUSS_RIFLE;
	}

	if(Util::partialMatch("heavy_weapon", type))
	{
		return ITEM_HEAVY_WEAPON;
	}

	if(Util::partialMatch("armor", type))
	{
		return ITEM_ARMOR;
	}

	if(Util::partialMatch("food", type))
	{
		return ITEM_FOOD;
	}

	if(Util::partialMatch("water", type))
	{
		return ITEM_WATER;
	}

	if(Util::partialMatch("alcohol", type))
	{
		return ITEM_ALCOHOL;
	}

	if(Util::partialMatch("medkit", type))
	{
		return ITEM_MEDKIT;
	}

	if(Util::partialMatch("stimpack", type))
	{
		return ITEM_STIMPACK;
	}

	if(Util::partialMatch("medicine", type))
	{
		return ITEM_MEDICINE;
	}

	if(Util::partialMatch("grenade", type))
	{
		return ITEM_GRENADE;
	}

	if(Util::partialMatch("shotgun", type))
	{
		return ITEM_SHOTGUN;
	}

	if(Util::partialMatch("ammo_223", type))
	{
		return ITEM_AMMO_223;
	}

	if(Util::partialMatch("ammo_45", type))
	{
		return ITEM_AMMO_45;
	}

	if(Util::partialMatch("ammo_laser", type))
	{
		return ITEM_AMMO_LASER;
	}

	if(Util::partialMatch("ammo_gauss", type))
	{
		return ITEM_AMMO_GAUSS;
	}

	if(Util::partialMatch("clothing", type))
	{
		return ITEM_CLOTHING;
	}

	return ITEM_NULL;
}

std::string ItemManager::getItemTypeString(ItemType type)
{
	std::string item_type;

	switch(type)
	{

		case ITEM_NULL:
			item_type = "null";
			break;

		case ITEM_UNARMED:
			item_type = "unarmed";
			break;

		case ITEM_MELEE:
			item_type = "melee";
			break;

		case ITEM_PISTOL:
			item_type = "pistol";
			break;

		case ITEM_RIFLE:
			item_type = "rifle";
			break;

		case ITEM_SMG:
			item_type = "smg";
			break;

		case ITEM_SNIPER:
			item_type = "sniper";
			break;

		case ITEM_SHOTGUN:
			item_type = "shotgun";
			break;

		case ITEM_GRENADE:
			item_type = "grenade";
			break;

		case ITEM_LASER_PISTOL:
			item_type = "laser_pistol";
			break;

		case ITEM_LASER_RIFLE:
			item_type = "laser_rifle";
			break;

		case ITEM_GAUSS_PISTOL:
			item_type = "gauss_pistol";
			break;

		case ITEM_GAUSS_RIFLE:
			item_type = "gauss_rifle";
			break;

		case ITEM_HEAVY_WEAPON:
			item_type = "heavy_weapon";
			break;

		case ITEM_ARMOR:
			item_type = "armor";
			break;

		case ITEM_FOOD:
			item_type = "food";
			break;

		case ITEM_WATER:
			item_type = "water";
			break;

		case ITEM_ALCOHOL:
			item_type = "alcohol";
			break;

		case ITEM_MEDKIT:
			item_type = "medkit";
			break;

		case ITEM_STIMPACK:
			item_type = "stimpack";
			break;

		case ITEM_MEDICINE:
			item_type = "medicine";
			break;

		case ITEM_JUNK:
			item_type = "junk";
			break;

		case ITEM_CLOTHING:
			item_type = "clothing";
			break;

		case ITEM_AMMO_223:
			item_type = "ammo_223";
			break;

		case ITEM_AMMO_45:
			item_type = "ammo_45";
			break;

		case ITEM_AMMO_10MM:
			item_type = "ammo_10mm";
			break;

		case ITEM_AMMO_LASER:
			item_type = "ammo_laser";
			break;

		case ITEM_AMMO_GAUSS:
			item_type = "ammo_gauss";
			break;
	}

	return item_type;
}

ErrorCode ItemManager::copyItemIndex(uint32_t source)
{
	Item *original = ItemManager::findItemIndex(source);
	Item *copy = ItemManager::findAvailableItemIndex();

	if(!copy)
	{
		Util::printError("Object copy: couldn't find an available item index.");
		return ERROR_INACTIVE_ITEM_INDEX;
	}
	else
	{
		std::stringstream message;
		message << "Attempting to copy item #" << original->getID() << " to item #" << copy->getID() << std::endl;
		Util::printServer(message.str());
	}

	if(!original->getActive())
	{
		Util::printError("Object copy: attempting to copy an inactive object index.");
		return ERROR_INACTIVE_ITEM_INDEX;
	}

	copy->setActive(true);
	copy->setType(original->getType());
	copy->setShortDescription(original->getShortDescription());
	copy->setLongDescription(original->getLongDescription());

	if(copy->isWeapon())
	{
		copy->setDamage(original->getDamage());
		copy->setMinimumDamage(original->getMinimumDamage());
	}

	return SUCCESS;
}

void ItemManager::listItemIndexStats(Player *player, std::vector<std::string> commands)
{
	std::stringstream message;

	uint32_t item_id = Util::stringToInteger(commands[1]);

	if(!item_id)
	{
		return;
	}

	Item *item = ItemManager::findItemIndex(item_id);

	message << "ID:\t" << item->getID() << "\t" << "Type:\t" << ItemManager::getItemTypeString(item->getType()) << std::endl;
	message << "Short:\t" << item->getShortDescription() << std::endl;
	message << "Long:\t" << item->getLongDescription() << std::endl;

	Util::sendToPlayer(player, message.str());
}
