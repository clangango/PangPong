#include "game.h"

#include <iostream>

#include "helper.h"
#include "config.h"

Game::Game()
{
	running_ = Init();

	computer_ = new Paddle(40, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);

	player_ = new Paddle(SCREEN_WIDTH - (40 + PADDLE_WIDTH), 
		SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);

	ball_ = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	mouse_y_ = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

	Reset();
}

Game::~Game()
{
	delete player_;
	delete computer_;
	delete ball_;

	SDL_DestroyTexture(font_player_score_);
	SDL_DestroyTexture(font_computer_score_);

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();

	font_player_score_ = nullptr;
	font_computer_score_ = nullptr;

	ball_ = nullptr;
	player_ = nullptr;
	computer_ = nullptr;

	renderer_ = nullptr;
	window_ = nullptr;
}

bool Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization error: " << SDL_GetError();
		return false;
	}

	window_ = SDL_CreateWindow("Pang Pong", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window_ == NULL)
	{
		std::cout << "Window creation error: " << SDL_GetError();
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	if (renderer_ == NULL)
	{
		std::cout << "Renderer creation error: " << SDL_GetError();
		return false;
	}

	if (SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255) < 0)
	{
		std::cout << "Error setting render draw color: " << SDL_GetError();
		return false;
	}

	SDL_ShowCursor(SDL_DISABLE);

	if (TTF_Init() < 0)
	{
		std::cout << "Font initialization error: " << TTF_GetError();
		return false;
	}

	font_color_ = { 255, 0, 0, 255 };
	font_name_ = "assets/fonts/Roboto-Black.ttf";

	return true;
}

void Game::Run()
{
	while (running_)
	{
		HandleEvents();
		Update();
		Render();
		SDL_Delay(1000 / 60);
	}
}

void Game::HandleEvents()
{
	while (SDL_PollEvent(&event_))
	{
		switch (event_.type)
		{
		case SDL_QUIT:
			running_ = false;
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(NULL, &mouse_y_);
			break;
		case SDL_KEYDOWN:
			if (event_.key.keysym.sym == SDLK_SPACE)
				if (ball_->state_ == Ball::READY || ball_->state_ == Ball::GAMEOVER)
					ball_->state_ = Ball::LAUNCH;
		}
	}
}

void Game::Update()
{
	player_->SetY(mouse_y_);
	computer_->AI(ball_);
	ball_->Update();

	ball_->CheckWallCollision(0, SCREEN_HEIGHT);

	if (ball_->PaddleCollision(player_))
	{
		ball_->BouncesOff(player_);
	}
	else if (ball_->PaddleCollision(computer_))
	{
		ball_->BouncesOff(computer_);
	}
	ball_->predicted_y_ = computer_->Predict(ball_);

	if (ball_->x_ < 0)
	{
		player_score_++;
		player_score_changed_ = true;
		ball_->Reset(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}

	if (ball_->x_ > SCREEN_WIDTH - Ball::BALL_SIZE)
	{
		computer_score_++;
		computer_score_changed_ = true;
		ball_->Reset(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer_);

	// drawing of the game in here
	RenderNet();
	player_->Render(renderer_);
	computer_->Render(renderer_);
	ball_->Render(renderer_);


	if (player_score_changed_)
	{
		font_player_score_ = renderText(std::to_string(player_score_), font_name_, font_color_, 24, renderer_);
		player_score_changed_ = false;
	}
	renderTexture(font_player_score_, renderer_, SCREEN_WIDTH - 60, 20);

	if (computer_score_changed_)
	{
		font_computer_score_ = renderText(std::to_string(computer_score_), font_name_, font_color_, 24, renderer_);
		computer_score_changed_ = false;
	}
	renderTexture(font_computer_score_, renderer_, 50, 20);


	SDL_RenderPresent(renderer_);
}

void Game::Reset()
{
	player_score_ = 0;
	computer_score_ = 0;

	player_score_changed_ = true;
	computer_score_changed_ = true;
}

void Game::RenderNet()
{
	SDL_SetRenderDrawColor(renderer_, 127, 127, 127, 255);
	for (int i = 0; i < SCREEN_HEIGHT; i += 15)
	{
		SDL_Rect dot = { SCREEN_WIDTH / 2 - 3, i, 6, 6 };
		SDL_RenderFillRect(renderer_, &dot);
	}
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
}
