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
	ResourceManager();		// 생성자
	~ResourceManager();		// 해지자

	// Singleton
private:
	// 다른 곳에서 실수로 생성하지 않도록, 생성자를 프라이빗으로 만든다.
	static ResourceManager *instance;
public:
	static ResourceManager *GetInstance();

private:
	std::map<std::string, SDL_Texture*> _textureMap;
	// std -> stl이 만든 NameSpace이다.
	// std::string -> key 값
	// string -> stl이 만든 문자열 자료형
	// SDL_Texture * _textureMap -> value 값

public:
	SDL_Texture *FindTexture(std::string filePath);
};