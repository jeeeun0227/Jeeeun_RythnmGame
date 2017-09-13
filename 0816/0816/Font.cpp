#include "SDL_ttf.h"

#include <stdio.h>

#include "GameSystem.h"
#include "Font.h"


Font::Font(char *fileName, int fontsize)
{
	char filePath[256];
	sprintf(filePath, "../Resource/Font/%s", fileName);

	_sansFont = TTF_OpenFont(filePath, 24);
}

Font::~Font()
{

}

void Font::SetText(const char* text)
{
	SDL_Color black = { 0,0,0 };
	SDL_Surface *surfaceMassage = TTF_RenderText_Solid(_sansFont, text, black);
	_texture = SDL_CreateTextureFromSurface(GameSystem::GetInstance()->Get_SDL_Renderer(), surfaceMassage);

	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);

	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.w = _srcRect.w;
	_destRect.h = _srcRect.h;
}