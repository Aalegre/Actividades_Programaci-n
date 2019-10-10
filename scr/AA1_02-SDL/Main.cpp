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

const SDL_Color BUTTON_ILDE{149,255,135,255};
const SDL_Color BUTTON_HOVER{222,255,208,255};
const SDL_Color BUTTON_CLICK{255,0,0,255};

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
	if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0) throw "No es pot inicializar Mix_Audio";

	Mix_Music* soundtrack{ Mix_LoadMUS("../../res/au/MonkeyIsland.mp3") };
	if (!soundtrack) throw "Unable to load Mix_music";
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_PlayMusic(soundtrack, -1);

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
	txtSurface = { TTF_RenderText_Blended(font, "Play", BUTTON_CLICK) };
	SDL_Texture* textPlayClick{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	SDL_Texture* textPlay = textPlayIlde;

	RigidBody2D playButtonRB({ SCREEN_WIDTH_CENTER, 100 }, { 40 * 4, 50 });
	SDL_Rect playButtonRect{ playButtonRB.getRenderPoint().x, playButtonRB.getRenderPoint().y, playButtonRB.getSize().x, playButtonRB.getSize().y };


	txtSurface = { TTF_RenderText_Blended(font, "Sound Off", BUTTON_ILDE) };
	SDL_Texture* textSoundOffIlde{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Sound Off", BUTTON_HOVER) };
	SDL_Texture* textSoundOffHover{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Sound Off", BUTTON_CLICK) };
	SDL_Texture* textSoundOffClick{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Sound On", BUTTON_ILDE) };
	SDL_Texture* textSoundOnIlde{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Sound On", BUTTON_HOVER) };
	SDL_Texture* textSoundOnHover{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Sound On", BUTTON_CLICK) };
	SDL_Texture* textSoundOnClick{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	SDL_Texture* textSound = textSoundOffIlde;

	RigidBody2D soundButtonRB({ SCREEN_WIDTH_CENTER, 200 }, { 40 * 8, 50 });
	SDL_Rect soundButtonRect{ soundButtonRB.getRenderPoint().x, soundButtonRB.getRenderPoint().y, soundButtonRB.getSize().x, soundButtonRB.getSize().y };

	txtSurface = { TTF_RenderText_Blended(font, "Exit", BUTTON_ILDE) };
	SDL_Texture* textExitIlde{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Exit", BUTTON_HOVER) };
	SDL_Texture* textExitHover{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	txtSurface = { TTF_RenderText_Blended(font, "Exit", BUTTON_CLICK) };
	SDL_Texture* textExitClick{ SDL_CreateTextureFromSurface(m_renderer, txtSurface) };
	SDL_Texture* textExit = textExitIlde;

	RigidBody2D exitButtonRB({ SCREEN_WIDTH_CENTER, 300 }, { 40 * 4, 50 });
	SDL_Rect exitButtonRect{ exitButtonRB.getRenderPoint().x, exitButtonRB.getRenderPoint().y, exitButtonRB.getSize().x, exitButtonRB.getSize().y };


	SDL_FreeSurface(txtSurface);
	TTF_CloseFont(font);

	// --- AUDIO ---

	// --- GAME LOOP ---
	SDL_Event event;

	//Input system
	InputSystem inputs;
	inputs["mousePos"] = new Input(AXIS, false, 10000);
	inputs["mouseClick"] = new Input(BUTTON, true);
	inputs["exit"] = new Input(BUTTON, true);
	inputs.resetAll();

	RigidBody2D cursor({ 0,0 }, {32,32});

	bool isRunning = true;
	bool sound = true;


	while (isRunning) {

		//////////
		//// EVENTS
		//////////
#pragma region EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				continue;
				break;
			case SDL_KEYDOWN:
				inputs["exit"].setInput(event.key.keysym.sym == SDLK_ESCAPE);
				break;
			case SDL_MOUSEMOTION:
				inputs["mousePos"].setInput({ float(event.motion.x), float(event.motion.y) });
				break;
			case SDL_MOUSEBUTTONDOWN:
				inputs["mouseClick"].setButtonDown();
				break;
			case SDL_MOUSEBUTTONUP:
				inputs["mouseClick"].setButtonUp();
				break;
			default:;
			}
		}
		inputs["mouseClick"].updateButton();
#pragma endregion EVENTS

		//////////
		//// UPDATE
		//////////
#pragma region UPDATE

		//CUSOR
		cursor.teleport(Interpolation::Exponential(cursor.getCenter(), inputs["mousePos"].getAxis(), 0.1f));
		playerRect.x = cursor.getRenderPoint().x;
		playerRect.y = cursor.getRenderPoint().y;

		//EXIT
		if (inputs["exit"].input()) {
			isRunning = false;
			continue;
		}

		///BUTTONS

		//PLAY
		if (playButtonRB.isInBoundaries(cursor.getCenter())) {
			if(inputs["mouseClick"].input())
				textPlay = textPlayClick;
			else
				textPlay = textPlayHover;
		}
		else {
			textPlay = textPlayIlde;
		}

		//SOUND
		if (soundButtonRB.isInBoundaries(cursor.getCenter())) {
			if (inputs["mouseClick"].inputUp()) {
				sound = !sound;
				if (sound) {
					Mix_ResumeMusic();
				}
				else {
					Mix_PauseMusic();
				}
			}
			if (sound) {
				if (inputs["mouseClick"].input()) {
					textSound = textSoundOnClick;
				}
				else {
					textSound = textSoundOnHover;
				}
			}
			else {
				if (inputs["mouseClick"].input()) {
					textSound = textSoundOffClick;
				}
				else {
					textSound = textSoundOffHover;
				}

			}
		}
		else {
			if (sound) {
				textSound = textSoundOnIlde;
			}
			else {
				textSound = textSoundOffIlde;
			}
		}

		//EXIT
		if (exitButtonRB.isInBoundaries(cursor.getCenter())) {
			if (inputs["mouseClick"].inputUp()) {
				isRunning = false;
				continue;
			}
			if (inputs["mouseClick"].input())
				textExit = textExitClick;
			else
				textExit = textExitHover;
		}
		else {
			textExit = textExitIlde;
		}
#pragma endregion UPDATE

		//////////
		//// DRAW
		//////////
#pragma region DRAW

		SDL_RenderClear(m_renderer);

		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

		SDL_RenderCopy(m_renderer, textPlay, nullptr, &playButtonRect);
		SDL_RenderCopy(m_renderer, textSound, nullptr, &soundButtonRect);
		SDL_RenderCopy(m_renderer, textExit, nullptr, &exitButtonRect);

		SDL_RenderCopy(m_renderer, cursorTexture, nullptr, &playerRect);

		//Background
		SDL_RenderPresent(m_renderer);

#pragma endregion DRAW

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(textPlayClick);
	SDL_DestroyTexture(textPlayHover);
	SDL_DestroyTexture(textPlayIlde);
	SDL_DestroyTexture(textPlay);
	SDL_DestroyTexture(textSoundOnClick);
	SDL_DestroyTexture(textSoundOnHover);
	SDL_DestroyTexture(textSoundOnIlde);
	SDL_DestroyTexture(textSoundOffClick);
	SDL_DestroyTexture(textSoundOffHover);
	SDL_DestroyTexture(textSoundOffIlde);
	SDL_DestroyTexture(textSound);
	SDL_DestroyTexture(textExitClick);
	SDL_DestroyTexture(textExitHover);
	SDL_DestroyTexture(textExitIlde);
	SDL_DestroyTexture(textExit);
	SDL_DestroyTexture(cursorTexture);
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}