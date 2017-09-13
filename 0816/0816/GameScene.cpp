#include <stdio.h>
#include <string.h>

#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Sprite.h"
#include "Track.h"
#include "GameScene.h"
#include "GameSystem.h"
#include "Font.h"

GameScene::GameScene()
{
	_BackgroundSprite = NULL;
}
GameScene::~GameScene()
{

}

void GameScene::Init()
{
	_BackgroundSprite = new Sprite("Background.csv", true);
	_BackgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindow_w() / 2, GameSystem::GetInstance()->GetWindow_h() / 2);

	char filePath[256];
	sprintf(filePath, "../Resource/Gameplay.csv");
	FILE *fp = fopen(filePath, "r");
	if (NULL == fp)
	{
		printf("File Open Error %s\n", filePath);
	}

	char backgroundSpriteName[256];
	char musicSpriteName[256];
	float gameTimeMin;

	char buffer[1025];
	char *record = fgets(buffer, sizeof(buffer), fp);
	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		{
			char *token = strtok(record, "\n");
			if (!strcmp(token, "Background"))
			{
				token = strtok(NULL, "\n");
				strcpy(backgroundSpriteName, token);
			}

			else if (!strcmp(token, "MusicName"))
			{
				token = strtok(NULL, "\n");
				strcpy(musicSpriteName, token);
			}

			else if (!strcmp(token, "PlayTime"))
			{
				token = strtok(NULL, "\n");
				gameTimeMin = atof(token);
			}
		}
	}

	fclose(fp);

	int bpm = 120;
	int tempo = bpm / 60;

	float gametime = 50.0f;
	int trackHeight = GameSystem::GetInstance()->GetWindow_h() * (gametime*tempo);
	trackHeight /= 4.5;

	GameSystem::GetInstance()->SetGameTime(gametime);
	GameSystem::GetInstance()->SetTrackHeight(trackHeight);

	_trackList = new Array<Track*>(2);
	{
		Track * _track = new Track();
		_track->Init();
		_track->SetTrackPosition(-120);
		_trackList->Set(0, _track);
	}

	{
		Track * _track = new Track();
		_track->Init();
		_track->SetTrackPosition(120);
		_trackList->Set(1, _track);
	}

	_gameDuration = 0;

	_textFont = new Font("arialbd.ttf", 24);
	_textFont->SetPosition(100, 100);

	char text[256];
	Score = NULL;
	sprintf(text, "score: %d", Score);

	_textFont->SetText(text);
	_textFont->SetPosition(100, 100);

	int result = Mix_Init(MIX_INIT_MP3);
	if (MIX_INIT_MP3 == result)
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

		char musicfilePath[256];
		sprintf(musicfilePath, "../Resource/Music/Maroon 5 - Sugar (Audio).mp3", musicSpriteName);
		Mix_Music *music = Mix_LoadMUS(musicfilePath);


		if (NULL != music)
		{
			/*
			_textFont->SetText(text);
			_textFont->SetPosition(100, 100);
			*/

			Mix_PlayMusic(music, 0);
		}
		else
		{
			printf("Error Load Mp3!\n");
		}
	}
	else
	{
		printf("Error Init Mp3!\n");
	}
}

void GameScene::Deinit()
{
	for (int i = 0; i < _trackList->ReturnSize(); i++)
	{
		_trackList->Get(i)->Deinit();
		delete _trackList->Get(i);
	}

	if (NULL != _BackgroundSprite)
	{
		delete _BackgroundSprite;
		_BackgroundSprite = NULL;
	}
}

void GameScene::Update(int deltaTime)
{
	if (_gameDuration <= GameSystem::GetInstance()->GetGameTimeTick())
	{
		_BackgroundSprite->Update(deltaTime);

		for (int i = 0; i < _trackList->ReturnSize(); i++)
		{
			_trackList->Get(i)->Update(deltaTime);
		}

		_gameDuration += deltaTime;
	}
	else
	{
		GameSystem::GetInstance()->Quit();
	}
}

void GameScene::Render()
{
	_BackgroundSprite->Render();

	for (int i = 0; i < _trackList->ReturnSize(); i++)
	{
		_trackList->Get(i)->Render();
	}
	_textFont->Render();
}

void GameScene::keyDown(int keycode)
{
	switch (keycode)
	{
	case SDLK_LSHIFT:
		Score = _trackList->Get(0)->KeyDown();
		break;
	case SDLK_SPACE:
		Score = _trackList->Get(1)->KeyDown();
		break;
	default:
		break;
	}
	char text[256];
	sprintf(text, "score: %d", Score);

	_textFont->SetText(text);
	_textFont->SetPosition(100, 100);
}

void GameScene::keyUp(int keycode)
{
	switch (keycode)
	{
	case SDLK_LSHIFT:
		_trackList->Get(0)->KeyUp();
		break;
	case SDLK_SPACE:
		_trackList->Get(1)->KeyUp();
		break;
	default:
		break;
	}
}