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

#define MAX_NPC      	65535
#define MAX_PLAYERS  	128
#define MAX_INPUT_SIZE  1024
#define MAX_HEALTH   	65535
#define MAX_MANA     	65535
#define MAX_MOVEMENT 	65535
#define MAX_ROOMS	65535
#define MAX_AREAS	32768

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
