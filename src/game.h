#pragma once
#include "nlohmann/json.hpp"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <openssl/sha.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define MAX_ITEMS	65535
#define MAX_NPCS	65535
#define MAX_PLAYERS  	128
#define MAX_INPUT_SIZE  1024
#define MAX_HEALTH   	65535
#define MAX_MANA     	65535
#define MAX_MOVEMENT 	65535
#define MAX_ROOMS	65535
#define MAX_AREAS	32768
#define MAX_STAT	255
#define MAX_CONDITION	65535

enum Color
{
	FG_BLACK = 30,
	FG_RED,
	FG_GREEN,
	FG_YELLOW,
	FG_BLUE,
	FG_MAGENTA,
	FG_CYAN,
	FG_GREY
};

enum Exit
{
	EXIT_NORTH,
	EXIT_SOUTH,
	EXIT_EAST,
	EXIT_WEST,
	EXIT_UP,
	EXIT_DOWN,
	EXIT_TELEPORT
};

enum ErrorCode
{
	SUCCESS,
	ERROR_INVALID_PORT,
	ERROR_MAX_PLAYERS,
	ERROR_MAX_ITEMS,
	ERROR_MAX_NPCS,
	ERROR_INACTIVE_ROOM,
	ERROR_INACTIVE_ITEM_INDEX,
	ERROR_INACTIVE_NPC_INDEX,
	ERROR_ACTIVE_ITEM_INDEX,
	ERROR_ACTIVE_ROOM_INDEX,
	ERROR_ACTIVE_NPC_INDEX,
	ERROR_INVALID_ROOM_ID,
	ERROR_INVALID_ITEM_ID,
	ERROR_INVALID_NPC_ID,
	ERROR_INVALID_AMMO_ID,
	ERROR_INVALID_PLAYER_NUMBER,
	ERROR_INVALID_LEVEL,
	ERROR_INVALID_STRENGTH,
	ERROR_INVALID_PERCEPTION,
	ERROR_INVALID_ENDURANCE,
	ERROR_INVALID_CHARISMA,
	ERROR_INVALID_INTELLIGENCE,
	ERROR_INVALID_AGILITY,
	ERROR_INVALID_LUCK,
	ERROR_INVALID_MOVEMENT,
	ERROR_INVALID_MAX_MOVEMENT,
	ERROR_INVALID_HEALTH,
	ERROR_INVALID_MAX_HEALTH,
	ERROR_INVALID_MANA,
	ERROR_INVALID_MAX_MANA,
	ERROR_INVALID_DAMAGE,
	ERROR_INVALID_CONDITION
};
