#include "paddle.h"

#include "config.h"
#include "ball.h"

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
	if (y_ + PADDLE_HEIGHT > SCREEN_HEIGHT)
		y_ = SCREEN_HEIGHT - PADDLE_HEIGHT;
}

void Paddle::Update(const int mouse_y)
{
	SetY(mouse_y);
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
	float slope = 0.0f;
	if(ball->dx_ != 0)
		slope = static_cast<float>(ball->dy_ / ball->dx_);
	int paddle_distance = ball->x_ - x_;
	int predicted_y = abs(-slope * paddle_distance + ball->y_);
	int num_bounces = predicted_y / SCREEN_HEIGHT;

	if (num_bounces % 2 == 0)
		predicted_y = predicted_y % SCREEN_HEIGHT;
	else
		predicted_y = SCREEN_HEIGHT - (predicted_y % SCREEN_HEIGHT);

	return predicted_y;
}

void Paddle::AI(Ball * ball)
{
	if (ball->x_ < SCREEN_WIDTH / 2 && ball->dx_ < 0)
	{
		if (y_ + (PADDLE_HEIGHT - ball->BALL_SIZE) / 2 < Predict(ball) - 8)
			SetY(y_ += 5);
		else if (y_ + (PADDLE_HEIGHT - ball->BALL_SIZE) / 2 > Predict(ball) + 8)
			SetY(y_ -= 5);
	}
	else if (ball->dx_ >= 0)
	{
		if (y_ + PADDLE_HEIGHT / 2 < SCREEN_HEIGHT / 2)
			y_ += 1;
		else
			y_ -= 1;
	}
}
