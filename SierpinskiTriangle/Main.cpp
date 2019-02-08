#include <SDL.h>
#include "SierpinskiTile.hpp"

#undef main // fixes error: no entry point defined

const int SCR_W = 1280;
const int SCR_H = 720;
const int TILE_W = 1;
const int TILE_H = 1;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;

bool quit = false;

SierpinskiTile *generator = NULL;

int main(int argc, char** args) {
	SDL_Init(SDL_INIT_VIDEO); 

	window = SDL_CreateWindow("Sierpinski-Triangle generator by D3PSI", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, SDL_WINDOW_SHOWN); 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	generator = new SierpinskiTile(SCR_W, SCR_H, TILE_W, TILE_H); 
	generator->setTile((SCR_W / TILE_W) / 2, 0); 

	int row = 0;
	while (!quit) {
		while (SDL_PollEvent(&event) > 0) 
			if (event.type == SDL_QUIT)
				quit = true;

		if (row < SCR_H / TILE_H)  {
			generator->draw(renderer, 255, 0, 0, row - 1);

			SDL_RenderPresent(renderer); 

			generator->calculate(row++);
		}
	}

	delete generator;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}