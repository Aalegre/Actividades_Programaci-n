#include "EnemyManager.h"

weapon::weapon() { name = ""; type = MELEE; range = 0; }
weapon::weapon(std::unordered_map<std::string, std::string> & attributes_, const std::string & name_)
{
	name = name_;

	range = std::atoi(attributes_["range"].c_str());
	std::string typeS = attributes_["type"];
	if (typeS == "magic") {
		type = MAGIC;
	}
	else if (typeS == "distance") {
		type = DISTANCE;
	}
	else {
		type = MELEE;
	}
}
attack::attack() { damage = 0; frequency = 0; }
attack::attack(std::unordered_map<std::string, std::string> & attributes_)
{
	damage = std::atoi(attributes_["damage"].c_str());
	frequency = std::atoi(attributes_["frequency"].c_str());
}
;
Enemy::Enemy() { name = ""; life = 0; defense = 0; xp = 0; }
Enemy::Enemy(std::string name_, int life_, int defense_, int xp_, attack attack_, std::vector<weapon> weapons_) { name = name_; life = life_; defense = defense_; xp = xp_; attk = attack_; weapons = weapons_;}

std::vector<Enemy> getEnemies(rapidxml::xml_node<> * enemiesNode_)
{
	std::vector<Enemy> enemies;

	for (rapidxml::xml_node<>* pNode = enemiesNode_->first_node("enemy"); pNode; pNode = pNode->next_sibling())
	{
		std::unordered_map<std::string, std::string> enemyAttributes = getAttributes(pNode);
		std::unordered_map<std::string, std::string> enemyAttackAttributes = getAttributes(pNode->first_node("attack"));
		std::vector<weapon> weapons = getWeapons(pNode->first_node("weapons"));
		enemies.push_back(Enemy(
			enemyAttributes["name"],
			std::atoi(enemyAttributes["life"].c_str()),
			std::atoi(enemyAttributes["defense"].c_str()),
			std::atoi(enemyAttributes["xp"].c_str()),
			attack(enemyAttackAttributes),
			weapons
		));
	}


	return enemies;
}

std::vector<weapon> getWeapons(rapidxml::xml_node<> * weaponsNode_)
{
	std::vector<weapon> weapons;

	for (rapidxml::xml_node<>* pNode = weaponsNode_->first_node("weapon"); pNode; pNode = pNode->next_sibling())
	{
		std::unordered_map<std::string, std::string> attributes = getAttributes(pNode);
		std::string name = pNode->value();
		weapons.push_back(weapon(attributes, name));
	}
	return weapons;
}

std::unordered_map<std::string, std::string> getAttributes(rapidxml::xml_node<> * node_)
{
	std::unordered_map <std::string, std::string> attributes;

	for (rapidxml::xml_attribute<> * pAttr = node_->first_attribute(); pAttr; pAttr = pAttr->next_attribute())
	{
		attributes[pAttr->name()] = pAttr->value();
	}

	return attributes;
}
