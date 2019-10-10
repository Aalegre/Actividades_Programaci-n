#include "GameTime.h"

const float GameTime::getDeltaTime()
{
	return 0.0f;
}

const float GameTime::getFixedDeltaTime()
{
	return fixedDeltaTime * timeScale;
}

const bool GameTime::canRender()
{
	return false;
}

void GameTime::nextFrame()
{
}

void GameTime::nextTick()
{
}
