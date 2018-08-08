#pragma once
#include "./game.h"
#include "./playermanager.h"
class AreaManager;

class RoomDescription
{
public:
	std::string title;
	std::string description;
};

class Room
{
	uint32_t id;
	bool active;
	std::string title;
	std::string description;
	std::vector<Player *> players;
public:
	bool exit_north;
	bool exit_south;
	bool exit_east;
	bool exit_west;
	bool exit_up;
	bool exit_down;
	uint32_t room_north;
	uint32_t room_south;
	uint32_t room_east;
	uint32_t room_west;
	uint32_t room_up;
	uint32_t room_down;
	bool visited;

	uint32_t getID(){ return this->id; }
	void setID(uint32_t new_id) { this->id = new_id; }
	std::string getTitle(){ return this->title; }
	void setTitle(std::string new_title){ this->title = new_title; }
	std::string getDescription(){ return this->description; }
	void setDescription(std::string new_desc){ this->description = new_desc; }
	void setActive(bool option){ this->active = option; }
	bool getActive() { return this->active; }

	Room()
	{
		id = 0;
		title = "";
		description = "";
		exit_north = false;
		exit_south = false;
		exit_east = false;
		exit_west = false;
		exit_up = false;
		exit_down = false;
		room_north = 0;
		room_south = 0;
		room_east = 0;
		room_west = 0;
		room_up = 0;
		room_down = 0;
	}
};

class Area
{
public:
	uint32_t start_room;
	int area_width;
	int area_height;
	std::vector<Room *> rooms;
};

class AreaManager
{
public:
	static std::vector<Room *> rooms;
	static std::vector<Area *> areas;
	static std::vector<RoomDescription *> room_descriptions;

	static void init();
	static Room *findRoom(uint32_t room_id);
	static void createExit(uint32_t source_room, uint32_t dest_room, Exit direction);
	static Area *generateArea();
	static Room *findAvailableRoom();
	static Exit generateRandomDirection();
	static void loadRoomFiles();
};