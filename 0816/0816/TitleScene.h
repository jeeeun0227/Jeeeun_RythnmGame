#pragma once

#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();
};