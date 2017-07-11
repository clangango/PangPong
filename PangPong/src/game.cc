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

	if (font_game_over_)
		SDL_DestroyTexture(font_game_over_);

	SDL_DestroyTexture(font_launch_);
	SDL_DestroyTexture(font_player_score_);
	SDL_DestroyTexture(font_computer_score_);

	TTF_Quit();

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();

	font_game_over_ = nullptr;
	font_launch_ = nullptr;
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

	font_color_ = { 255, 0, 0, SDL_ALPHA_OPAQUE };
	font_name_ = "assets/fonts/Roboto-Black.ttf";

	font_launch_ = renderText("Press SPACE to start", font_name_, 
		font_color_, 16, renderer_);
	SDL_QueryTexture(font_launch_, NULL, NULL, &launch_w_, &launch_h_);

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
			if (event_.key.keysym.sym == SDLK_ESCAPE)
				running_ = false;
			if (event_.key.keysym.sym == SDLK_SPACE)
				if (ball_->state_ == Ball::READY)
					ball_->state_ = Ball::LAUNCH;
				if (ball_->state_ == Ball::GAMEOVER)
				{
					Reset();
					ball_->state_ = Ball::LAUNCH;
				}
		}
	}
}

void Game::Update()
{
	player_->Update(mouse_y_);
	computer_->AI(ball_);
	ball_->Update(player_, computer_);

	if (ball_->x_ < 0)
	{
		SDL_DestroyTexture(font_player_score_);
		font_player_score_ = ScoreTexture(++player_score_);
		ball_->Reset(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		if (player_score_ >= 5)
			GameOver("PLAYER");
	}

	if (ball_->x_ > SCREEN_WIDTH - Ball::BALL_SIZE)
	{
		SDL_DestroyTexture(font_computer_score_);
		font_computer_score_ = ScoreTexture(++computer_score_);
		ball_->Reset(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		if (computer_score_ >= 5)
			GameOver("COMPUTER");
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer_);

	// drawing of the game in here
	RenderNet();
	renderTexture(font_player_score_, renderer_, SCREEN_WIDTH - 60, 20);
	renderTexture(font_computer_score_, renderer_, 50, 20);

	player_->Render(renderer_);
	computer_->Render(renderer_);
	ball_->Render(renderer_);

	if (ball_->state_ == Ball::READY)
	{
		renderTexture(font_launch_, renderer_, SCREEN_WIDTH / 2 - launch_w_ / 2, 
			SCREEN_HEIGHT / 2 + (50 - launch_h_));
	}

	if (ball_->state_ == Ball::GAMEOVER)
	{
		renderTexture(font_game_over_, renderer_, 
			SCREEN_WIDTH / 2 - gameover_w_ / 2, SCREEN_HEIGHT / 2 - 50);
		renderTexture(font_launch_, renderer_, SCREEN_WIDTH / 2 - launch_w_ / 2,
			SCREEN_HEIGHT / 2 + (50 - launch_h_));
	}

	SDL_RenderPresent(renderer_);
}

void Game::Reset()
{
	player_score_ = 0;
	computer_score_ = 0;
	font_player_score_ = ScoreTexture(player_score_);
	font_computer_score_ = ScoreTexture(computer_score_);
}

void Game::RenderNet()
{
	SDL_SetRenderDrawColor(renderer_, 127, 127, 127, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < SCREEN_HEIGHT; i += 15)
	{
		SDL_Rect dot = { SCREEN_WIDTH / 2 - 3, i, 6, 6 };
		SDL_RenderFillRect(renderer_, &dot);
	}
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void Game::GameOver(std::string winner)
{
	font_game_over_ = renderText(winner + " Wins!", font_name_, font_color_, 16,
		renderer_);
	SDL_QueryTexture(font_game_over_, NULL, NULL, &gameover_w_, &gameover_h_);
	ball_->state_ = Ball::GAMEOVER;
}

SDL_Texture * Game::ScoreTexture(int score)
{
	SDL_Texture * score_texture = renderText(std::to_string(score), 
		font_name_, font_color_, 24, renderer_);
	return score_texture;
}
