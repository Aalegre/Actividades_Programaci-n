#include "Sprite.h"

void Sprite::loadPos(unsigned int pos_)
{
	if (pos_ != lastPos) {
		if (pos_ >= tileCount)
			pos_ = tileCount - 1;
		unsigned int xPos = pos_ % tiles.x;
		unsigned int yPos = pos_ / tiles.x;

		renderPos.x = xPos * renderSize.x;
		renderPos.x = yPos * renderSize.y;
	}
}

void Sprite::loadPos(Vector2Int pos_)
{
	renderPos.x = pos_.x * renderSize.x;
	renderPos.x = pos_.y * renderSize.y;
}
