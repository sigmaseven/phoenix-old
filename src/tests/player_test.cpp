#include "../game.h"
#include "../playermanager.h"

int main(int argc, char **argv)
{
	std::cout << "Running player class unit tests..." << std::endl;

	Player *player = new Player();

	player->setName(std::string("test"));
	player->setPassword(std::string("test"));
	player->setStrength(1);
	player->setPerception(2);
	player->setEndurance(3);
	player->setCharisma(4);
	player->setIntelligence(5);
	player->setAgility(6);
	player->setLuck(7);
	player->setActive(true);

	if(player->getName() != "test")
	{
		std::cerr << "[!] Error setting/getting player name.\n";
	}

	if(player->getPassword() != "test")
	{
		std::cerr << "[!] Error setting/getting player password.\n";
	}

	if(player->getStrength() != 1)
	{
		std::cerr << "[!] Error setting/getting player strength.\n";
	}

	if(player->getPerception() != 2)
	{
		std::cerr << "[!] Error setting/getting player perception.\n";
	}

	if(player->getEndurance() != 3)
	{
		std::cerr << "[!] Error setting/getting player endurance.\n";
	}

	if(player->getCharisma() != 4)
	{
		std::cerr << "[!] Error setting/getting player charisma.\n";
	}

	if(player->getIntelligence() != 5)
	{
		std::cerr << "[!] Error setting/getting player intelligence.\n";
	}

	if(player->getAgility() != 6)
	{
		std::cerr << "[!] Error setting/getting player agility.\n";
	}

	if(player->getLuck() != 7)
	{
		std::cerr << "[!] Error setting/getting player luck.\n";
	}

	if(player->setStrength(0))
	{
		std::cerr << "[!] setStrength: value of zero allowed.\n";
	}

	if(player->setPerception(0) == SUCCESS)
	{
		std::cerr << "[!] setPerception: value of zero allowed.\n";
	}

	if(player->setEndurance(0) == SUCCESS)
	{
		std::cerr << "[!] setEndurance: value of zero allowed.\n";
	}

	if(player->setCharisma(0) == SUCCESS)
	{
		std::cerr << "[!] setCharisma: value of zero allowed.\n";
	}

	if(player->setIntelligence(0) == SUCCESS)
	{
		std::cerr << "[!] setIntelligence: value of zero allowed.\n";
	}

	if(player->setCharisma(0) == SUCCESS)
	{
		std::cerr << "[!] setCharisma: value of zero allowed.\n";
	}

	if(player->setAgility(0) == SUCCESS)
	{
		std::cerr << "[!] setAgility: value of zero allowed.\n";
	}

	if(player->setLuck(0) == SUCCESS)
	{
		std::cerr << "[!] setLuck: value of zero allowed.\n";
	}

	delete(player);

	std::cout << "Unit test complete." << std::endl;
}
