#pragma once

#include "Gameobject.h"

class Scene : public GameObject
{
public:
	Scene();
	~Scene();

	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();

	// Input
public:
	virtual void keyDown(int keycode);
	virtual void keyUp(int keycode);
};