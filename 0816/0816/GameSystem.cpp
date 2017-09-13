#include <stdio.h>
#include "SDL.h"	
#include "GameSystem.h"

// ������� ������ ���� ������� �ٽ� ��������߸�, �Ϲ� ��� ����ó�� ����� �� �ִ�.
GameSystem *GameSystem::_instance = NULL;

GameSystem::GameSystem()
{

}

GameSystem::~GameSystem()
{

}

// Singleton
GameSystem *GameSystem::GetInstance()
{
	if (_instance == NULL)
		_instance = new GameSystem();
	return _instance;
}

int GameSystem::GetWindow_w()
{
	return 1024;
}

int GameSystem::GetWindow_h()
{
	return 800;
}

void  GameSystem::Quit()
{
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}

void GameSystem::SetGameTime(float sec)
{
	_gameTimeTick = (int)(sec * 1000.0f);
}

int GameSystem::GetGameTimeTick()
{
	return _gameTimeTick;
}

void GameSystem::SetTrackHeight(int height)
{
	_trackHeight = height;
}

int GameSystem::GetTrackHeight()
{
	return _trackHeight;
}

void GameSystem::Set_SDL_Renderer(SDL_Renderer* sdlRenderer)
{
	_sdlRender = sdlRenderer;
}

SDL_Renderer* GameSystem::Get_SDL_Renderer()
{
	return _sdlRender;
}