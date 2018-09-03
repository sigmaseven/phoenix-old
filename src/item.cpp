#include "./item.h"

uint32_t Item::getID()
{
	return this->id;
}

bool Item::setID(uint32_t new_id)
{
	if(new_id > 0)
	{
		this->id = new_id;
		return true;
	}
	return false;
}

std::string Item::getShortDescription()
{
	return this->short_description;
}

void Item::setShortDescription(std::string short_desc)
{
	this->short_description = short_desc;
}

std::string Item::getLongDescription()
{
	return this->long_description;
}

void Item::setLongDescription(std::string long_desc)
{
	this->long_description = long_desc;
}

bool Item::getActive()
{
	return this->active;
}

bool Item::setActive(bool option)
{
	this->active = option;
	return true;
}

uint32_t Item::getLevel()
{
	return this->level;
}

bool Item::setLevel(uint32_t new_level)
{
	if(level < 1)
	{
		return(false);
	}

	this->level = new_level;
	return(true);
}

uint32_t Item::getDamage()
{
	return this->damage;
}

bool Item::setDamage(uint32_t new_damage)
{
	if(new_damage < 1)
	{
		return(false);
	}

	this->damage = new_damage;

	return(true);
}

uint32_t Item::getMinimumDamage()
{
	return this->min_damage;
}

bool Item::setMinimumDamage(uint32_t new_damage)
{
	if(new_damage < 1)
	{
		return(false);
	}

	this->min_damage = new_damage;

	return(true);
}

ItemType Item::getType()
{
	return this->type;
}

void Item::setType(ItemType item_type)
{
	this->type = item_type;
}

uint32_t Item::getAmmoID()
{
	return this->ammo_id;
}

bool Item::setAmmoID(uint32_t new_ammo)
{
	if(new_ammo > MAX_ITEMS)
	{
		return(false);
	}

	this->ammo_id = new_ammo;

	return(true);
}
