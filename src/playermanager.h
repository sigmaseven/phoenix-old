#pragma once
#include "game.h"
#include "server.h"
#include "nanny.h"

class Player
{
	std::string name;
	std::string password;

	uint16_t health;
	uint16_t max_health;
	uint16_t mana;
	uint16_t max_mana;
	uint16_t movement;
	uint16_t max_movement;

	uint8_t strength;
	uint8_t perception;
	uint8_t endurance;
	uint8_t charisma;
	uint8_t intelligence;
	uint8_t luck;

	bool active;
	int clientfd;
public:
	uint8_t getStrength(){ return this->strength; }
	uint8_t getPerception(){ return this->perception; }
	uint8_t getEndurance(){ return this->endurance; }
	uint8_t getCharisma(){ return this->charisma; }
	uint8_t getIntelligence(){ return this->intelligence; }
	uint8_t getLuck(){ return this->luck; }
	std::string getName(){ return this->name; }
	bool getActive(){ return this->active; }
	int getFileDescriptor(){ return this->clientfd; }
	uint16_t getHealth(){ return this->health; }
	uint16_t getMaxHealth(){ return this->max_health; }
	uint16_t getMana(){ return this->mana; }
	uint16_t getMaxMana(){ return this->max_mana; }
	uint16_t getMovement(){ return this->movement; }
	uint16_t getMaxMovement(){ return this->max_movement; }

	void setHealth(uint16_t hp){ this->health = hp; }
	void setMaxHealth(uint16_t hp){ this->max_health = hp; }
	void setMana(uint16_t mp){ this->mana = mp; }
	void setMaxMana(uint16_t mp){ this->max_mana = mp; }
	void setMovement(uint16_t mp){ this->movement = mp; }
	void setMaxMovement(uint16_t mp){ this->max_movement = mp; }
	void setActive(bool b){ this->active = b; }
	void setName(std::string name){ this->name = name; }
	void setPassword(std::string password){ this->password = password; }
	void setFileDescriptor(int fd){ this->clientfd = fd; }
};

class PlayerManager
{
	static std::vector<Player *> players;

public:
	static void init();
	static Player *findOpenPlayerSlot();
};
