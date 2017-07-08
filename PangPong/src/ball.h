#ifndef _PANGPONG_BALL_H_
#define _PANGPONG_BALL_H_

#include <SDL.h>

#include "paddle.h"

class Ball
{
public:
	Ball(int x, int y);
	~Ball();

	void Launch();
	void UpdateSpeed();
	void CheckWallCollision(int min, int max);
	bool PaddleCollision(Paddle * paddle);
	void BouncesOff(Paddle * paddle);
	void Reset(int x, int y);

	void Update();
	void Render(SDL_Renderer * renderer);

public:
	enum State { READY, LAUNCH, LAUNCHED, GAMEOVER };
	static const int BALL_SIZE;

	State state_;

	int x_;
	int y_;

	int dx_;
	int dy_;

	int speed_;
	int hits_;

	int predicted_y_;

	float angle_;

	bool bounce_;

private:
	SDL_Rect ball;
};

#endif
