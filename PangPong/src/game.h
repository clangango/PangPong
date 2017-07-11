#ifndef _PANGPONG_GAME_H_
#define _PANGPONG_GAME_H_

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "paddle.h"
#include "ball.h"

class Game
{
public:
	Game();
	~Game();

	bool Init();

	void Run();
	void HandleEvents();
	void Update();
	void Render();
	void Reset();

private:
	void RenderNet();

private:
	SDL_Event event_;
	SDL_Window * window_;
	SDL_Renderer * renderer_;

	Ball * ball_;
	Paddle * player_;
	Paddle * computer_;

	int mouse_y_;
	int player_score_;
	int computer_score_;

	bool running_;
	bool player_score_changed_;
	bool computer_score_changed_;

	std::string font_name_;

	SDL_Color font_color_;
	SDL_Texture * font_player_score_;
	SDL_Texture * font_computer_score_;
};

#endif
