#include "game.h"


t_map *init_mapTab() {
	int i;
	int j;
	t_map *mapTab = NULL;
	mapTab = malloc(sizeof(t_map));

	int map1[MAXX][MAXY] = { { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1 }, { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 }, {
			-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 }, { -1, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, -1 }, { -1, 0, -2, -2, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, -1 }, { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 },
			{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 }, { -1, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, -1 }, { -1, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, -1 }, { -1, -1, -1, -1, -1, -1, -1, -1,
					-1, -1, -1, -1, -1, -1, -1 } };
	mapTab->tab = (int **) malloc(MAXX * sizeof(int *));
	for (i = 0; i < MAXX; i++)
		mapTab->tab[i] = (int *) malloc(MAXY * sizeof(int));

	for (i = 0; i < MAXX; i++) {
		for (j = 0; j < MAXY; j++) {
			mapTab->tab[i][j] = map1[i][j];
		}
	}

	return mapTab;
}

void print_map_sdl(t_sdl* mapSdl,t_game *game,t_map *tabMap) {
	int x;
	int y;

	SDL_SetRenderDrawColor(mapSdl->screen_renderer, 0, 0, 0, 255);
	SDL_RenderClear(mapSdl->screen_renderer);

	SDL_RenderCopy(mapSdl->screen_renderer, mapSdl->background, 0, 0);

	if (tabMap != NULL && tabMap->tab != NULL) {
		for (x = 0; x < MAXX; x++) {
			for (y = 0; y < MAXY; y++) {
				switch (tabMap->tab[x][y]) {
				case -2:

					print_textures(mapSdl,game, tabMap->tab[x][y], x, y, 1,
							mapSdl->textures);
					break;
				case -1:
					print_textures(mapSdl,game, tabMap->tab[x][y], x, y, 0,
							mapSdl->textures);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
					print_player(mapSdl,game, tabMap->tab[x][y], x, y);
					break;
				case 5:
					print_textures(mapSdl,game, tabMap->tab[x][y], x, y, 0,
							mapSdl->bomb);
					break;
				case 8:
					print_textures(mapSdl,game, tabMap->tab[x][y], x, y, 0,
							mapSdl->bomb);
					break;
				case 9:
					print_textures(mapSdl,game, tabMap->tab[x][y], x, y, 1,
							mapSdl->bomb);
					break;
				case 10:
					print_textures(mapSdl,game, tabMap->tab[x][y], x, y, 2,
							mapSdl->bomb);
					break;
				case 11:
					print_explode(mapSdl,game,tabMap->tab[x][y], x, y);
					break;
				default:
					break;
				}
			}
		}
	}

	SDL_RenderPresent(mapSdl->screen_renderer);
}
int print_textures(t_sdl* mapSdl,t_game *game, int map, int height, int width,
		int destructible, SDL_Texture* texture) {
	SDL_Rect sprite = { BLOCK * destructible, 0, BLOCK, BLOCK };
	SDL_Rect position = { width * BLOCK, height * BLOCK, BLOCK, BLOCK };

	if (map > 0 || map) {
		SDL_RenderCopy(mapSdl->screen_renderer, texture, &sprite,
				&position);
		return 1;
	}
	return 0;
}

int print_explode(t_sdl* mapSdl,t_game *game, int map, int height, int width) {
	SDL_Rect sprite = { 0, 0, BLOCK, BLOCK };
	SDL_Rect position = { width * BLOCK, height * BLOCK, BLOCK, BLOCK };

	if (map > 0) {
		SDL_RenderCopy(mapSdl->screen_renderer, mapSdl->fire, &sprite,
				&position);
		return 1;
	}
	return 0;
}

int print_player(t_sdl* mapSdl,t_game *game, int map, int height, int width) {
	int id = map - 1;
	int startSprite = 0;
	switch (game->player_infos[id].current_dir) {
	case 1:
		startSprite = 0;
		break;
	case 2:
		startSprite = BLOCK;
		break;
	case 3:
		startSprite = 3 * BLOCK;
		break;
	case 4:
		startSprite = 2 * BLOCK;
		break;
	}
	SDL_Rect sprite = { startSprite, 0, BLOCK, BLOCK };
	SDL_Rect position = { width * BLOCK, height * BLOCK, BLOCK, BLOCK };

	if (map > 0) {
		SDL_RenderCopy(mapSdl->screen_renderer, mapSdl->player[id],
				&sprite, &position);
		return 1;
	}
	return 0;
}
