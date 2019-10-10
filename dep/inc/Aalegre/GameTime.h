#pragma once

#include <time.h> 

class GameTime
{
	clock_t lastTime;
	float timeDown;
	float deltaTime;
	float fixedDeltaTime;
	unsigned long int frameCount;
	unsigned long int tickCount;
public:
	const unsigned int FPS;
	const float renderTime;
	float timeScale;

	GameTime(unsigned int fps_, float timeScale_ = 1) : FPS(fps_), renderTime(1000 / fps_), timeScale(timeScale_){};

	const float getDeltaTime();
	const float getFixedDeltaTime();
	const bool canRender();

	void nextFrame();
	void nextTick();
};

