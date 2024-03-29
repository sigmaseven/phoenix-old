#include "areamanager.h"

std::vector< Room *> AreaManager::rooms;
std::vector< Area *> AreaManager::areas;
std::vector< RoomDescription *> AreaManager::room_descriptions;

void AreaManager::init()
{
	int x;
	Util::printServer("Initializing rooms");

	for(x = 0; x < MAX_ROOMS; x++)
	{
		Room *room = new Room();
		room->setID(x);
		rooms.push_back(room);
	}

	for(x = 0; x < MAX_AREAS; x++)
	{
		Area *area = new Area();
		area->setID(x);
		areas.push_back(area);
	}

	AreaManager::loadAreaFiles();
	AreaManager::generateArea();
/*
	rooms[0]->setTitle(std::string("Purgatory"));
	rooms[0]->setDescription(std::string("Something has gone terribly wrong here.\n"));
	rooms[0]->setActive(true);
	rooms[1]->setTitle(std::string("The Room"));
	std::stringstream desc;
	desc << "You stand in an oddly familiar brick-walled\n";
	desc << "apartment. A blue tie lies draped over a nearby\n";
	desc << "lamp shade, and for some reason nobody seems\n";
	desc << "concerned about shutting the front door.\n";
	rooms[1]->setDescription(desc.str());
	rooms[1]->setActive(true);

	rooms[2]->setTitle(std::string("The Rooftop"));
	desc.str("");
	desc << "You stand high above the buildings on the rooftop\n";
	desc << "here in the big apple... or is this San Francisco?\n";
	desc << "While you aren't really sure either way, you do\n";
	desc << "know you're on a very non-descript rooftop.\n";
	rooms[2]->setDescription(desc.str());
	rooms[2]->setActive(true);

	AreaManager::createExit(1, 2, EXIT_UP);
*/
}

Room *AreaManager::findRoom(uint32_t room_id)
{
	if(room_id > rooms.size())
	{
		Util::printError("findRoom: Invalid lookup ID");
		return NULL;
	}
	return rooms[room_id];
}

Room *AreaManager::findAvailableRoom()
{
	uint32_t x;
	for(x = 0; x < rooms.size(); x++)
	{
		if(!rooms[x]->getActive())
		{
			std::cout << "findAvailableRoom: found room " << rooms[x]->getID() << std::endl;
			return rooms[x];
		}
	}
	return NULL;
}

void AreaManager::createExit(uint32_t source_room, uint32_t dest_room, Exit direction)
{
        Room *src = AreaManager::findRoom(source_room);
        Room *dst = AreaManager::findRoom(dest_room);
	std::cout << "source room id " << src->getID() << std::endl;
	std::cout << "dest room id " << dst->getID() << std::endl;
	if(source_room > rooms.size() || !rooms[source_room] || !src)
	{
		Util::printError("createExit: bad source room");
		return;
	}
	if( dest_room > rooms.size() || !rooms[dest_room] || !src)
	{
		Util::printError("createExit: bad dest room");
		return;
	}

	switch(direction)
	{
		default:
			break;
		case EXIT_NORTH:
			src->exit_north = true;
			src->room_north = dst->getID();
			dst->exit_south = true;
			dst->room_south = src->getID();
			break;
		case EXIT_SOUTH:
			src->exit_south = true;
			src->room_south = dst->getID();
			dst->exit_north = true;
			dst->room_north = src->getID();
			break;
		case EXIT_EAST:
			src->exit_east = true;
			src->room_east = dst->getID();
			dst->exit_west = true;
			dst->room_west = src->getID();
			break;
		case EXIT_WEST:
			src->exit_west = true;
			src->room_west = dst->getID();
			dst->exit_east = true;
			dst->room_east = src->getID();
			break;
		case EXIT_UP:
			src->exit_up = true;
			src->room_up = dst->getID();
			dst->exit_down = true;
			dst->room_down = src->getID();
			break;
		case EXIT_DOWN:
			src->exit_down = true;
			src->room_down = dst->getID();
			dst->exit_up = true;
			dst->room_up = src->getID();
			break;
	}
	if(!dst->getActive())
	{
		dst->setActive(true);
	}
	if(!src->getActive())
	{
		src->setActive(true);
	}
}

Area *AreaManager::generateArea()
{
	Area *area = new Area();
	return area;
}

Exit AreaManager::generateRandomDirection()
{
	Exit direction;
	int roll = Util::rollDice(1,6);
	switch(roll)
	{
		default:
			break;
		case 1:
			direction = EXIT_NORTH;
			break;
		case 2:
			direction = EXIT_SOUTH;
			break;
		case 3:
			direction = EXIT_EAST;
			break;
		case 4:
			direction = EXIT_WEST;
			break;
		case 5:
			direction = EXIT_UP;
			break;
		case 6:
			direction = EXIT_DOWN;
			break;
	}
	return direction;
}

void AreaManager::loadAreaFiles()
{
	DIR *directory;
	struct dirent *file;

	directory = opendir("./areas");

	if(directory)
	{
		while((file = readdir(directory)))
		{
			if(std::string(file->d_name).find(std::string(".json")) != std::string::npos)
			{
				std::string contents;
				std::stringstream filename;
				filename << "./areas/" << file->d_name;
				std::cout << "opening file " << filename.str() << std::endl;

				contents = Util::readFromFile(filename.str().c_str());
				std::cout << contents;
				auto j = nlohmann::json::parse(contents.c_str());
				uint32_t id = j["id"];

				for(uint32_t x = 0; x < j["rooms"].size(); x++)
				{
					uint32_t id = j["rooms"][x]["id"];
					Room *room = AreaManager::findRoom(id);
					room->setTitle(j["rooms"][x]["title"]);
					room->setDescription(j["rooms"][x]["description"]);

					if(j["rooms"][x]["exit_north"] == "true")
					{
						room->exit_north = true;
						room->room_north = j["rooms"][x]["room_north"];
					}
					if(j["rooms"][x]["exit_south"] == "true")
					{
						room->exit_south = true;
						room->room_south = j["rooms"][x]["room_south"];
					}
					if(j["rooms"][x]["exit_east"] == "true")
					{
						room->exit_east = true;
						room->room_east = j["rooms"][x]["room_east"];
					}
					if(j["rooms"][x]["exit_west"] == "true")
					{
						room->exit_west = true;
						room->room_west = j["rooms"][x]["room_west"];
					}
					if(j["rooms"][x]["exit_up"] == "true")
					{
						room->exit_up = true;
						room->room_up = j["rooms"][x]["room_up"];
					}
					if(j["rooms"][x]["exit_down"] == "true")
					{
						room->exit_down = true;
						room->room_down = j["rooms"][x]["room_down"];
					}
					room->setActive(true);
				}
			}
		}
	}
}

Area *AreaManager::findAvailableArea()
{
	uint32_t x;

	for(x = 0; x < areas.size(); x++)
	{
		if(!areas[x]->getActive())
		{
			return areas[x];
		}
	}
	return NULL;
}

Area *AreaManager::findArea(uint32_t id)
{
	if(id <= areas.size())
	{
		return areas[id];
	}
	return NULL;
}
