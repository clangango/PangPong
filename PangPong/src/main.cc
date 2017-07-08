#include <iostream>

#include <SDL.h>

int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization error: " << SDL_GetError();
		return -1;
	}

	std::cout << "Hello World" << std::endl;
	std::cin.get();

	return 0;
}