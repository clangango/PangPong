#ifndef _PANGPONG_HELPER_H_
#define _PANGPONG_HELPER_H_

#include <SDL.h>
#include <string>

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect dst,
	SDL_Rect* clip = nullptr);

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y,
	SDL_Rect* clip = nullptr);

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, SDL_Renderer* renderer);

#endif
