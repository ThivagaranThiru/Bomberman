#include "game.h"

int input_sdl_ingame() {
	SDL_Event e;
	int input = 0;

	if (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			input = -1;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				input = 1;
				break;
			case SDLK_DOWN:
				input = 2;
				break;
			case SDLK_LEFT:
				input = 3;
				break;
			case SDLK_RIGHT:
				input = 4;
				break;
			case SDLK_SPACE:
				input = 5;
				break;
			default:
				input = 0;
				break;
			}
		}
	}

	return input;
}
