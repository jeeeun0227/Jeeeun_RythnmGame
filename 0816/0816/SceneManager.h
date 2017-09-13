#pragma once

#include "Scene.h"

class SceneManager
{
	//Singleton Pattern
private:
	static SceneManager *_instance;

public:
	static SceneManager *GetInstance();

private:
	SceneManager();

public:
	~SceneManager();

private:
	Scene *_scene;

public:
	void ChangeScene(const char *SceneName);
	
	void Update(int deltaTime);
	void Render();

	void KeyUp(int keycode);
	void KeyDown(int keycode);
};