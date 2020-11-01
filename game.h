/*
 * game.h
 *
 *  Created on: 4 mai 2019
 *      Author: quentin
 */

#ifndef GAME_H_
#define GAME_H_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sys/time.h>
#include <errno.h>

#define MAX_PLAYERS 4
#define MAXX 10
#define MAXY 15
#define BLOCK 50

typedef struct s_client_request {
	unsigned int magic;
	int x_pos;
	int y_pos;
	int dir;
	int speed;
	int ckecksum;
	int x_bomb;
	int y_bomb;
	int live;
} t_client_request;

typedef struct s_player_infos {
	char connected;
	char alive;
	int x_pos;
	int y_pos;
	int current_dir;
	int current_speed;
	int x_bomb;
	int y_bomb;
} t_player_infos;

typedef struct s_map {
	int** tab;
} t_map;

typedef struct s_sdl {
	SDL_Window* screen_window;
	SDL_Point screen_size;
	SDL_Renderer* screen_renderer;
	SDL_Texture* background;
	SDL_Texture* player[MAX_PLAYERS];
	SDL_Texture* textures;
	SDL_Texture* bomb;
	SDL_Texture* fire;
	SDL_Texture* bonus;
	TTF_Font* font;
}t_sdl;

typedef struct s_other {
	int nbClient;
	int tab[MAX_PLAYERS];
	int sock;
} t_other;

typedef struct s_game {
	t_player_infos player_infos[MAX_PLAYERS];
	t_other infos;
} t_game;

//INPUT
int input_sdl_ingame();

//CLIENT&SERVER
void *read_client(void *game);
void *server(void *game);
void *client (void *adresse);

//GAME
void move_possible_client(int input,t_client_request *newclientRequest,t_map *tabMap);
void update_map(t_game *game,t_map *tabMap);
int wait_action(int wait_time);
t_game* kill_player(t_map *tabMap,t_game* game,t_client_request *newclientRequest);
int winner(t_map* tabMap);

//PLAYER
t_game* init_players(t_game* game);
t_player_infos init_player(int joueur, t_player_infos player);
t_client_request *init_clientRequest(t_client_request *clientRequest,t_game *game);

//WINDOWS
void init_screen_menu(t_sdl* mapSDL);
int menu_input();
SDL_Texture* load_image(char* name, SDL_Renderer* renderer);
void print_salle_attente(t_sdl *mapSDL,int nbClient);
t_sdl *init_mapSDL();
void free_sdl(t_sdl *mapSDL);
void show_result(int player,t_sdl *mapSDL);

//MAP
t_map *init_mapTab();
void print_map_sdl(t_sdl *mapSdl, t_game *game,t_map *tabMap);
int print_player(t_sdl* mapSdl,t_game *game, int map, int height, int width);
int print_textures(t_sdl* mapSdl,t_game *game, int map, int height, int width, int destructible, SDL_Texture* texture);
int print_explode(t_sdl* mapSdl,t_game *game, int map, int height, int width);

//BOMBE
t_map* init_bomb(int player, t_map* tabMap,t_client_request * newclientRequest);
t_map* bomb_stat(int temps,t_map* tabMap,t_client_request * newclientRequest);
t_map* check_explode(t_map* tabMap, int moveToX, int moveToY);


#endif /* GAME_H_ */
