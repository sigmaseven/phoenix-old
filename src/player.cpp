#include "./playermanager.h"

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

bool Player::setStrength(uint8_t s)
{
	if(s > 0)
	{
		this->strength = s;
		return true;
	}
	return false;
}

uint8_t Player::getPerception()
{
	return this->perception;
}

bool Player::setPerception(uint8_t p)
{
	if(p > 0)
	{
		this->perception = p;
		return true;
	}
	return false;
}

uint8_t Player::getEndurance()
{
	return this->endurance;
}

bool Player::setEndurance(uint8_t e)
{
	if(e > 0)
	{
		this->endurance = e;
		return true;
	}
	return false;
}

uint8_t Player::getCharisma()
{
	return this->charisma;
}

bool Player::setCharisma(uint8_t c)
{
	if(c > 0)
	{
		this->charisma = c;
		return true;
	}
	return false;
}

uint8_t Player::getIntelligence()
{
	return this->intelligence;
}

bool Player::setIntelligence(uint8_t i)
{
	if(i > 0)
	{
		this->intelligence = i;
		return true;
	}
	return false;
}

uint8_t Player::getAgility()
{
	return this->agility;
}

bool Player::setAgility(uint8_t a)
{
	if(a > 0)
	{
		this->agility = a;
		return true;
	}
	return false;
}

uint8_t Player::getLuck()
{
	return this->luck;
}

bool Player::setLuck(uint8_t l)
{
	if(l > 0)
	{
		this->luck = l;
		return true;
	}
	return false;
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

bool Player::setHealth(uint16_t hp)
{
	if(hp > 0)
	{
		this->health = hp;
		return true;
	}
	return false;
}

uint16_t Player::getMaxHealth()
{
	return this->max_health;
}

bool Player::setMaxHealth(uint16_t hp)
{
	if(hp > 0)
	{
		this->max_health = hp;
		return true;
	}
	return false;
}

uint16_t Player::getMana()
{
	return this->mana;
}

bool Player::setMana(uint16_t mp)
{
	if(mp > 0)
	{
		this->mana = mp;
		return true;
	}
	return false;
}

uint16_t Player::getMaxMana()
{
	return this->max_mana;
}

bool Player::setMaxMana(uint16_t mp)
{
	if(mp > 0)
	{
		this->max_mana = mp;
		return true;
	}
	return false;
}

uint16_t Player::getMovement()
{
	return this->movement;
}

bool Player::setMovement(uint16_t mp)
{
	if(mp > 0)
	{
		this->movement = mp;
		return true;
	}
	return false;
}

uint16_t Player::getMaxMovement()
{
	return this->max_movement;
}

bool Player::setMaxMovement(uint16_t mp)
{
	if(mp > 0)
	{
		this->max_movement = mp;
		return true;
	}
	return false;
}

uint32_t Player::getRoom()
{
	return this->room;
}

bool Player::setRoom(uint32_t id)
{
	Room *room = AreaManager::findRoom(id);

	if(room->getID() > 0 && room->getActive())
	{
		this->room = id;
		return true;
	}
	return false;
}
