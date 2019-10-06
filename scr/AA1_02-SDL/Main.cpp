#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <exception>
#include <iostream>
#include <string>

#include "../../dep/inc/Aalegre/Interpolation.h"
#include "../../dep/inc/Aalegre/RigidBody2D.h"

//Game general information
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SCREEN_WIDTH_CENTER SCREEN_WIDTH/2
#define SCREEN_HEIGHT_CENTER SCREEN_HEIGHT/2

const SDL_Color BUTTON_ILDE{149,255,135,255};
const SDL_Color BUTTON_HOVER{222,255,208,255};
const SDL_Color BUTTON_CLICK{255,255,255,255};

int main(int, char* [])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window* m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer* m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() != 0) throw "No es pot inicializar SDL_ttf";
	//-->SDL_Mix

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bgCRT.jpg") };
	if (bgTexture == nullptr) throw "Error: Background init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_Texture* cursorTexture{ IMG_LoadTexture(m_renderer, "../../res/img/Cursor.png") };
	if (cursorTexture == nullptr) throw "Error: Cursor init";
	SDL_Rect playerRect{ 0,0,32,32 };

	//---Animated Sprite ---



	// --- TEXT ---
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/PressStart2P.ttf", 80) };
	if (font == nullptr) throw "No es pot inicializar PressStart2P";
	SDL_Surface* txtSurface{ TTF_RenderText_Blended(font, "Play", BUTTON_ILDE) };
	if (txtSurface == nullptr) throw "No es pot inicializar el Surface";
	SDL_Texture* textPlayIlde{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Play", BUTTON_HOVER) };
	SDL_Texture* textPlayHover{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };

	RigidBody2D playButtonRB({ SCREEN_WIDTH_CENTER, 100 }, { 40 * 4, 50 });
	SDL_Rect playButtonRect{ playButtonRB.getRenderPoint().x, playButtonRB.getRenderPoint().y, playButtonRB.getSize().x, playButtonRB.getSize().y };


	txtSurface = { TTF_RenderText_Blended(font, "Sound Off", BUTTON_ILDE) };
	SDL_Texture* textSoundOffIlde{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Sound Off", BUTTON_HOVER) };
	SDL_Texture* textSoundOffHover{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Sound On", BUTTON_ILDE) };
	SDL_Texture* textSoundOnIlde{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Sound On", BUTTON_HOVER) };
	SDL_Texture* textSoundOnHover{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };

	RigidBody2D soundButtonRB({ SCREEN_WIDTH_CENTER, 200 }, { 40 * 8, 50 });
	SDL_Rect soundButtonRect{ soundButtonRB.getRenderPoint().x, soundButtonRB.getRenderPoint().y, soundButtonRB.getSize().x, soundButtonRB.getSize().y };

	txtSurface = { TTF_RenderText_Blended(font, "Exit", BUTTON_ILDE) };
	SDL_Texture* textExitIlde{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Exit", BUTTON_HOVER) };
	SDL_Texture* textExitHover{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };

	RigidBody2D exitButtonRB({ SCREEN_WIDTH_CENTER, 300 }, { 40 * 4, 50 });
	SDL_Rect exitButtonRect{ exitButtonRB.getRenderPoint().x, exitButtonRB.getRenderPoint().y, exitButtonRB.getSize().x, exitButtonRB.getSize().y };


	SDL_FreeSurface(txtSurface);
	TTF_CloseFont(font);

	// --- AUDIO ---

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;

	bool sound = true;

	Vector2 mousePosition;
	RigidBody2D cursor({ 0,0 }, {32,32});

	bool playButtonHover = false;
	bool soundButtonHover = false;
	bool exitButtonHover = false;

	while (isRunning) {
		bool click = false;
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				mousePosition = { float(event.motion.x), float(event.motion.y) };
				break;
			case SDL_MOUSEBUTTONDOWN:
				click = true;
				break;
			default:;
			}
		}

		// UPDATE
		cursor.teleport(Interpolation::Exponential(cursor.getCenter(), mousePosition, 0.5f));
		playerRect.x = cursor.getRenderPoint().x;
		playerRect.y = cursor.getRenderPoint().y;

		playButtonHover = playButtonRB.isInBoundaries(cursor.getCenter());

		soundButtonHover = soundButtonRB.isInBoundaries(cursor.getCenter());
		if (soundButtonHover && click)
			sound = !sound;

		exitButtonHover = exitButtonRB.isInBoundaries(cursor.getCenter());
		if (exitButtonHover && click)
			isRunning = false;

		// DRAW
		SDL_RenderClear(m_renderer);

		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

		if (playButtonHover)
			SDL_RenderCopy(m_renderer, textPlayHover, nullptr, &playButtonRect);
		else
			SDL_RenderCopy(m_renderer, textPlayIlde, nullptr, &playButtonRect);

		if (sound)
			if (soundButtonHover)
				SDL_RenderCopy(m_renderer, textSoundOnHover, nullptr, &soundButtonRect);
			else
				SDL_RenderCopy(m_renderer, textSoundOnIlde, nullptr, &soundButtonRect);
		else
			if (soundButtonHover)
				SDL_RenderCopy(m_renderer, textSoundOffHover, nullptr, &soundButtonRect);
			else
				SDL_RenderCopy(m_renderer, textSoundOffIlde, nullptr, &soundButtonRect);

		if (exitButtonHover)
			SDL_RenderCopy(m_renderer, textExitHover, nullptr, &exitButtonRect);
		else
			SDL_RenderCopy(m_renderer, textExitIlde, nullptr, &exitButtonRect);


		SDL_RenderCopy(m_renderer, cursorTexture, nullptr, &playerRect);

		//Background
		SDL_RenderPresent(m_renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}