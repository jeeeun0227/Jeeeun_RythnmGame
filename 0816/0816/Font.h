#pragma once

#include "SDL_ttf.h"
#include "Texture.h"

class Font : public Texture
{
public:
	Font(char *fileName, int fontsize);
	~Font();

public:
	void SetText(const char* text);

private:
	TTF_Font *_sansFont;
};