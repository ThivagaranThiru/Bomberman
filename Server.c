/*
 * Server.c
 *
 *  Created on: 8 mai 2019
 *      Author: thiva
 */

#include "game.h"

void *read_client(void *game)
{

	t_game *jeu = (t_game*) game;
	t_client_request *client_request = NULL;
	client_request = malloc(sizeof(t_client_request));

	while(1){

		for(int j = 0; j < jeu->infos.nbClient; j++){

			if(send(jeu->infos.tab[j],(char*) jeu,sizeof(t_game),0) < 0){
				jeu->player_infos[j].connected = 'D';
				close(jeu->infos.tab[j]);

			}

			if(recv(jeu->infos.tab[j],(char*) client_request,sizeof(t_client_request),0) > 0){

				jeu->player_infos[client_request->magic].x_pos = client_request->x_pos;
				jeu->player_infos[client_request->magic].y_pos = client_request->y_pos;
				jeu->player_infos[client_request->magic].x_bomb = client_request->x_bomb;
				jeu->player_infos[client_request->magic].y_bomb = client_request->y_bomb;
				jeu->player_infos[client_request->magic].current_dir = client_request->dir;
				if(client_request->live == 0) jeu->player_infos[client_request->magic].alive = 'D';

			}else{
				jeu->player_infos[j].connected = 'D';
				close(jeu->infos.tab[j]);
			}
		}
	}

	free(game);
	free(client_request);

	return 0;
}

void *server(void *game){

	int mysock;
	int newClient;
	socklen_t client_addr_len;
	struct sockaddr_in server;
	struct sockaddr_in client;
	t_game *jeu = (t_game*) game;

	mysock = socket(AF_INET, SOCK_STREAM,0);

	if(mysock < 0){
		perror("socket()");
		return NULL;
	}

	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);

	if(bind(mysock,(struct sockaddr*)&server,sizeof(server)) < 0){
		perror("bind()");
		return NULL;
	}

	listen(mysock,4);
	puts("waiting clients ...");

	jeu->infos.sock = mysock;
	jeu->infos.nbClient = 0;

	while((newClient = accept(mysock,(struct sockaddr*)&client, &client_addr_len))){

		puts("Search Clients");

		if(jeu->infos.nbClient < 4 && newClient > 0){

			jeu->infos.tab[jeu->infos.nbClient] = newClient;
			jeu->player_infos[jeu->infos.nbClient].connected = 'C';
			jeu->player_infos[jeu->infos.nbClient].alive = 'L';
			jeu->infos.nbClient++;

			pthread_t newThread;

			if(pthread_create(&newThread, NULL, read_client, (void*) jeu) < 0) perror("Thread Server problem");

			if(pthread_detach(newThread)) pthread_exit(&newThread);

		}else{
			perror("accept()");
			puts("Too many Peoples");
			close(newClient);
		}
	}

	free(jeu);
	close(mysock);

	return 0;
}
