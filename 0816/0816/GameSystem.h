#pragma once

#include "SDL.h"

class GameSystem
{
	// Singleton
private:
	static GameSystem *_instance;		// 외부에서 접근 불가 메모리 생성
	
public:
	static GameSystem *GetInstance();		// 정적변수이기 때문에 어딘가에(?) 메모리 생성

private:
	GameSystem();		// 다른 곳에서 실수로 생성하지 않도록, 생성자를 프라이빗으로 만든다.
public:
	~GameSystem();

	// Window Info
public:
	int GetWindow_w();
	int GetWindow_h();

	void Quit();

	// GameInfo
private:
	int _gameTimeTick;
	int _trackHeight;

public:
	void SetGameTime(float sec);
	int GetGameTimeTick();
	void SetTrackHeight(int height);
	int GetTrackHeight();

private:
	SDL_Renderer *_sdlRender;

public:
	void Set_SDL_Renderer(SDL_Renderer *_sdlRender);
	SDL_Renderer *Get_SDL_Renderer();
};