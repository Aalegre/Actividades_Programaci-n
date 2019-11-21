#pragma once

#include <chrono> 

class GameTime
{
	std::chrono::time_point<std::chrono::steady_clock> lastTick = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> lastFrame = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> lastRenderStart = std::chrono::steady_clock::now();
	float timeDown = 0;
	float deltaTime = 0;
	float fixedDeltaTime = 0;
	float lastRenderTime = 0;
	unsigned long int frameCount = 0;
	unsigned long int tickCount = 0;
	unsigned long int lastFrameTickCount = 0;
public:
	const unsigned int FPS;
	const float renderTime;
	float timeScale;
	bool frameControl;

	GameTime(unsigned int fps_ = 60, float timeScale_ = 1, bool frameControl_ = true) : FPS(fps_), renderTime(1.0f / fps_), timeScale(timeScale_), frameControl(frameControl_){};

	const unsigned long int getFrameCount();
	const unsigned long int getTickCount();
	const unsigned long int getLastFrameTickCount();
	const float getDeltaTime();
	const float getFixedDeltaTime();
	const float getLastRenderTime();
	const float getCurrentFPS();

	bool canRender();
	void nextFrame();
	void nextTick();
};

