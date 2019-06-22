#include "game.h"

int main(int argc, const char * argv[]) {

	int n = 0;

	pthread_t thread_server;
	pthread_t thread_client;
	char *adresseIP = NULL;
	t_game *game = NULL;
	
	t_sdl *sdlmap = init_mapSDL();

	init_screen_menu(sdlmap);
	n = menu_input();
	free_sdl(sdlmap);

	if(n == 1){
		game = malloc(sizeof(t_game));
		game = init_players(game);

		if(pthread_create(&thread_server, NULL,server, (void*) game) < 0){
			puts("server not create in thread");
			return 1;
		}

		pthread_join(thread_server, NULL);

	}else{

		adresseIP = malloc(sizeof(char)* 10);

		if(pthread_create(&thread_client,NULL,client, (void*) adresseIP) < 0){
			puts("client not create in thread");
			return 1;
		}

		pthread_join(thread_client, NULL);
	}

	if(pthread_detach(thread_server) != 0) {
		puts("server thread");
		free(game);
		pthread_exit(&thread_server);
	}
	if(pthread_detach(thread_client) != 0){
		puts("client thread");
		free(adresseIP);
		pthread_exit(&thread_client);
	}

	return 0;
}
