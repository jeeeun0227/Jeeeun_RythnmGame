#pragma once

#include "SDL.h"

class GameSystem
{
	// Singleton
private:
	static GameSystem *_instance;		// �ܺο��� ���� �Ұ� �޸� ����
	
public:
	static GameSystem *GetInstance();		// ���������̱� ������ ��򰡿�(?) �޸� ����

private:
	GameSystem();		// �ٸ� ������ �Ǽ��� �������� �ʵ���, �����ڸ� �����̺����� �����.
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