#include "game.h"

#include <iostream>

const int Game::SCREEN_WIDTH = 800;
const int Game::SCREEN_HEIGHT = 480;

Game::Game()
{
	running_ = Init();
	computer_ = new Paddle(40, SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2);
	player_ = new Paddle(SCREEN_WIDTH - (40 + Paddle::PADDLE_WIDTH), 
		SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2);
	mouse_y_ = SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2;
	Reset();
}

Game::~Game()
{
	delete player_;
	delete computer_;

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();

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

	return true;
}

void Game::Run()
{
	while (running_)
	{
		HandleEvents();
		Update();
		Render();
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
		}
	}
}

void Game::Update()
{
	player_->SetY(mouse_y_);
}

void Game::Render()
{
	SDL_RenderClear(renderer_);

	// drawing of the game in here
	RenderNet();
	player_->Render(renderer_);
	computer_->Render(renderer_);

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
