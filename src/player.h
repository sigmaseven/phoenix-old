#pragma once
#include "./game.h"
#include "./server.h"
#include "./nanny.h"
#include "./util.h"
#include "./areamanager.h"

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
	uint8_t agility;
	uint8_t luck;

	bool active;
	int clientfd;
	uint32_t room;
	bool autodig;
public:
	uint8_t getStrength();
	uint8_t getPerception();
	uint8_t getEndurance();
	uint8_t getCharisma();
	uint8_t getAgility();
	uint8_t getIntelligence();
	uint8_t getLuck();
	std::string getName();
	bool getActive();
	int getFileDescriptor();
	uint16_t getHealth();
	uint16_t getMaxHealth();
	uint16_t getMana();
	uint16_t getMaxMana();
	uint16_t getMovement();
	uint16_t getMaxMovement();
	std::string getPassword();
	uint32_t getRoom();
	bool getAutoDig();

	ErrorCode setHealth(uint16_t hp);
	ErrorCode setMaxHealth(uint16_t hp);
	ErrorCode setMana(uint16_t mp);
	ErrorCode setMaxMana(uint16_t mp);
	ErrorCode setMovement(uint16_t mp);
	ErrorCode setMaxMovement(uint16_t mp);
	ErrorCode setStrength(uint8_t s);
	ErrorCode setPerception(uint8_t p);
	ErrorCode setEndurance(uint8_t e);
	ErrorCode setCharisma(uint8_t c);
	ErrorCode setIntelligence(uint8_t i);
	ErrorCode setAgility(uint8_t a);
	ErrorCode setLuck(uint8_t l);
	ErrorCode setRoom(uint32_t room_number);
	void setActive(bool b);
	void setName(std::string n);
	void setPassword(std::string p);
	bool setFileDescriptor(int fd);
	bool setAutoDig(bool dig);

	void moveToRoom(uint32_t room_number, Exit direction);
};
