

// OpenGL headers
#include <GL/glew.h>
/*#include <GL/glu.h>
#include <GL/gl.h>*/

// SDL headers
#include <SDL_main.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <string>
#include "SquareMeshVbo.h"
#include "GameEngine.h"
#include "GameStateController.h"

using namespace std;
bool quit;
bool keyDown; 
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
const GLint WIDTH = SCREEN_WIDTH, HEIGHT = SCREEN_HEIGHT;
int currentFrame = 0, lastFrame = 0;

SDL_Window* window;
SDL_GLContext glContext;
SDL_Event sdlEvent;

GameEngine* engine = nullptr;
GameStateController* gameStateController = nullptr;
GameData* gameData = nullptr;

 
void GameLoop();
void KeyboardInputHandling();

int main(int argc, char* argv[])
{
 	quit = false;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Display error message
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			// Display error message
			cout << "Window could not be created! SDL_Error" << SDL_GetError() << endl;
			return false;
		}
		else
		{
			// Create OpenGL context
			glContext = SDL_GL_CreateContext(window);

			if (glContext == NULL)
			{
				// Display error message
				cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
				return false;
			}
			else
			{
				// Initialize glew
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << endl;
					return false;
				}
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
				}

				gameData = GameData::GetInstance();

				engine = GameEngine::GetInstance();
				engine->Init(WIDTH, HEIGHT);

				gameStateController = new GameStateController();
				gameStateController->Init(GameState::GS_LEVEL1);
			}
		}
	}

 	// Game loop
	while (GameData::GetInstance()->gGameStateCurr != GameState::GS_QUIT)
	{
		GameLoop(); 
	}

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}

void GameLoop() {

	if (GameData::GetInstance()->gGameStateCurr != GS_RESTART)
	{
		gameStateController->Update();
		gameStateController->currentLevel->LevelLoad();
	}
	else
	{
		GameData::GetInstance()->gGameStateNext =
			GameData::GetInstance()->gGameStateCurr = GameData::GetInstance()->gGameStatePrev;
	}


	// Initialize the gamestate
	gameStateController->currentLevel->LevelInit();

	while (GameData::GetInstance()->gGameStateCurr == GameData::GetInstance()->gGameStateNext)
	{
		currentFrame = SDL_GetTicks();

		GameEngine::GetInstance()->SetDeltaTime(currentFrame - lastFrame);

		KeyboardInputHandling (); 

		while (SDL_PollEvent(&sdlEvent) != 0)
		{
			// Esc button is pressed
			if (sdlEvent.type == SDL_QUIT)
			{
				GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT;
			}
			else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (sdlEvent.button.button = SDL_BUTTON_LEFT)
				{
					gameStateController->currentLevel->HandleMouse(0, sdlEvent.button.x, sdlEvent.button.y);
				}
			}
			else if (sdlEvent.type == SDL_KEYDOWN) //If event is keydown 
			{
 				
				if (!keyDown)
				{
					keyDown = true;
					switch (sdlEvent.key.keysym.sym)
					{
					/*case SDLK_LEFT:
					case SDLK_a:	gameStateController->currentLevel->HandleKey('a'); break;
					case SDLK_RIGHT:
					case SDLK_d:	gameStateController->currentLevel->HandleKey('d'); break;
					case SDLK_UP:
					case SDLK_w:	gameStateController->currentLevel->HandleKey('w'); break;
					case SDLK_DOWN:
					case SDLK_s:	gameStateController->currentLevel->HandleKey('s'); break;
					case SDLK_ESCAPE: gameStateController->currentLevel->HandleKey('q'); break;
					case SDLK_r: gameStateController->currentLevel->HandleKey('r'); break;*/
					case SDLK_e: gameStateController->currentLevel->HandleKey('e'); break;
					/*case SDLK_g: gameStateController->currentLevel->HandleKey('g'); break;
					case SDLK_z: gameStateController->currentLevel->HandleKey('z'); break;
					case SDLK_x: gameStateController->currentLevel->HandleKey('x'); break;
					case SDLK_f: gameStateController->currentLevel->HandleKey('f'); break;*/
					}
				}
			}
			else if (sdlEvent.type == SDL_KEYUP) {
				keyDown = false;
			}
		 
		}

		gameStateController->currentLevel->LevelUpdate();

		gameStateController->currentLevel->LevelDraw();
		SDL_GL_SwapWindow(window);

		lastFrame = currentFrame;
	}

	gameStateController->currentLevel->LevelFree();

	if (GameData::GetInstance()->gGameStateNext != GS_RESTART)
	{
		gameStateController->currentLevel->LevelUnload();
	}

	GameData::GetInstance()->gGameStatePrev = GameData::GetInstance()->gGameStateCurr;
	GameData::GetInstance()->gGameStateCurr = GameData::GetInstance()->gGameStateNext;
}

void KeyboardInputHandling() {
 	 
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		if (keyboardState[SDL_SCANCODE_A]) gameStateController->currentLevel->HandleKey('a');
		if (keyboardState[SDL_SCANCODE_D]) gameStateController->currentLevel->HandleKey('d');
		if (keyboardState[SDL_SCANCODE_W]) gameStateController->currentLevel->HandleKey('w');
		if (keyboardState[SDL_SCANCODE_S]) gameStateController->currentLevel->HandleKey('s');
		if (keyboardState[SDL_SCANCODE_Q]) gameStateController->currentLevel->HandleKey('q');
		if (keyboardState[SDL_SCANCODE_R]) gameStateController->currentLevel->HandleKey('r');
 		if (keyboardState[SDL_SCANCODE_G]) gameStateController->currentLevel->HandleKey('g');
		if (keyboardState[SDL_SCANCODE_Z]) gameStateController->currentLevel->HandleKey('z');
		if (keyboardState[SDL_SCANCODE_X]) gameStateController->currentLevel->HandleKey('x');
		if (keyboardState[SDL_SCANCODE_F]) gameStateController->currentLevel->HandleKey('f');
		if (keyboardState[SDL_SCANCODE_T]) gameStateController->currentLevel->HandleKey('t');
		if (keyboardState[SDL_SCANCODE_H]) gameStateController->currentLevel->HandleKey('h');
		if (keyboardState[SDL_SCANCODE_H]) gameStateController->currentLevel->HandleKey('n');


}
