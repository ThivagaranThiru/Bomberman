 #include "game.h"

void move_possible_client(int input,t_client_request *newclientRequest,t_map *tabMap) {
	switch (input) {
		case (1):
			if(!(tabMap->tab[newclientRequest->x_pos - 1][newclientRequest->y_pos] >= 1 && tabMap->tab[newclientRequest->x_pos - 1][newclientRequest->y_pos] <= 4)
				&& tabMap->tab[newclientRequest->x_pos - 1][newclientRequest->y_pos] != -1 && tabMap->tab[newclientRequest->x_pos - 1][newclientRequest->y_pos] != -2
				&& tabMap->tab[newclientRequest->x_pos - 1][newclientRequest->y_pos] != 8) {
					newclientRequest->x_pos -= 1;
					newclientRequest->dir = 3;
			}
			break;
		case(2):
			if(!(tabMap->tab[newclientRequest->x_pos + 1][newclientRequest->y_pos] >= 1 && tabMap->tab[newclientRequest->x_pos + 1][newclientRequest->y_pos] <= 4)
				&& tabMap->tab[newclientRequest->x_pos + 1][newclientRequest->y_pos] != -1 && tabMap->tab[newclientRequest->x_pos + 1][newclientRequest->y_pos] != -2
				&& tabMap->tab[newclientRequest->x_pos + 1][newclientRequest->y_pos] != 8) {
					newclientRequest->x_pos += 1;
					newclientRequest->dir = 1;
			}
			break;
		case(3):
			if(!(tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos - 1] >= 1 && tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos - 1] <= 4)
				&& tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos-1] != -1 && tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos-1] != -2
				&& tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos-1] != 8) {
					newclientRequest->y_pos -= 1;
					newclientRequest->dir = 4;
			}
			break;
		case(4):
			if(!(tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos + 1] >= 1 && tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos + 1] <= 4)
				&& tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos+1] != -1 && tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos+1] != -2
				&& tabMap->tab[newclientRequest->x_pos][newclientRequest->y_pos+1] != 8) {
				newclientRequest->y_pos += 1;
				newclientRequest->dir = 2;
			}
			break;
		case (5):
			tabMap = init_bomb(newclientRequest->magic, tabMap,newclientRequest);
			break;
	}
}

int wait_action(int wait_time) {
	clock_t start = clock();
	clock_t after = clock();
	int current_time = 0;

	while (current_time < wait_time) {
		after = clock() - start;
		current_time = after * 1000 / CLOCKS_PER_SEC;
	}

	return current_time;
}

void update_map(t_game *game,t_map *tabMap){
	int i,j,k;
	for(k = 0; k < game->infos.nbClient; k++){
		for (i = 0; i < MAXX; i++) {
			for (j = 0; j < MAXY; j++) {
				if(tabMap->tab[i][j] == (k + 1)){
					tabMap->tab[i][j] = 0;
				}
			}
		}

		if(game->player_infos[k].alive == 'L'){
			tabMap->tab[game->player_infos[k].x_pos][game->player_infos[k].y_pos] = (k + 1);

			if(game->player_infos[k].x_bomb != 0 && game->player_infos[k].y_bomb != 0
					&& tabMap->tab[game->player_infos[k].x_bomb][game->player_infos[k].y_bomb] != 9
					&& tabMap->tab[game->player_infos[k].x_bomb][game->player_infos[k].y_bomb] != 10
					&& tabMap->tab[game->player_infos[k].x_bomb][game->player_infos[k].y_bomb] != 11){

					tabMap->tab[game->player_infos[k].x_bomb][game->player_infos[k].y_bomb] = 8;
			}
		}
	}
}

t_game* kill_player(t_map* tabMap,t_game* game,t_client_request *newclientRequest) {
	int x;
	int y;
	int i;

	for (x = 0; x < MAXX; x++) {
		for (y = 0; y < MAXY; y++) {
			for (i = 0; i < 4; i++) {
				int posX = game->player_infos[i].x_pos;
				int posY = game->player_infos[i].y_pos;

				if (tabMap->tab[posX][posY] == 11 && x == posX && y == posY && newclientRequest->magic == i) newclientRequest->live = 0;
			}
		}
	}

	return game;
}

int winner(t_map* tabMap) {
	int x;
	int y;
	int count = 0;
	int countBomb = 0;
	int res = -1;

	for (x = 0; x < MAXX; x++) {
		for (y = 0; y < MAXY; y++) {
			if (tabMap->tab[x][y] == 1 || tabMap->tab[x][y] == 2
					|| tabMap->tab[x][y] == 3 || tabMap->tab[x][y] == 4) {
				count++;
			} else if (tabMap->tab[x][y] == 8 || tabMap->tab[x][y] == 9
					|| tabMap->tab[x][y] == 10) {
				countBomb++;
			}
		}
	}

	if (count == 1 && countBomb == 0) {
		for (x = 0; x < MAXX; x++) {
			for (y = 0; y < MAXY; y++) {
				if (tabMap->tab[x][y] == 1 || tabMap->tab[x][y] == 2
						|| tabMap->tab[x][y] == 3
						|| tabMap->tab[x][y] == 4) {
					res = tabMap->tab[x][y];
					return res;
				}
			}
		}
	}

	return res;
}
