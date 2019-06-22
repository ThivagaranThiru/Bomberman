/*
 * Client.c
 *
 *  Created on: 8 mai 2019
 *      Author: thiva
 */

#include "game.h"

void *client (void *adresse){

	int temps = 0;
	//char *adresseIP = (char*) adresse;
	int mysocket;
	struct sockaddr_in server;

	fd_set read;
	struct timeval time;

	t_sdl *map = NULL;
	t_map *tabMap = NULL;
	t_game *game = NULL;
	t_client_request *newclientRequest = NULL;

	game = malloc(sizeof(t_game));
	newclientRequest = malloc(sizeof(t_client_request));

	mysocket = socket(AF_INET, SOCK_STREAM,0);

	if(mysocket < 0){
		perror("socket()");
		return NULL;
	}

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);

	if(connect(mysocket,(struct sockaddr *)&server, sizeof(server)) < 0){
		perror("connect()");
		return NULL;
	}else {
		puts("newClient");
		newclientRequest->magic = -1;
		newclientRequest->ckecksum = mysocket;
	}

	map = init_mapSDL();
	tabMap = init_mapTab();

	while(1){

		time.tv_sec = 1;
		time.tv_usec = 0;

		FD_ZERO(&read);

		FD_SET(newclientRequest->ckecksum, &read);

		select(newclientRequest->ckecksum + 1, &read, NULL,NULL,&time);

		int input = input_sdl_ingame();

		if(input == - 1){
			free(tabMap->tab);
			free(tabMap);
			free(game);
			free(newclientRequest);
			//free(adresseIP);
			close(newclientRequest->ckecksum);
			free_sdl(map);
			return NULL;
		}

		if(input > 0) move_possible_client(input,newclientRequest,tabMap);
			
		if(FD_ISSET(newclientRequest->ckecksum,&read)){

			if(recv(newclientRequest->ckecksum, (char*) game,sizeof(t_game),0) > 0){

				if(newclientRequest->magic == -1 && game->infos.nbClient <= 4 && game->player_infos[game->infos.nbClient - 1].connected == 'C') newclientRequest = init_clientRequest(newclientRequest,game);

				if(game->infos.nbClient < 4){

					print_salle_attente(map,game->infos.nbClient);

				}else {

					update_map(game,tabMap);

					bomb_stat(temps,tabMap,newclientRequest);

					kill_player(tabMap,game,newclientRequest);

					print_map_sdl(map,game,tabMap);

					temps += wait_action(10);
				}

			}else{
				puts("Client disconnected");
				close(newclientRequest->ckecksum);
				return NULL;
			}

			if(send(newclientRequest->ckecksum, (char*) newclientRequest, sizeof(t_client_request),0) < 0){
				puts("server 1 disconnected");
				close(newclientRequest->ckecksum);
				return NULL;
			}
		}
	}

	close(newclientRequest->ckecksum);

	return 0;
}
