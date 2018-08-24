#include "./itemmanager.h"

std::vector<Item *> ItemManager::items;

void ItemManager::init()
{
	uint32_t x;

	for(x = 0; x < MAX_ITEMS; x++)
	{
		Item *item = new Item();
		item->setID(x);
		item->setActive(false);
		items.push_back(item);
	}
}

Item *ItemManager::findAvailableItem()
{
	uint32_t x;

	for(x = 0; x < MAX_ITEMS; x++)
	{
		Item *item = items[x];

		if(!item->getActive())
		{
			return item;
		}
	}

	return NULL;
}

Item *ItemManager::findItem(uint32_t id)
{
	if(id > MAX_ITEMS)
	{
		return NULL;
	}

	return items[id];
}
