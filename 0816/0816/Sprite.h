#pragma once

#include "Array.h"

class Texture;

class Sprite
{
private:
	Array<Texture*> *_textureFrame;

	int _frame;
	int _FrameMaxCount = 2;

	int AniSpeed;
	int FrameDuration;
	
	int _x;
	int _y;

	bool _isLoap;
	bool _isPlay;

public:
	Sprite(const char *filename, bool isLoap);		// 생성자
	~Sprite();		//해지자

	void Update(int deltaTime);
	void Render();

	void SetPosition(int x, int y);
	int GetY();

	void Play();
};
