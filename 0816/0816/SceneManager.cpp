#include <stdio.h>

#include "TitleScene.h"
#include "Scene.h"
#include "SceneManager.h"

// Singleton Pattern
SceneManager *SceneManager::_instance = NULL;

SceneManager *SceneManager::GetInstance()
{
	if (NULL == _instance)
		_instance = new SceneManager();
	return _instance;
}

SceneManager::SceneManager()
{
	_scene = NULL;		// ★ 멤버변수 생성자에서 초기화 ★
}

SceneManager::~SceneManager()
{
	if (NULL != _scene)
	{
		_scene->Deinit();
		delete _scene;
	}
}

void SceneManager::ChangeScene(const char *SceneName)
{
	if (NULL != _scene)
	{
		_scene->Deinit();
		delete _scene;
	}

	switch (scene)
	{
	case eScene::SCENE_TITLE:
		_scene = new TitleScene();
		_scene->Init();
		break;
	}
}

void SceneManager::Update(int deltaTime)
{

}

void SceneManager::Render()
{

}

void SceneManager::KeyUp(int keycode)
{

}

void SceneManager::KeyDown(int keycode)
{

}