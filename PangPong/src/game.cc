#include "game.h"

#include <iostream>

const int Game::SCREEN_WIDTH = 800;
const int Game::SCREEN_HEIGHT = 480;

Game::Game()
{
	running_ = Init();
	Reset();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();

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
		}
	}
}

void Game::Update()
{

}

void Game::Render()
{
	SDL_RenderClear(renderer_);

	// drawing of the game in here

	SDL_RenderPresent(renderer_);
}

void Game::Reset()
{
	player_score_ = 0;
	computer_score_ = 0;

	player_score_changed_ = true;
	computer_score_changed_ = true;
}