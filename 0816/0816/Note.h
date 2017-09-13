#pragma once

#include "GameObject.h"

class Sprite;

class Note : public GameObject
{
private:
	int _updateDuration;
	int _x;
	int _y;
	int _startTick;
	
	bool isLive;

	int _JudgeDeltaLine;

public:
	Note(float sec, int JudgeDeltaLine);
	~Note();

	void Init();
	void Deinit();

	bool _isLive();

public:
	void Update(int deltaTime);
	void Render();

	void UpdatePosition(int deltaTime);
	int GetNoteTime();

	bool isPass();
	bool _isPass;

	void Pass();
	
	void Note::SetPostionWidth(int w);

	// Sprite
public:
	Sprite* _sprite;
};