# Bomberman


Le projet consiste en la réalisation d'un clone du célèbre bomberman multijoueurs en réseau.

Le projet permert  d'héberger une partie, et d'y participer et de se connecter à une partie distante. Le principe est que le joueur manipule un personnage se déplaçant sur une carte en deux dimensions faite de murs plus ou moins destructibles (cela va du mur destructible en une/-deux/... explosion, explosions, jusqu’au mur indestructible). Le but pour chacun des joueurs est d’éliminer le joueur adverse en posant des bombes. Un joueur est éliminé quand il est pris dans le souffle d’une bombe. Une bombe met un certain temps à exploser.

Le projet est développer en C sous GNU/Linux avec les librairies suivantes : libC, Pthreads, Socket, Select, SDL, SDL_TTF, SDL_Image. Et elle possède un seul exécutable (client/serveur) .

Principe du jeu :

- Le client se connecte
- Le serveur lui envoie son numéro de joueur s'il accepte la connexion, sinon il répond que le serveur est plein puis déconnecte
- Le client/serveur envoie l'ordre de commencer la partie
- Le serveur renvoie les données du jeu, soit :
- Liste des joueurs connectés, score, positions sur la carte, état, Nombre de bombes, super pouvoir activé, direction, etc
- La carte (Position des bombes, des murs, des bonus, etc)
- Le client envoie sa volonté d'avancer à droite
- Le serveur renvoie les données du jeu en réponse
- Le client envoie sa volonté de poser un bombe
- Le serveur renvoie à nouveau les données du jeu
 Etc
 
Le projet est basé sur un protocole entièrement binaire (par opposition aux protocoles "textes"). Cela signifie que des structures de données seront directement échangées, plutôt que des commandes textuelles avec paramètres.
 
