#pragma once

#include "Scene.h"
#include "Array.h"

class Track;
class Sprite;
class Font;

struct SDL_Texture;

class GameScene : public Scene
{
private:
	Sprite *_BackgroundSprite;

	Array<Track*>* _trackList;

	int _gameDuration;

	int Score;

public:
	GameScene();
	~GameScene();

	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();

	void keyDown(int keycode);
	void keyUp(int keycode);

private:
	SDL_Texture *texture;
	Font *_textFont;
};