#pragma once
#include "./game.h"

enum ItemType
{
	ITEM_NULL,
	ITEM_JUNK,
	ITEM_ARMOR,
	ITEM_AMMO,
	ITEM_FOOD,
	ITEM_WATER,
	ITEM_ALCOHOL,
	ITEM_STIMPACK,
	ITEM_MEDKIT,
	ITEM_MEDICINE,
	ITEM_UNARMED,
	ITEM_MELEE,
	ITEM_PISTOL,
	ITEM_RIFLE,
	ITEM_SMG,
	ITEM_SNIPER,
	ITEM_SHOTGUN,
	ITEM_GRENADE,
	ITEM_LASER_PISTOL,
	ITEM_LASER_RIFLE,
	ITEM_GAUSS_PISTOL,
	ITEM_GAUSS_RIFLE,
	ITEM_HEAVY_WEAPON
};

class Item
{
	uint32_t id;
	bool active;
	uint32_t level;
	ItemType type;
	uint32_t damage;
	uint32_t min_damage;
	uint32_t ammo_id;
	std::string short_description;
	std::string long_description;

public:
	uint32_t getID();
	bool getActive();
	std::string getShortDescription();
	std::string getLongDescription();
	uint32_t getLevel();
	uint32_t getDamage();
	uint32_t getMinimumDamage();
	ItemType getType();
	uint32_t getAmmoID();

	bool setID(uint32_t new_id);
	bool setActive(bool option);
	void setShortDescription(std::string short_desc);
	void setLongDescription(std::string long_desc);
	bool setLevel(uint32_t new_level);
	bool setDamage(uint32_t new_damage);
	bool setMinimumDamage(uint32_t new_damage);
	void setType(ItemType item_type);
	bool setAmmoID(uint32_t new_ammo);

        Item()
        {
                type = ITEM_JUNK;
                level = 0;
                active = false;
                damage = 0;
                min_damage = 0;
                short_description = "";
                long_description  = "";
        }

};