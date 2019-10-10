#pragma once
#include "Vector2.h"

class Sprite
{
public:
	const string path;
	const Vector2Int size;
	const Vector2Int tiles;
	Vector2Int renderPos;
	const Vector2Int renderSize;
	unsigned int lastPos;
	const unsigned int tileCount;

	Sprite(string path_, Vector2Int size_, Vector2Int tiles_) : path(path_), size(size_), tiles(tiles_), renderPos({ 0,0 }), renderSize({int(size_.x / tiles_.x), int(size_.y / tiles_.y)}), lastPos(-1), tileCount(tiles_.x * tiles_.y) {};
	
	void loadPos(unsigned int pos_);
	void loadPos(Vector2Int pos_);
};

