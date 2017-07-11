#ifndef _PANGPONG_CONFIG_H_
#define _PANGPONG_CONFIG_H_

#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 520;

const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 60;

const int BALL_SIZE = 15;

const SDL_Color WHITE = { 255, 255, 255, SDL_ALPHA_OPAQUE };
const SDL_Color BLACK = { 0, 0, 0, SDL_ALPHA_OPAQUE };
const SDL_Color GRAY = { 127, 127, 127, SDL_ALPHA_OPAQUE };
const SDL_Color BALL_COLOR = { 244, 238, 66, SDL_ALPHA_OPAQUE };
const SDL_Color RED = { 255, 0, 0, SDL_ALPHA_OPAQUE };

#endif
