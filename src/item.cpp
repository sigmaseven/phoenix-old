#include "./item.h"

uint32_t Item::getID()
{
	return this->id;
}

ErrorCode Item::setID(uint32_t new_id)
{
	if(new_id > 0)
	{
		this->id = new_id;
		return ERROR_INVALID_ITEM_ID;
	}

	return SUCCESS;
}

std::string Item::getShortDescription()
{
	return this->short_description;
}

ErrorCode Item::setShortDescription(std::string short_desc)
{
	this->short_description = short_desc;
	return SUCCESS;
}

std::string Item::getLongDescription()
{
	return this->long_description;
}

ErrorCode Item::setLongDescription(std::string long_desc)
{
	this->long_description = long_desc;
	return SUCCESS;
}

bool Item::getActive()
{
	return this->active;
}

ErrorCode Item::setActive(bool option)
{
	this->active = option;
	return SUCCESS;
}

uint32_t Item::getLevel()
{
	return this->level;
}

ErrorCode Item::setLevel(uint32_t new_level)
{
	if(level < 1)
	{
		return ERROR_INVALID_LEVEL;
	}

	this->level = new_level;
	return SUCCESS;
}

uint32_t Item::getDamage()
{
	return this->damage;
}

ErrorCode Item::setDamage(uint32_t new_damage)
{
	if(new_damage < 1)
	{
		return ERROR_INVALID_DAMAGE;
	}

	this->damage = new_damage;

	return SUCCESS;
}

uint32_t Item::getMinimumDamage()
{
	return this->min_damage;
}

ErrorCode Item::setMinimumDamage(uint32_t new_damage)
{
	if(new_damage < 1)
	{
		return ERROR_INVALID_DAMAGE;
	}

	this->min_damage = new_damage;

	return SUCCESS;
}

ItemType Item::getType()
{
	return this->type;
}

ErrorCode Item::setType(ItemType item_type)
{
	this->type = item_type;
	return SUCCESS;
}

uint32_t Item::getAmmoID()
{
	return this->ammo_id;
}

ErrorCode Item::setAmmoID(uint32_t new_ammo)
{
	if(new_ammo > MAX_ITEMS)
	{
		return ERROR_INVALID_AMMO_ID;
	}

	this->ammo_id = new_ammo;

	return SUCCESS;
}

bool Item::isWeapon()
{
	switch(type)
	{
		case ITEM_PISTOL:
		case ITEM_RIFLE:
		case ITEM_SMG:
		case ITEM_SHOTGUN:
		case ITEM_GRENADE:
		case ITEM_LASER_RIFLE:
		case ITEM_LASER_PISTOL:
		case ITEM_GAUSS_PISTOL:
		case ITEM_GAUSS_RIFLE:
		case ITEM_UNARMED:
		case ITEM_MELEE:
		case ITEM_HEAVY_WEAPON:
		case ITEM_SNIPER:
			return true;
		default:
			return false;
	}

	return false;
}

bool Item::isArmor()
{
	switch(type)
	{
		case ITEM_ARMOR:
			return true;

		default:
			return false;
	}

	return false;
}

uint32_t Item::getCondition()
{
	return this->condition;
}

ErrorCode Item::setCondition(uint32_t new_condition)
{
	if(new_condition < 0 || new_condition > MAX_CONDITION)
	{
		return ERROR_INVALID_CONDITION;
	}

	this->condition = new_condition;
	return SUCCESS;
}

