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

	bool setHealth(uint16_t hp);
	bool setMaxHealth(uint16_t hp);
	bool setMana(uint16_t mp);
	bool setMaxMana(uint16_t mp);
	bool setMovement(uint16_t mp);
	bool setMaxMovement(uint16_t mp);
	bool setStrength(uint8_t s);
	bool setPerception(uint8_t p);
	bool setEndurance(uint8_t e);
	bool setCharisma(uint8_t c);
	bool setIntelligence(uint8_t i);
	bool setAgility(uint8_t a);
	bool setLuck(uint8_t l);
	bool setRoom(uint32_t room_number);
	void setActive(bool b);
	void setName(std::string n);
	void setPassword(std::string p);
	bool setFileDescriptor(int fd);
	bool setAutoDig(bool dig);

	void moveToRoom(uint32_t room_number, Exit direction);
};

class PlayerManager
{
	static std::vector<Player *> players;
public:
	static long update_timestamp;
	static void init();
	static Player *findOpenPlayerSlot();
	static void writePlayerFile(Player *player);
	static bool playerFileExists(std::string name);
	static void resetPlayer(Player *player);
	static void readPlayerFile(Player *player, std::string name);
	static void *update(void *cmd);
	static std::vector<Player *> getActivePlayers();
	static long getLastUpdate(){ return PlayerManager::update_timestamp; }
	static void setLastUpdate(long timestamp){ PlayerManager::update_timestamp = timestamp; }
	static bool isPlayerOnline(std::string name);
	static Player *findPlayerByDescriptor(int fd);
};
