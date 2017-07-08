#ifndef _PANGPONG_GAME_H_
#define _PANGPONG_GAME_H_

#include <SDL.h>

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

public:
	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;

private:
	SDL_Window * window_;
	SDL_Renderer * renderer_;

	SDL_Event event_;

	int player_score_;
	int computer_score_;

	bool player_score_changed_;
	bool computer_score_changed_;

	bool running_;
};

#endif
