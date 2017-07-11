#include "ball.h"

#include <cmath>
#include <random>

#include "config.h"
#include "game.h"
#include "paddle.h"

namespace {
	std::random_device rd;
	std::mt19937 gen(rd());
}

const int Ball::BALL_SIZE = 15;

Ball::Ball(int x, int y)
	: x_(x), y_(y)
{
	speed_ = 8;
	Reset(x, y);
}

Ball::~Ball()
{
}

void Ball::Launch()
{
	std::uniform_int_distribution<int> dir(0, 1);
	int direction = 1 - 2 * dir(gen) % 2;

	std::uniform_int_distribution<int> ang(-60, 60);
	angle_ = ang(gen);

	dx_ = direction * speed_ * std::cos(angle_ * M_PI / 180.0f);
	dy_ = speed_ * std::sin(angle_ * M_PI / 180.0f);

	state_ = LAUNCHED;
}

void Ball::UpdateSpeed()
{
	if (hits_ == 5)
	{
		speed_++;
		hits_ = 0;
	}
}

void Ball::CheckWallCollision(int min, int max)
{
	if ((y_ + dy_) < min || (y_ + BALL_SIZE + dy_) >= max)
		dy_ = -dy_;
}

bool Ball::PaddleCollision(Paddle * paddle)
{
	if (paddle->GetX() < SCREEN_WIDTH / 2)
		return x_ < paddle->GetX() + PADDLE_WIDTH
		&& x_ + BALL_SIZE > paddle->GetX()
		&& y_ > paddle->GetY() - BALL_SIZE
		&& y_ < paddle->GetY() + PADDLE_HEIGHT;
	else
		return x_ + BALL_SIZE > paddle->GetX()
		&& x_ < paddle->GetX() + PADDLE_WIDTH
		&& y_ > paddle->GetY() - BALL_SIZE
		&& y_ < paddle->GetY() + PADDLE_HEIGHT;
}

void Ball::BouncesOff(Paddle * paddle)
{
	hits_++;
	int sign = x_ < SCREEN_WIDTH / 2 ? 1 : -1;
	int relY = y_ - paddle->GetY() + BALL_SIZE;
	angle_ = 1.5f * relY - 75.0f;
	dx_ = sign * speed_ * std::cos(angle_ * M_PI / 180.0f);
	dy_ = speed_ * std::sin(angle_ * M_PI / 180.0f);
}

void Ball::Reset(int x, int y)
{
	state_ = READY;
	speed_ = 8;
	hits_ = 0;
	angle_ = 0.0f;
	x_ = x - BALL_SIZE / 2;
	y_ = y - BALL_SIZE / 2;
	dx_ = 0;
	dy_ = 0;
	bounce_ = false;
}

void Ball::Update()
{
	
	if (state_ == LAUNCH)
	{
		Launch();
	}

	UpdateSpeed();
	CheckWallCollision(0, SCREEN_HEIGHT);

	x_ += dx_;
	y_ += dy_;
}

void Ball::Render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 244, 238, 66, 255);
	ball = { x_, y_, BALL_SIZE, BALL_SIZE };
	SDL_RenderFillRect(renderer, &ball);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
