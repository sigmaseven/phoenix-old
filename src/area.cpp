#include "./areamanager.h"

uint32_t Area::getID()
{
	return this->id;
}

void Area::setID(uint32_t number)
{
	this->id = number;
}

std::string Area::getDescription()
{
	return this->description;
}

void Area::setDescription(std::string desc)
{
	this->description = desc;
}

bool Area::getActive()
{
	return this->active;
}

void Area::setActive(bool option)
{
	this->active = option;
}

void Area::loadFromFile(char *filename)
{
	std::string contents = Util::readFromFile(filename);
	auto j = nlohmann::json::parse(contents.c_str());

	uint32_t id = j["area"]["id"];
	Area *area = AreaManager::findArea(id);
	//area->setID(j["area"]["id"]);
	//area->setTitle(j["area"]["title"]);
	//area->setDecription(j["area"]["description"];


}
