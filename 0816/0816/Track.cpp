#include <stdio.h>
#include <stdlib.h>

#include "Note.h"
#include "Sprite.h"
#include "Track.h"
#include "GameSystem.h"
#include "GameScene.h"

Track::Track()
{
	_isKeyDown = false;
	_isJudge = eJudge::None;
}

Track::~Track()
{

}

void Track::Init()
{
	int JudgeDeltaLine = 200;

	Sprite* _JudgeLineSprite = new Sprite("track.csv", true);
	_JudgeLineSprite->SetPosition(GameSystem::GetInstance()->GetWindow_w() / 2, GameSystem::GetInstance()->GetWindow_h() / 2);
	_backgroundSpriteList.Append(_JudgeLineSprite);

	Sprite* _trackSprite = new Sprite("JudgeLine.csv", true);
	_trackSprite->SetPosition(GameSystem::GetInstance()->GetWindow_w() / 2, GameSystem::GetInstance()->GetWindow_h() - JudgeDeltaLine);
	_backgroundSpriteList.Append(_trackSprite);

	Sprite* _explosionSprite = new Sprite("explosion.csv", false);
	_explosionSprite->SetPosition(GameSystem::GetInstance()->GetWindow_w() / 2, GameSystem::GetInstance()->GetWindow_h() - JudgeDeltaLine);

	_effectList = new Array<Sprite*>(1);
	_effectList->Set(eEffext::EXPLOSION, _explosionSprite);


	int gameTime = GameSystem::GetInstance()->GetGameTimeTick();

	float deltaTick = 0;

	for (int noteTick = 0; noteTick < gameTime;)
	{
		int randValue = rand() % 3;
		switch (randValue)
		{
		case 0:
			deltaTick = 250;
			break;
		case 1:
			deltaTick = 500;
			break;
		case 2:
			deltaTick = 750;
			break;
		default:
			deltaTick = 1000;
		}

		noteTick += deltaTick;

		float sec = (float)noteTick / 1000.0f;

		Note* note = new Note(sec, JudgeDeltaLine);
		note->Init();
		_noteList.Append(note);
	}
	_score = NULL;
}

void Track::Deinit()
{
	DLinkedListItertator<Note*> itr = _noteList.GetIterator();
	{
		for (itr.Start(); itr.Valid(); itr.Forth())
		{
			itr.Item()->Deinit();
			delete itr.Item();
			_noteList.Remove(itr);
		}
	}

	DLinkedListItertator<Sprite*> backitr = _backgroundSpriteList.GetIterator();
	for (backitr.Start(); backitr.Valid(); backitr.Forth())
	{
		{
			delete backitr.Item();
		}
		_backgroundSpriteList.Remove(backitr);
	}
	if (NULL != _effectList->Get(eEffext::EXPLOSION))
	{
		delete _effectList->Get(eEffext::EXPLOSION);
	}
}

void Track::Update(int deltaTime)
{
	DLinkedListItertator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		if (itr.Item()->_isLive())
		{
			itr.Item()->Update(deltaTime);
		}
		else
		{
			delete itr.Item();
			_noteList.Remove(itr);
		}

		DLinkedListItertator<Sprite*> backitr = _backgroundSpriteList.GetIterator();
		for (backitr.Start(); backitr.Valid(); backitr.Forth())
		{
			backitr.Item()->Update(deltaTime);
		}

		// 노트 판정
		int JudgeTick = GameSystem::GetInstance()->GetGameTimeTick();
		_JudgeStartTick = JudgeTick - 100;
		_JudgeEndTick = JudgeTick + 100;

		if (_JudgeEndTick < itr.Item()->GetNoteTime() && false == itr.Item()->isPass())
		{
			itr.Item()->Pass();
			_isJudge = eJudge::Fail;
		}
	}
	_effectList->Get(eEffext::EXPLOSION)->Update(deltaTime);
}

void Track::Render()
{
	DLinkedListItertator<Sprite*> backitr = _backgroundSpriteList.GetIterator();
	for (backitr.Start(); backitr.Valid(); backitr.Forth())
	{
		backitr.Item()->Render();
	}

	DLinkedListItertator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.Item()->Render();
	}
	_effectList->Get(eEffext::EXPLOSION)->Render();
}

int Track::KeyDown()
{
	if (_isKeyDown)
		return _score;

	_isKeyDown = true;

	DLinkedListItertator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		if (itr.Item()->GetNoteTime() < _JudgeStartTick)
		{
			return _score;
		}

		if (_JudgeStartTick <= itr.Item()->GetNoteTime() && itr.Item()->GetNoteTime() <= _JudgeEndTick)
		{
			_isJudge = eJudge::Judge;
			break;
		}
	}

	switch (_isJudge)
	{
	case eJudge::Judge:
		_effectList->Get(eEffext::EXPLOSION)->Play();
		_score += 10;
		_noteList.Remove(itr);
		return _score;
	}
}

void Track::KeyUp()
{
	_isKeyDown = false;
}

void Track::SetTrackPosition(int setTrack)
{
	{
		DLinkedListItertator<Sprite*> itr = _backgroundSpriteList.GetIterator();

		itr.Start();
		int y = itr.Item()->GetY();
		itr.Item()->SetPosition(GameSystem::GetInstance()->GetWindow_w() / 2 + setTrack, y);

		itr.Forth();
		y = itr.Item()->GetY();
		itr.Item()->SetPosition(GameSystem::GetInstance()->GetWindow_w() / 2 + setTrack, y);
		
		y = _effectList->Get(0)->GetY();
		_effectList->Get(0)->SetPosition(GameSystem::GetInstance()->GetWindow_w() / 2 + setTrack, y);
	}
	
	DLinkedListItertator<Note*>  itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.Item()->SetPostionWidth(setTrack);
	}
}