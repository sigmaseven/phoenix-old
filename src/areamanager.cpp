#include "areamanager.h"

std::vector<Room *> AreaManager::rooms;

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

	rooms[0]->setTitle(std::string("The Room"));
	std::stringstream desc;
	desc << "You stand in an oddly familiar brick-walled\n";
	desc << "apartment. A blue tie lies draped over a nearby\n";
	desc << "lamp shade, and for some reason nobody seems\n";
	desc << "concerned about shutting the front door.\n";
	rooms[0]->setDescription(desc.str());
	rooms[0]->setActive(true);

	rooms[1]->setTitle(std::string("The Rooftop"));
	desc.str("");
	desc << "You stand high above the buildings on the rooftop\n";
	desc << "here in the big apple... or is this San Francisco?\n";
	desc << "While you aren't really sure either way, you do\n";
	desc << "know you're on a very non-descript rooftop.\n";
	rooms[1]->setDescription(desc.str());
	rooms[1]->setActive(true);

	AreaManager::createExit(0, 1, EXIT_UP);
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

void AreaManager::createExit(uint32_t source_room, uint32_t dest_room, Exit direction)
{
        Room *src = AreaManager::findRoom(source_room);
        Room *dst = AreaManager::findRoom(dest_room);

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
			src->room_east = src->getID();
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
}
