#include "./player.h"

std::string Player::getName()
{
	return this->name;
}

void Player::setName(std::string n)
{
	this->name = n;
}

std::string Player::getPassword()
{
	return this->password;
}

void Player::setPassword(std::string p)
{
	this->password = p;
}

uint8_t Player::getStrength()
{
	return this->strength;
}

ErrorCode Player::setStrength(uint8_t s)
{
	if(s > 0 && s < MAX_STAT)
	{
		this->strength = s;
		return SUCCESS;;
	}
	return ERROR_INVALID_STRENGTH;
}

uint8_t Player::getPerception()
{
	return this->perception;
}

ErrorCode Player::setPerception(uint8_t p)
{
	if(p > 0 && p < MAX_STAT)
	{
		this->perception = p;
		return SUCCESS;
	}

	return ERROR_INVALID_PERCEPTION;;
}

uint8_t Player::getEndurance()
{
	return this->endurance;
}

ErrorCode Player::setEndurance(uint8_t e)
{
	if(e > 0 && e < MAX_STAT)
	{
		this->endurance = e;
		return SUCCESS;
	}

	return ERROR_INVALID_ENDURANCE;
}

uint8_t Player::getCharisma()
{
	return this->charisma;
}

ErrorCode Player::setCharisma(uint8_t c)
{
	if(c > 0 && c < MAX_STAT)
	{
		this->charisma = c;
		return SUCCESS;
	}

	return ERROR_INVALID_CHARISMA;;
}

uint8_t Player::getIntelligence()
{
	return this->intelligence;
}

ErrorCode Player::setIntelligence(uint8_t i)
{
	if(i > 0 && i < MAX_STAT)
	{
		this->intelligence = i;
		return SUCCESS;
	}

	return ERROR_INVALID_INTELLIGENCE;
}

uint8_t Player::getAgility()
{
	return this->agility;
}

ErrorCode Player::setAgility(uint8_t a)
{
	if(a > 0 && a < MAX_STAT)
	{
		this->agility = a;
		return SUCCESS;
	}
	return ERROR_INVALID_AGILITY;
}

uint8_t Player::getLuck()
{
	return this->luck;
}

ErrorCode Player::setLuck(uint8_t l)
{
	if(l > 0 && l < MAX_STAT)
	{
		this->luck = l;
		return SUCCESS;
	}

	return ERROR_INVALID_LUCK;
}

bool Player::getActive()
{
	return this->active;
}

void Player::setActive(bool b)
{
	this->active = b;
}

uint16_t Player::getHealth()
{
	return this->health;
}

ErrorCode Player::setHealth(uint16_t hp)
{
	if(hp > 0 && hp < MAX_HEALTH && hp < this->max_health)
	{
		this->health = hp;
		return SUCCESS;
	}

	return ERROR_INVALID_HEALTH;
}

uint16_t Player::getMaxHealth()
{
	return this->max_health;
}

ErrorCode Player::setMaxHealth(uint16_t hp)
{
	if(hp > 0 && hp < MAX_HEALTH)
	{
		this->max_health = hp;
		return ERROR_INVALID_MAX_HEALTH;
	}

	return SUCCESS;
}

uint16_t Player::getMana()
{
	return this->mana;
}

ErrorCode Player::setMana(uint16_t mp)
{
	if(mp > 0 && mp < MAX_MANA)
	{
		this->mana = mp;
		return SUCCESS;
	}

	return ERROR_INVALID_MANA;
}

uint16_t Player::getMaxMana()
{
	return this->max_mana;
}

ErrorCode Player::setMaxMana(uint16_t mp)
{
	if(mp > 0)
	{
		this->max_mana = mp;
		return SUCCESS;
	}

	return ERROR_INVALID_MAX_MANA;
}

uint16_t Player::getMovement()
{
	return this->movement;
}

ErrorCode Player::setMovement(uint16_t mp)
{
	if(mp > 0 && mp < MAX_MOVEMENT && mp < this->max_movement)
	{
		this->movement = mp;
		return SUCCESS;
	}

	return ERROR_INVALID_MOVEMENT;
}

uint16_t Player::getMaxMovement()
{
	return this->max_movement;
}

ErrorCode Player::setMaxMovement(uint16_t mp)
{
	if(mp > 0 && mp < MAX_MOVEMENT)
	{
		this->max_movement = mp;
		return SUCCESS;
	}

	return ERROR_INVALID_MAX_MOVEMENT;
}

uint32_t Player::getRoom()
{
	return this->room;
}

ErrorCode Player::setRoom(uint32_t id)
{

	if(id < 0 || id > MAX_ROOMS)
	{
		return ERROR_INVALID_ROOM_ID;
	}

	Room *room = AreaManager::findRoom(id);

	if(room->getID() < 0)
	{
		return ERROR_INVALID_ROOM_ID;
	}

	if(!room->getActive())
	{
		return ERROR_INACTIVE_ROOM;
	}

	this->room = id;
	return SUCCESS;
}
