#pragma once

#include <vector>
#include <unordered_map >
#include <string>

#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

const enum WEAPON_TYPE { MELEE, DISTANCE, MAGIC, COUNT };

struct weapon {
	std::string name;
	WEAPON_TYPE type;
	int range;
	weapon();
	weapon(std::unordered_map<std::string, std::string> & attributes_, const std::string & name_);
};

struct attack {
	int damage;
	int frequency;
	attack();
	attack(std::unordered_map<std::string, std::string> & attributes_);
};

class Enemy {
public:
	std::string name;
private:
	int life;
	int defense;
	int xp;
	attack attk;
	std::vector<weapon> weapons;
public:
	Enemy();
	Enemy(std::string name_, int life_, int defense_, int xp_, attack attack_, std::vector<weapon> weapons_);
};

std::vector<Enemy> getEnemies(rapidxml::xml_node<> * enemiesNode_);
std::vector<weapon> getWeapons(rapidxml::xml_node<> * weaponsNode_);
std::unordered_map<std::string, std::string> getAttributes(rapidxml::xml_node<> * node_);