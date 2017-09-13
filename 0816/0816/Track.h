#pragma once

#include "DLinkedList.h"
#include "GameObject.h"

class Note;
class Sprite;

enum eJudge
{
	None,
	Judge,
	Fail
};

class Track : public GameObject
{
public:
	enum eEffext
	{
		EXPLOSION,
		FAIL
	};

private:
	DoubleLinkedList<Note*> _noteList;
	DoubleLinkedList<Sprite*> _backgroundSpriteList;
	
	Array<Sprite*>* _effectList;

	bool _isKeyDown;

	eJudge _isJudge;

	// �ߺ� �����丵�� ���� �������ȭ
	int _JudgeStartTick;
	int _JudgeEndTick;

	int _score;

public:
	Track();
	~Track();

	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();
	
	int KeyDown();
	void KeyUp();

	void Track::SetTrackPosition(int setTrack);
};