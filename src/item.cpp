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
