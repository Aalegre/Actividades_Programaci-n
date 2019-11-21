#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>

#include "../../dep/inc/Aalegre/Interpolation.h"
#include "../../dep/inc/Aalegre/RigidBody2D.h"
#include "../../dep/inc/Aalegre/InputSystem.h"
#include "../../dep/inc/Aalegre/GameTime.h"

//Game general information
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SCREEN_WIDTH_CENTER SCREEN_WIDTH/2
#define SCREEN_HEIGHT_CENTER SCREEN_HEIGHT/2

#define AUDIO_FREQUENCY 48000

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void Init(SDL_Window*& m_window, SDL_Renderer*& m_renderer) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	m_window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) throw "No es pot inicialitzar SDL_Window";

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Close(SDL_Window*& m_window, SDL_Renderer*& m_renderer) {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	m_renderer = nullptr;
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	GameTime gameTime(60, 1, false);
	srand(time(NULL));

	try {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		Init(window, renderer);
		SDL_Event e;
		bool quit = false;

		//std::vector<Vector2> polyPoints;
		//for (size_t i = 0; i < rand() % 10 +3; i++)
		//{
		//	polyPoints.push_back({ float(rand() % 400 - 200), float(rand() % 400 - 200) });
		//}
		//RigidBody2D polygon1({ SCREEN_WIDTH_CENTER,SCREEN_HEIGHT_CENTER }, polyPoints, false);
		//std::vector<Vector2> polyPoints2;
		//for (size_t i = 0; i < rand() % 10 +3; i++)
		//{
		//	polyPoints2.push_back({ float(rand() % 400 - 200), float(rand() % 400 - 200) });
		//}
		//RigidBody2D polygon2({ SCREEN_WIDTH_CENTER,SCREEN_HEIGHT_CENTER }, polyPoints2, false);

		RigidBody2D polygon1({ SCREEN_WIDTH_CENTER,SCREEN_HEIGHT_CENTER }, {100, 200}, false);
		RigidBody2D polygon2({ SCREEN_WIDTH_CENTER,SCREEN_HEIGHT_CENTER }, {250, 250}, false);

		SDL_Event event;
		InputSystem inputs;
		inputs["mousePos"] = new Input(AXIS, false, 10000);

		while (!quit) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					quit = true;
					continue;
					break;
				//case SDL_KEYDOWN:
				//	inputs["exit"].setInput(event.key.keysym.sym == SDLK_ESCAPE);
				//	break;
				case SDL_MOUSEMOTION:
					inputs["mousePos"].setInput({ float(event.motion.x), float(event.motion.y) });
					break;
				//case SDL_MOUSEBUTTONDOWN:
				//	inputs["mouseClick"].setButtonDown();
				//	break;
				//case SDL_MOUSEBUTTONUP:
				//	inputs["mouseClick"].setButtonUp();
				//	break;
				default:;
				}
			}
			SDL_SetRenderDrawColor(renderer, 0,0,0,255);
			SDL_RenderClear(renderer);
			if (polygon1.isColliding(polygon2)) {
				SDL_SetRenderDrawColor(renderer, 255, 100, 200, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}

			polygon1.rotate(polygon1.getRotation() + 1000 * gameTime.getFixedDeltaTime());
			std::vector<Vector2> polygonPoints = polygon1.getPoints();
			Vector2 oldPoint = polygonPoints[polygonPoints.size() - 1];
			for (std::vector<Vector2>::iterator it = polygonPoints.begin(); it != polygonPoints.end(); ++it) {
				SDL_RenderDrawLine(renderer, oldPoint.x, oldPoint.y, it->x, it->y);
				oldPoint = *it;
			}

			polygon2.teleport(inputs["mousePos"].getAxis());
			polygon2.rotate(polygon2.getRotation() + 1000 * gameTime.getFixedDeltaTime());


			std::vector<Vector2> polygonPoints2 = polygon2.getPoints();
			oldPoint = polygonPoints2[polygonPoints2.size() - 1];
			for (std::vector<Vector2>::iterator it = polygonPoints2.begin(); it != polygonPoints2.end(); ++it) {
				SDL_RenderDrawLine(renderer, oldPoint.x, oldPoint.y, it->x, it->y);
				oldPoint = *it;
			}

			gameTime.nextTick();

			if (gameTime.canRender()) {
				SDL_RenderPresent(renderer);
				//cout << "fixedDelta  " << gameTime.getFixedDeltaTime() << endl;
				//cout << "Delta       " << gameTime.getDeltaTime() << endl;
				//cout << "tickCount   " << gameTime.getLastFrameTickCount() << endl;
				//cout << "renderTime  " << gameTime.getLastRenderTime() << endl;
				cout << "FPS         " << gameTime.getCurrentFPS() << endl;
				gameTime.nextFrame();
			}
		}
		Close(window, renderer);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		auto sdlError = SDL_GetError();
		if (strlen(sdlError)) std::cout << "SDL Error: " << sdlError << std::endl;
		std::cin.get();
	}
	return 0;
}