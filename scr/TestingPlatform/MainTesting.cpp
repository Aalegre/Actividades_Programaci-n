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
	srand(time(NULL));

	try {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		Init(window, renderer);
		SDL_Event e;
		bool quit = false;

		RigidBody2D box1({ SCREEN_WIDTH_CENTER,SCREEN_HEIGHT_CENTER }, { 50,100 }, false);
		RigidBody2D sphere1({ SCREEN_WIDTH_CENTER,SCREEN_HEIGHT_CENTER }, 250, false);

		std::vector<Vector2> polyPoints;
		for (size_t i = 0; i < rand() % 10 +3; i++)
		{
			polyPoints.push_back({ float(rand() % 400 - 200), float(rand() % 400 - 200) });
		}
		RigidBody2D polygon1({ SCREEN_WIDTH_CENTER,SCREEN_HEIGHT_CENTER }, polyPoints, false);

		while (!quit) {
			if (!SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) quit = true;
				if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;
			}
			SDL_SetRenderDrawColor(renderer, 0,0,0,255);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			box1.rotate(box1.getRotation() +1);
			std::vector<Vector2> boxPoints = box1.getPoints();
			Vector2 oldPoint = boxPoints[boxPoints.size()-1];
			for (std::vector<Vector2>::iterator it = boxPoints.begin(); it != boxPoints.end(); ++it) {
				SDL_RenderDrawLine(renderer, oldPoint.x, oldPoint.y, it->x, it->y);
				oldPoint = *it;
			}

			std::vector<Vector2> spherePoints = sphere1.getPoints();
			oldPoint = spherePoints[spherePoints.size() - 1];
			for (std::vector<Vector2>::iterator it = spherePoints.begin(); it != spherePoints.end(); ++it) {
				SDL_RenderDrawLine(renderer, oldPoint.x, oldPoint.y, it->x, it->y);
				oldPoint = *it;
			}

			polygon1.rotate(polygon1.getRotation() - 1);
			std::vector<Vector2> polygonPoints = polygon1.getPoints();
			oldPoint = polygonPoints[polygonPoints.size() - 1];
			for (std::vector<Vector2>::iterator it = polygonPoints.begin(); it != polygonPoints.end(); ++it) {
				SDL_RenderDrawLine(renderer, oldPoint.x, oldPoint.y, it->x, it->y);
				oldPoint = *it;
			}
			SDL_RenderPresent(renderer);
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