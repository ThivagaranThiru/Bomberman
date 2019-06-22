#include "game.h"


t_map* init_bomb(int player,t_map* tabMap,t_client_request * newclientRequest)
{
	int xpos = newclientRequest->x_pos;
	int ypos = newclientRequest->y_pos;
	newclientRequest->x_bomb = xpos;
	newclientRequest->y_bomb = ypos;
	return tabMap;
}

t_map* check_explode(t_map* tabMap, int moveToX, int moveToY){
	if(tabMap->tab[moveToX][moveToY] != -1){
		tabMap->tab[moveToX][moveToY] = 11;
	}
	return tabMap;
}

t_map* bomb_stat(int temps,t_map* tabMap,t_client_request * newclientRequest){
	int i,y;
	for (i = 0; i < MAXX; i++) {
		for (y = 0; y < MAXY; y++) {
			if(tabMap->tab[i][y] == 8) {
				if (temps % 2000 == 0) {
					tabMap->tab[i][y] = 9;
					newclientRequest->x_bomb = 0;
					newclientRequest->y_bomb = 0;
				}
			}
			else if(tabMap->tab[i][y] == 9) {
				if (temps % 2000 == 0) {
					tabMap->tab[i][y] = 10;
				}
			} else if(tabMap->tab[i][y] == 10) {
				if (temps % 2000 == 0) {
					tabMap = check_explode(tabMap,i,y+1);
					tabMap = check_explode(tabMap,i,y-1);
					tabMap = check_explode(tabMap,i+1,y);
					tabMap = check_explode(tabMap,i-1,y);
					tabMap = check_explode(tabMap,i,y);
				}
			} else if(tabMap->tab[i][y] == 11) {
				if (temps % 3500 == 0) {
					tabMap->tab[i][y] = 0;
				}
			}
		}
	}
	return tabMap;
}

