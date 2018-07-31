#pragma once
#include "nlohmann/json.hpp"

#include <vector>
#include <iostream>
#include <sstream>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <openssl/sha.h>

#define MAX_NPC      65535
#define MAX_PLAYERS  128
#define MAX_INPUT    1024
#define MAX_HEALTH   65535
#define MAX_MANA     65535
#define MAX_MOVEMENT 65535
