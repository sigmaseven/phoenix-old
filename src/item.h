#pragma once
#include "./game.h"

enum ItemType
{
	ITEM_NULL,
	ITEM_JUNK,
	ITEM_ARMOR,
	ITEM_CLOTHING,
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
	ITEM_HEAVY_WEAPON,
	ITEM_AMMO_10MM,
	ITEM_AMMO_223,
	ITEM_AMMO_45,
	ITEM_AMMO_GAUSS,
	ITEM_AMMO_LASER
};

enum WearLocation
{
	WEAR_HEAD,
	WEAR_CHEST,
	WEAR_TORSO,
	WEAR_BACK,
	WEAR_WAIST,
	WEAR_ARMS,
	WEAR_LEGS,
	WEAR_HANDS,
	WEAR_FACE,
	WEAR_FEET
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
	uint32_t condition;
	uint32_t value;
	WearLocation wear_location;
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
	uint32_t getCondition();

	ErrorCode setID(uint32_t new_id);
	ErrorCode setActive(bool option);
	ErrorCode setShortDescription(std::string short_desc);
	ErrorCode setLongDescription(std::string long_desc);
	ErrorCode setLevel(uint32_t new_level);
	ErrorCode setDamage(uint32_t new_damage);
	ErrorCode setMinimumDamage(uint32_t new_damage);
	ErrorCode setType(ItemType item_type);
	ErrorCode setAmmoID(uint32_t new_ammo);
	ErrorCode setCondition(uint32_t new_condition);
	bool isWeapon();
	bool isArmor();

        Item()
        {
                type = ITEM_NULL;
                level = 0;
                active = false;
                damage = 0;
                min_damage = 0;
                short_description = "";
                long_description  = "";
        }

};
