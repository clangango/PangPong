#include "helper.h"

#include <iostream>

#include <SDL_ttf.h>

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer,
	SDL_Rect dst, SDL_Rect* clip)
{
	SDL_RenderCopy(renderer, texture, clip, &dst);
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer,
	int x, int y, SDL_Rect* clip)
{
	SDL_Rect destR;
	destR.x = x;
	destR.y = y;
	if (clip != nullptr)
	{
		destR.w = clip->w;
		destR.h = clip->h;
	}
	else
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &destR.w, &destR.h);
	}
	renderTexture(texture, renderer, destR, clip);
}

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (!font)
	{
		std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
		// handle error
	}
	SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}