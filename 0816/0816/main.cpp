#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"		// = #include "../sdk/SDL/include/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "GameSystem.h"
#include "Sprite.h"
#include "Note.h"
// #include "GameScene.h"
// #include "TitleScene.h"
#include "SceneManager.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	if (TTF_Init() < 0)
	{
		printf("Error Init SDL Font\n");
	}
	atexit(TTF_Quit);

	int Window_h = GameSystem::GetInstance()->GetWindow_h();		//int Window_h = 1024;
	int Window_w = GameSystem::GetInstance()->GetWindow_w();		//int Window_w = 800;

	SDL_Window *sdlWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window_w, Window_h, SDL_WINDOW_OPENGL);
	SDL_Renderer *sdlRender = SDL_CreateRenderer(sdlWindow, 0, 0);
	GameSystem::GetInstance()->Set_SDL_Renderer(sdlRender);

	SDL_SetRenderDrawColor(GameSystem::GetInstance()->Get_SDL_Renderer(), 178, 235, 244, 255);		// 배경색 지정 -> 하늘색 배경

	/*
	TitleScene *Scene = new TitleScene();
	Scene->Init();
	*/

	SceneManager::GetInstance()->ChangeScene("Title");

	int Frame = 0;
	int Old_Frame = 0;
	int Current_Tick = SDL_GetTicks();
	int Old_Tick = Current_Tick;

	SDL_Event sdlEvent;
	while (1)		// ESC를 누르면 실행창을 나가는 Event
	{
		Current_Tick = SDL_GetTicks();

		Frame = (SDL_GetTicks() % 1000) * 60;		// 60frame
		Frame /= 1000;

		if (Old_Frame != Frame)
		{
			Old_Frame = Frame;

			int deltaTime = Current_Tick - Old_Tick;
			Old_Tick = Current_Tick;

			if (SDL_PollEvent(&sdlEvent))
			{
				if (SDL_QUIT == sdlEvent.type)
					break;

				if (SDL_KEYUP == sdlEvent.type)
				{
					if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_Event quitEvent;
						quitEvent.type = SDL_QUIT;
						SDL_PushEvent(&quitEvent);
					}

					// Scene->keyUp(sdlEvent.key.keysym.sym);
					SceneManager::GetInstance()->KeyUp(sdlEvent.key.keysym.sym);
				}

				if (SDL_KEYDOWN == sdlEvent.type)
				{
					// Scene->keyDown(sdlEvent.key.keysym.sym);
					SceneManager::GetInstance()->KeyDown(sdlEvent.key.keysym.sym);
				}
			}
			// Scene->Update(deltaTime);
			SceneManager::GetInstance()->Update(deltaTime);

			SDL_RenderClear(GameSystem::GetInstance()->Get_SDL_Renderer());
			{
				// Scene->Render();
				SceneManager::GetInstance()->Render();
			}
			SDL_RenderPresent(GameSystem::GetInstance()->Get_SDL_Renderer());
		}
	}

	//Scene->Deinit();
//	delete Scene;

	return 0;
}