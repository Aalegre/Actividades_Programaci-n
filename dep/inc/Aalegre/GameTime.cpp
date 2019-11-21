#include "GameTime.h"

const unsigned long int GameTime::getFrameCount()
{
	return frameCount;
}

const unsigned long int GameTime::getTickCount()
{
	return tickCount;
}

const unsigned long int GameTime::getLastFrameTickCount()
{
	return lastFrameTickCount;
}

const float GameTime::getDeltaTime()
{
	return deltaTime;
}

const float GameTime::getFixedDeltaTime()
{
	return fixedDeltaTime * timeScale;
}

const float GameTime::getLastRenderTime()
{
	return lastRenderTime;
}

const float GameTime::getCurrentFPS()
{
	return 1.0 / deltaTime;
}

bool GameTime::canRender()
{
	if (frameControl) {
		long float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastFrame).count();
		elapsed /= 1000.0f;

		if (elapsed + lastRenderTime >= renderTime) {
			lastRenderStart = std::chrono::steady_clock::now();
			return true;
		}
		else
			return false;
	}
	return true;
}

void GameTime::nextFrame()
{
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastFrame).count();
	deltaTime /= 1000.0f;
	lastFrame = std::chrono::steady_clock::now();

	lastRenderTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastRenderStart).count();
	lastRenderTime /= 1000.0f;

	frameCount++;
	lastFrameTickCount = 0;
}

void GameTime::nextTick()
{
	fixedDeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastTick).count();
	fixedDeltaTime /= 1000.0f;
	lastTick = std::chrono::steady_clock::now();
	lastFrameTickCount++;
	tickCount++;
}
