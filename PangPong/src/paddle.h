#ifndef _PANGPONG_PADDLE_H_
#define _PANGPONG_PADDLE_H_

#include <SDL.h>

class Paddle
{
public:
	Paddle(int x, int y);
	~Paddle();

	int GetX() const;
	int GetY() const;

	void SetX(const int x);
	void SetY(const int y);

	void Update();
	void Render(SDL_Renderer * renderer);

public:
	static const int PADDLE_WIDTH;
	static const int PADDLE_HEIGHT;

private:
	int x_, y_;
	SDL_Rect paddle;
};

#endif
