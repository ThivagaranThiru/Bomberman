/*
 * player.c
 *
 *  Created on: 8 mai 2019
 *      Author: quentin
 */

#include "game.h"

t_game* init_players(t_game* game) {
	int i;
	for (i = 0; i < 4; i++) {
		t_player_infos player = { 1, 1, 1, 1, 1, 1,0,0};
		game->player_infos[i] = init_player(i, player);
	}

	return game;
}

t_player_infos init_player(int joueur, t_player_infos player) {
	switch (joueur) {
	case 0:
		player.connected = 'N';
		player.alive = 'D';
		player.x_pos = 2;
		player.y_pos = 2;
		break;
	case 1:
		player.connected = 'N';
		player.alive = 'D';
		player.x_pos = MAXX - 3;
		player.y_pos = 2;
		break;
	case 2:
		player.connected = 'N';
		player.alive = 'D';
		player.x_pos = 2;
		player.y_pos = MAXY - 3;
		break;
	case 3:
		player.connected = 'N';
		player.alive = 'D';
		player.x_pos = MAXX - 3;
		player.y_pos = MAXY - 3;
		break;
	}
	return player;
}

t_client_request *init_clientRequest(t_client_request *clientRequest,t_game *game){

	switch(game->infos.nbClient - 1){
		case 0 :
			clientRequest->magic = 0;
			clientRequest->x_pos = game->player_infos[0].x_pos;
			clientRequest->y_pos = game->player_infos[0].y_pos;
			clientRequest->dir = game->player_infos[0].current_dir;
			clientRequest->speed = game->player_infos[0].current_speed;
			clientRequest->x_bomb = game->player_infos[0].x_bomb;
			clientRequest->y_bomb = game->player_infos[0].y_bomb;
			if(game->player_infos[0].alive == 'L') clientRequest->live = 1;
			break;
		case 1 :
			clientRequest->magic = 1;
			clientRequest->x_pos = game->player_infos[1].x_pos;
			clientRequest->y_pos = game->player_infos[1].y_pos;
			clientRequest->dir = game->player_infos[1].current_dir;
			clientRequest->speed = game->player_infos[1].current_speed;
			clientRequest->x_bomb = game->player_infos[1].x_bomb;
			clientRequest->y_bomb = game->player_infos[1].y_bomb;
			if(game->player_infos[1].alive == 'L') clientRequest->live = 1;
			break;
		case 2 :
			clientRequest->magic = 2;
			clientRequest->x_pos = game->player_infos[2].x_pos;
			clientRequest->y_pos = game->player_infos[2].y_pos;;
			clientRequest->dir = game->player_infos[2].current_dir;
			clientRequest->speed = game->player_infos[2].current_speed;
			clientRequest->x_bomb = game->player_infos[2].x_bomb;
			clientRequest->y_bomb = game->player_infos[2].y_bomb;
			if(game->player_infos[2].alive == 'L') clientRequest->live = 1;
			break;
		case 3 :
			clientRequest->magic = 3;
			clientRequest->x_pos = game->player_infos[3].x_pos;
			clientRequest->y_pos = game->player_infos[3].y_pos;
			clientRequest->dir = game->player_infos[3].current_dir;
			clientRequest->speed = game->player_infos[3].current_speed;
			clientRequest->x_bomb = game->player_infos[3].x_bomb;
			clientRequest->y_bomb = game->player_infos[3].y_bomb;
			if(game->player_infos[3].alive == 'L') clientRequest->live = 1;
			break;
	}

	return clientRequest;
}


