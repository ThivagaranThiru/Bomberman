#include "game.h"

void init_screen_menu(t_sdl* mapSDL) {
	SDL_SetRenderDrawColor(mapSDL->screen_renderer, 0, 0, 0, 255);
	SDL_RenderClear(mapSDL->screen_renderer);
	SDL_RenderCopy(mapSDL->screen_renderer, mapSDL->background, NULL,
	NULL);
	SDL_Surface *surface;
	SDL_Color color = { 255, 255, 255 };
	SDL_Rect first_pos = { 225, 150, 270, 50 };

	SDL_Rect second_pos = { 225, 250, 270, 50 };

	if ((surface = TTF_RenderUTF8_Solid(mapSDL->font, "Client", color))) {
		SDL_RenderCopy(mapSDL->screen_renderer,
				SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
						surface), NULL, &first_pos);
		SDL_FreeSurface(surface);
	}
	if ((surface = TTF_RenderUTF8_Solid(mapSDL->font, "Serveur", color))) {
		SDL_RenderCopy(mapSDL->screen_renderer,
				SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
						surface), NULL, &second_pos);
		SDL_FreeSurface(surface);
	}

	SDL_RenderPresent(mapSDL->screen_renderer);

}

int menu_input() {
	SDL_Event e;
	int y;
	int x;
	int value = 0;
	while (value == 0) {
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				x = e.motion.x;
				y = e.motion.y;
				if (e.button.button == SDL_BUTTON_LEFT) {
					if (x >= 200 && x <= 500 && y >= 20 && y <= 200) {
						puts("Client");
						value = 2;
					} else if (x >= 200 && x <= 500 && y >= 250 && y <= 400) {
						puts("Serveur");
						value = 1;
					}
				}
			}
		}
	}
	return value;
}

SDL_Texture* load_image(char* name, SDL_Renderer* renderer) {
	SDL_Surface *surface = IMG_Load(name);
	if (surface != NULL) {
		return SDL_CreateTextureFromSurface(renderer, surface);
	}
	return NULL;
}

void print_salle_attente(t_sdl *mapSDL,int nbClient){

	SDL_SetRenderDrawColor(mapSDL->screen_renderer, 0, 0, 0, 255);
	SDL_RenderClear(mapSDL->screen_renderer);
	SDL_RenderCopy(mapSDL->screen_renderer, mapSDL->background, NULL,
	NULL);

	/*SDL_Surface *surface;
	SDL_Color color = { 255, 255, 255 };
	SDL_Rect first_pos = { 225, 50, 270, 50 };
	SDL_Rect second_pos = { 225, 150, 270, 50 };
	SDL_Rect third_pos = { 225, 250, 270, 50 };
	SDL_Rect fourth_pos = { 225, 350, 270, 50 };

	int k;

	for(k = 0; k < nbClient; k++){
		switch ((k+1)) {
			case 1:
				if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
						"Player 1 here", color))) {
					SDL_RenderCopy(mapSDL->screen_renderer,
							SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
									surface), NULL, &first_pos);
					SDL_FreeSurface(surface);
				}
				break;
			case 2:
				if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
						"Player 2 here", color))) {
					SDL_RenderCopy(mapSDL->screen_renderer,
							SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
									surface), NULL, &second_pos);
					SDL_FreeSurface(surface);
				}
				break;
			case 3:
				if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
						"Player 3 here", color))) {
					SDL_RenderCopy(mapSDL->screen_renderer,
							SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
									surface), NULL, &third_pos);
					SDL_FreeSurface(surface);
				}
				break;
			case 4:
				if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
						"Player 4 here", color))) {
					SDL_RenderCopy(mapSDL->screen_renderer,
							SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
									surface), NULL, &fourth_pos);
					SDL_FreeSurface(surface);
				}
				break;
		}
	}*/

	SDL_RenderPresent(mapSDL->screen_renderer);
}


