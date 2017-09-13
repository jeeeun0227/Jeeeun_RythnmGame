#include <stdio.h>

#include "ResourceManager.h"
#include "GameSystem.h"

using namespace std;
// �ѹ��� �����ϸ� ������ Ÿ�������� �ʾƵ� �ȴ�.

// ������� ������ ���� ������� �ٽ� ��������߸�, �Ϲ� ��� ����ó�� ����� �� �ִ�.
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
