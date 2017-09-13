#pragma once

#include <iostream>
#include <map>
#include <String>

#include "SDL.h"
#include "SDL_image.h"

class SDL_Texture;

class ResourceManager
{
private:
	ResourceManager();		// ������
	~ResourceManager();		// ������

	// Singleton
private:
	// �ٸ� ������ �Ǽ��� �������� �ʵ���, �����ڸ� �����̺����� �����.
	static ResourceManager *instance;
public:
	static ResourceManager *GetInstance();

private:
	std::map<std::string, SDL_Texture*> _textureMap;
	// std -> stl�� ���� NameSpace�̴�.
	// std::string -> key ��
	// string -> stl�� ���� ���ڿ� �ڷ���
	// SDL_Texture * _textureMap -> value ��

public:
	SDL_Texture *FindTexture(std::string filePath);
};