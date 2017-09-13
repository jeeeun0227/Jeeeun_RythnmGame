#pragma once

class Texture
{
public:
	Texture();
	Texture(const char *fileName);
	~Texture();

protected:
	SDL_Texture *_texture;

	SDL_Rect _srcRect;
	SDL_Rect _destRect;

public:
	void SetScale(float wScale, float hScale);
	void SetPosition(int x, int y);

	int GetRenderWidth();
	int GetRenderHeight();

	void Render();
};