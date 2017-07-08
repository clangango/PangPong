#include "paddle.h"

#include "game.h"
#include "ball.h"

const int Paddle::PADDLE_WIDTH = 10;
const int Paddle::PADDLE_HEIGHT = 60;

Paddle::Paddle(int x, int y)
	: x_(x), y_(y)
{
}

Paddle::~Paddle()
{
}

int Paddle::GetX() const
{
	return x_;
}

int Paddle::GetY() const
{
	return y_;
}

void Paddle::SetX(const int x)
{
	x_ = x;
}

void Paddle::SetY(const int y)
{
	y_ = y;

	if (y_ < 0)
		y_ = 0;
	if (y_ + Paddle::PADDLE_HEIGHT> Game::SCREEN_HEIGHT)
		y_ = Game::SCREEN_HEIGHT - PADDLE_HEIGHT;
}

void Paddle::Update()
{
}

void Paddle::Render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	paddle = { x_, y_, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_RenderFillRect(renderer, &paddle);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

int Paddle::Predict(Ball * ball)
{
	return 0;
}
