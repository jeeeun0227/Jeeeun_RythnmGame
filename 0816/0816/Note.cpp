#include <stdio.h>

#include "GameSystem.h"
#include "Sprite.h"
#include "Note.h"

Note::Note(float sec, int JudgeDeltaLine)
{
	_sprite = NULL;
	_startTick = GameSystem::GetInstance()->GetGameTimeTick() - (int)(sec * 1000.0f);
	_JudgeDeltaLine = JudgeDeltaLine;
	_isPass = false;
}

Note::~Note()
{
	Deinit();
}

bool Note::_isLive()
{
	return isLive;
}

void Note::Init()
{
	_sprite = new Sprite("RythmGame.csv", true);
	_x = GameSystem::GetInstance()->GetWindow_w() / 2;

	int gameTimeTick = GameSystem::GetInstance()->GetGameTimeTick();

	_updateDuration = _startTick;
	isLive = true;

	UpdatePosition(0);
	_sprite->SetPosition(_x, _y);
}

void Note::Deinit()
{
	if (NULL != _sprite)
	{
		delete _sprite;
		_sprite = NULL;
	}
}

void Note::Update(int deltaTime)
{
	_sprite->Update(deltaTime);

	int totalMoveTick = GameSystem::GetInstance()->GetGameTimeTick();
	int totalHeight = GameSystem::GetInstance()->GetTrackHeight();

	UpdatePosition(deltaTime);
	
	_sprite->SetPosition(_x, _y);
}

void Note::Render()
{
	_sprite->Render();
}

void Note::UpdatePosition(int deltaTime)
{
	_updateDuration += deltaTime;
	if (_updateDuration <= GameSystem::GetInstance()->GetGameTimeTick()+1000)
	{
		int gameTimeTick = GameSystem::GetInstance()->GetGameTimeTick();
		int trackHeight = GameSystem::GetInstance()->GetTrackHeight();
		float postionRate = (float)_updateDuration / (float)gameTimeTick;
		float positionInSec = trackHeight * postionRate;
		_y = positionInSec - (trackHeight - GameSystem::GetInstance()->GetWindow_h() + _JudgeDeltaLine);
	}
	else
	{
		isLive = false;
	}
}

int Note::GetNoteTime()
{
	return _updateDuration;
}

bool Note::isPass()
{
	return _isPass;
}

void Note::Pass()
{
	_isPass = true;
}

void Note::SetPostionWidth(int w)
{
	_x = (GameSystem::GetInstance()->GetWindow_w() / 2) + w;
}