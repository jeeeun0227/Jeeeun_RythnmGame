#include <stdio.h>

#include "ResourceManager.h"
#include "GameSystem.h"

using namespace std;
// 한번만 선언하면 여러번 타이핑하지 않아도 된다.

// 헤더에서 선언한 정적 멤버들을 다시 선언해줘야만, 일반 멤버 변수처럼 사용할 수 있다.
ResourceManager *ResourceManager::instance = NULL;

// Singleton
ResourceManager *ResourceManager::GetInstance()
{
	if (instance == NULL)
		instance = new ResourceManager();
	return instance;
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	map<string, SDL_Texture*>::iterator it;
	for(it = _textureMap.begin(); it != _textureMap.end(); it++)
	{
		delete it->second;
	}
	_textureMap.clear();
}

SDL_Texture *ResourceManager::FindTexture(string filePath)
{
	map<string, SDL_Texture*>::iterator it = _textureMap.find(filePath);
	if (it != _textureMap.end())
	{
		return it->second;
	}

	SDL_Texture *_texture = IMG_LoadTexture(GameSystem::GetInstance()->Get_SDL_Renderer(), filePath.c_str());
	_textureMap[filePath] = _texture;
	return _texture;
}