t_sdl *init_mapSDL(){
	t_sdl *mapSDL = NULL;
	mapSDL = malloc(sizeof(t_sdl));

	if (mapSDL != NULL) {
		mapSDL->screen_size.x = MAXY * BLOCK;
		mapSDL->screen_size.y = MAXX * BLOCK;

		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			fprintf(stderr, "Error in SDL_INIT_VIDEO %s\n", SDL_GetError());
		}

		if (TTF_Init() == -1) {
			fprintf(stderr, "Error in TTF_INIT %s\n", TTF_GetError());
		} else {
			mapSDL->font = TTF_OpenFont("resources/arial.ttf", 18);
		}
	}

	mapSDL->screen_window = SDL_CreateWindow("Bomberman",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		MAXY * BLOCK, MAXX * BLOCK,
		SDL_WINDOW_SHOWN);;

		if (mapSDL->screen_window != NULL) {
			mapSDL->screen_renderer = SDL_CreateRenderer(
			mapSDL->screen_window, -1, SDL_RENDERER_ACCELERATED);

			if (mapSDL->screen_renderer == NULL) {
				free_sdl(mapSDL);
			} else {
				mapSDL->background = load_image("resources/background.png",
						mapSDL->screen_renderer);
				mapSDL->player[0] = load_image("resources/p1.png",
						mapSDL->screen_renderer);
				mapSDL->player[1] = load_image("resources/p2.png",
						mapSDL->screen_renderer);
				mapSDL->player[2] = load_image("resources/p3.png",
						mapSDL->screen_renderer);
				mapSDL->player[3] = load_image("resources/p4.png",
						mapSDL->screen_renderer);
				mapSDL->bomb = load_image("resources/bomb.png",
						mapSDL->screen_renderer);
				mapSDL->textures = load_image("resources/wall.png",
						mapSDL->screen_renderer);
				mapSDL->fire = load_image("resources/fire.png",
						mapSDL->screen_renderer);
				mapSDL->bonus = load_image("resources/bonus.png",
						mapSDL->screen_renderer);
			}
		} else {
			free_sdl(mapSDL);
		}

		return mapSDL;
}

void free_sdl(t_sdl *mapSDL) {
	int i = 0;

	if (mapSDL != NULL) {
		if (mapSDL->background) {
			SDL_DestroyTexture(mapSDL->background);
		}
		for (i = 0; i < 4; i++) {
			if (mapSDL->player[i]) {
				SDL_DestroyTexture(mapSDL->player[i]);
			}
		}
		if (mapSDL->textures) {
			SDL_DestroyTexture(mapSDL->textures);
		}
		if (mapSDL->bomb) {
			SDL_DestroyTexture(mapSDL->bomb);
		}
		if (mapSDL->fire) {
			SDL_DestroyTexture(mapSDL->fire);
		}
		if (mapSDL->bonus) {
			SDL_DestroyTexture(mapSDL->bonus);
		}
		if (mapSDL->screen_renderer) {
			SDL_DestroyRenderer(mapSDL->screen_renderer);
		}
		if (mapSDL->screen_window) {
			SDL_DestroyWindow(mapSDL->screen_window);
		}

		free(mapSDL);
	}

	SDL_Quit();
	TTF_Quit();
}

void show_result(int player, t_sdl *mapSDL) {
	SDL_SetRenderDrawColor(mapSDL->screen_renderer, 0, 0, 0, 255);
	SDL_RenderClear(mapSDL->screen_renderer);
	SDL_RenderCopy(mapSDL->screen_renderer, mapSDL->background, NULL,
	NULL);

	SDL_Surface *surface;
	SDL_Color color = { 255, 255, 255 };
	SDL_Rect first_pos = { 225, 150, 270, 50 };
	SDL_Rect second_pos = { 225, 250, 270, 50 };

	switch (player) {
	case 1:
		if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
				"Player 1 win", color))) {
			SDL_RenderCopy(mapSDL->screen_renderer,
					SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
							surface), NULL, &first_pos);
			SDL_FreeSurface(surface);
		}
		break;
	case 2:
		if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
				"Player 2 win", color))) {
			SDL_RenderCopy(mapSDL->screen_renderer,
					SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
							surface), NULL, &first_pos);
			SDL_FreeSurface(surface);
		}
		break;
	case 3:
		if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
				"Player 3 win", color))) {
			SDL_RenderCopy(mapSDL->screen_renderer,
					SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
							surface), NULL, &first_pos);
			SDL_FreeSurface(surface);
		}
		break;
	case 4:
		if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
				"Player 4 win", color))) {
			SDL_RenderCopy(mapSDL->screen_renderer,
					SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
							surface), NULL, &first_pos);
			SDL_FreeSurface(surface);
		}
		break;
	default:
		if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
				"You lose !!!!", color))) {
			SDL_RenderCopy(mapSDL->screen_renderer,
					SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
							surface), NULL, &first_pos);
			SDL_FreeSurface(surface);
		}
	break;
	}

	if ((surface = TTF_RenderUTF8_Solid(mapSDL->font,
			"Enter Space to close", color))) {
		SDL_RenderCopy(mapSDL->screen_renderer,
				SDL_CreateTextureFromSurface(mapSDL->screen_renderer,
						surface), NULL, &second_pos);
		SDL_FreeSurface(surface);
	}

	SDL_RenderPresent(mapSDL->screen_renderer);
}

