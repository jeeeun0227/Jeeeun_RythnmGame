#include <stdio.h>
#include <string.h>

#include "DLinkedList.h"
#include "GameSystem.h"
#include "Texture.h"
#include "Sprite.h"

// 생성자
Sprite::Sprite(const char *filename, bool isLoap)
{
	DoubleLinkedList<Texture*> LinkedList;

	char *textureName;
	float scaleWidth;
	float scaleHeight;

	char filePath[256];
	sprintf(filePath, "../Resource/%s", filename);
	
	FILE *fp = fopen(filePath, "r");

	if (NULL == fp)
	{
		printf("File Open Effor %s\n", filename);
	}

	char buffer[1024];

	char *record = fgets(buffer, sizeof(buffer), fp);

	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		{
			char *token = strtok(record, ",");
			textureName = token;

			token = strtok(NULL, ",");
			scaleWidth = atof(token);

			token = strtok(NULL, ",");
			scaleHeight = atof(token);
		}
			Texture *texture = new Texture(textureName);
			texture->SetScale(scaleWidth, scaleHeight);
			LinkedList.Append(texture);
	}

	fclose(fp);

	_FrameMaxCount = LinkedList.GetCount();
	_textureFrame = new Array <Texture*>(_FrameMaxCount);

	int frame = 0;
	DLinkedListItertator<Texture*> itr = LinkedList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		Texture* texture = itr.Item();
		_textureFrame->Set(frame, texture);
		frame++;
	}

	AniSpeed = 20000 / 60;
	FrameDuration = 0;
	_frame = 0;

	_isLoap = isLoap;
	if (_isLoap)
	{
		_isPlay = true;
	}
	else
	{
		_isPlay = false;
	}
}

// 해지자
Sprite::~Sprite()
{

}

void Sprite::Update(int deltaTime)
{
	if (false == _isPlay)
		return;

	FrameDuration += deltaTime;

	if (AniSpeed < FrameDuration)
	{
		FrameDuration = 0;
		_frame = (_frame + 1) % _FrameMaxCount;

		if (false == _isLoap)
		{
			if (0 == _frame)
			{
				_isPlay = false;
			}
		}
	}
		Texture *text = _textureFrame->Get(_frame);
		text->SetPosition(_x, _y);
}

void Sprite::Render()
{
	if (false == _isPlay)
		return;

	_textureFrame->Get(_frame)->Render();
}

void Sprite::SetPosition(int x, int y)
{
	_x = x;
	_y = y;

	Texture *texture = _textureFrame->Get(_frame);
	texture->SetPosition(_x, _y);
}

int Sprite::GetY()
{
	return _y;
}

void Sprite::Play()
{
	_frame = 0;
	_isPlay = true;
}