#pragma once

#include <iostream>
#include <sstream>

#include "EnemyManager.h"


int main() {

	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/enemies.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	std::vector<Enemy> enemies = getEnemies(doc.first_node("enemies"));
}