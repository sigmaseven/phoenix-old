#pragma once
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
#include <pthread.h>

#define MAX_NPC 64000
#define MAX_PLAYERS 128
#define MAX_INPUT 1024
