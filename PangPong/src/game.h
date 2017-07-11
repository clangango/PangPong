#ifndef _PANGPONG_GAME_H_
#define _PANGPONG_GAME_H_

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

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
	void GameOver(std::string winner);
	SDL_Texture * ScoreTexture(int score);


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

	std::string font_name_;

	SDL_Color font_color_;

	SDL_Texture * font_player_score_;
	SDL_Texture * font_computer_score_;
	SDL_Texture * font_launch_;
	SDL_Texture * font_game_over_;

	Mix_Chunk * sound_paddle_;
	Mix_Chunk * sound_wall_;
	Mix_Chunk * sound_score_;

	int launch_w_, launch_h_;
	int gameover_w_, gameover_h_;
};

#endif
