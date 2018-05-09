#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>
#include "mercenary.h"
#include "map.h"
#include "entity.h"
#include "villager.h"

#define PORT 4242
#define BUFFER_SIZE 2048
#define VILLAGER_MAX 30

// create elements of the game
Map map;
Entity sphinx;
Entity oedipe;
Entity Thebes;
Mercenary tab_Mercenary[6];
Villager tab_Villager[30];
int my_mercenary;
int game_start;
// create the functions of the mercenary

// function move
char* deplacer(){
	char x[50];
	char y[50];
	printf("Introduire les coordonnées x et y");
	fgets(x,50,stdin);
	char *pos=strchr(x,'\n');
   	pos='\0';
	sleep(0);
	fgets(y,50,stdin);
	pos=strchr(y,'\n');
    	pos='\0';

	char* action= "mercenary move ";
	strcat(action,x);
	strcat(action," ");
	strcat(action,y);
	return action;
}

//function take villager
char* prendre(){
	return "mercenary carry";
}

//function drop villager
char* deposer(){
	return "mercenary drop";
}

//function ask sphynx
char* interoger(){
	return "mercenary ask";
}

//function answer sphynx
char* repondre(){
  	char buf[512];
	printf("Introduire le reponse pour le Sphynx");
	fgets(buf, sizeof(512), stdin);
	char *pos=strchr(buf,'\n');
    	pos='\0';
	char* result = "mercenary answer ";
	strcat(result,buf);
	return result;
}

//function steal a villager from another mercenary
char* voler(){
	char x[50];
	char y[50];
	printf("Introduire les coordonnées x et y du villageois à voler");
	fgets(x,50,stdin);
	char *pos=strchr(x,'\n');
   	pos='\0';
	sleep(0);
	fgets(y,50,stdin);
	pos=strchr(x,'\n');
    	pos='\0';
	char* result= "mercenary steal ";
	strcat(result,x);
	strcat(result," ");
	strcat(result,y);
	return result;

}

// function concerning all the possibilities that the user can pick for its mercenary
// manual mode
void game_moves(int sock){
    while (game_start == 1){
      int intention;
      printf("Que voulez-vous faire?\n1 pour se deplacer\n2 pour prendre un villageois\n3 pour deposer un villageois\n4 pour interoger le sphinx\n5 pour repondre au sphinx\n6 pour voler un villageois\n");
      scanf("%d",&intention);
      const char* action;
      char* buffer;
      if(intention==1) {
        action=deplacer();
        strcpy(buffer,action);
      }else if(intention==2){
        action=prendre();
        strcpy(buffer,action);
      }else if(intention==3){
        action=deposer();
        strcpy(buffer, action);
      }else if(intention==4){
        action=interoger();
        strcpy(buffer, action);
      }else if(intention==5){
        action=repondre();
        strcpy(buffer, action);
      }else if(intention==6){
        action=voler();
        strcpy(buffer, action);
      }
      send(sock, buffer, sizeof(buffer), 0);
    }
}

//function to listen to the server and save information received
void * ecoute(void *csocks) {

  char **argv = NULL;
  argv = malloc(sizeof(char *) * 8);
  char msg_recv[2048] = "";
  char *p = NULL;
  size_t i = 0;
  int csock = *((int*)csocks);

  argv = malloc(sizeof(char *) * 8);

  // transform the message received in an array of characters which contains arguments
  while(recv(csock, msg_recv, sizeof(msg_recv), 0) > 0){
    printf("Message recu : %s\n",msg_recv);

    p = strtok(msg_recv, " ");
    while(p != NULL){
      if(i < 8)
      {
         argv[i] = malloc(sizeof(char) * (1+strlen(p)));
         strcpy(argv[i], p);
         i++;
      }
      else
         break;
      p = strtok(NULL, " ");
    }
    argv[i] = NULL;

    //if we receive the "game start" command
    if(strcmp(argv[0],"game") == 0){
      // start the game
      if(strcmp(argv[1],"start") == 0){
				printf("game move stage\n");
        game_start = 1;
        game_moves(csock);
      }

      // itialisation of the map
      if(strcmp(argv[1],"map") == 0){
        init_map(&map, argv[2]);
				print_map(&map);
      }

      if(strcmp(argv[1],"score") == 0){
        int idMercenary = atof(argv[2]);
        int idVillager = atof(argv[3]);

      }

    }

    //instruction for mercenary
    if(strcmp(argv[0],"mercenary") == 0){
      int id = atof(argv[1]);

      //change position
      // if he is already carrying a villager ? change position too
      if(strcmp(argv[2],"position") == 0){
        int x = atof(argv[3]);;
        int y = atof(argv[4]);
        int oldX = get_CoordX_M(&tab_Mercenary[id]);
        int oldY = get_CoordY_M(&tab_Mercenary[id]);
        //change in tab
        change_position_M(&tab_Mercenary[id],x,y);
        // change in the map
        set_Case(&map,oldX,oldY,'G');
        set_Case(&map,x,y,'M');
				print_map(&map);
      }

      if(strcmp(argv[2],"dead") == 0){
        set_Status_M(&tab_Mercenary[id],"dead");
      }

      if(strcmp(argv[2],"carry") == 0){
        // check if he is already carrying a villager ?
        int idVillager = atof(argv[3]);
        set_Villager_M(&tab_Mercenary[id],idVillager);
        set_carried(&tab_Villager[idVillager],id);
      }

      if(strcmp(argv[2],"drop") == 0){
        int idVillager = atof(argv[3]);
        set_Villager_M(&tab_Mercenary[id],-1);
        set_carried(&tab_Villager[idVillager],-1);
        // change value in the map
      }

      if(strcmp(argv[2],"question") == 0){

      }

    }

    //instructions concerning oedipe
    if(strcmp(argv[0],"oedipe") == 0){

      if(strcmp(argv[1],"position") == 0){
        int x = atof(argv[2]);;
        int y = atof(argv[3]);
        int oldX = get_CoordX_E(&oedipe);
        int oldY = get_CoordY_E(&oedipe);
        // change in the Entity
        change_position_E(&oedipe,x,y);
        set_Case(&map,oldX,oldY,'G');
        set_Case(&map,x,y,'O');
      }

      if(strcmp(argv[1],"dead") == 0){

      }

    }

    //instructions concerning villagers
    if(strcmp(argv[0],"villager") == 0){
      int id = atof(argv[1]);
      int x = atof(argv[2]);
      int y = atof(argv[3]);
      change_position_V(&tab_Villager[id],x,y);
    }

    //instructions concerning the sphynx
    if(strcmp(argv[0],"sphinx") == 0){

      //when the sphynx ask a mercenary a question
      if(strcmp(argv[2],"ask") == 0){
        int id = atof(argv[1]);
        set_Status_M(&tab_Mercenary[id], "ask");
      }

      //if the mercenary succeds in responding and gets prized
      if(strcmp(argv[2],"succes") == 0){
        int id = atof(argv[1]);
        set_Status_M(&tab_Mercenary[id], "free");
      }

      //when the mercenary fails to respond and gets trapped
      if(strcmp(argv[2],"jail") == 0){
        int id = atof(argv[1]);
        set_Status_M(&tab_Mercenary[id], "jail");
      }

      //when the timeout runs out and the mercenary is released
      if(strcmp(argv[2],"release") == 0){
        int id = atof(argv[1]);
        int x = atof(argv[3]);
        int y = atof(argv[4]);
        set_Status_M(&tab_Mercenary[id], "free");
        change_position_V(&tab_Villager[id],x,y);
        // when you release a mercenary, can you choose the place ?
      }
    }
  }
    // free memory
    free(argv);

    // close the socket
    close(csock);
    return EXIT_SUCCESS;
}

//main
int main(void) {

  //Buffer
  char buffer[BUFFER_SIZE];
  int sock;
  int csock;
  struct sockaddr_in sin;

  pthread_t thread;

  /* Création de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration de la connexion */
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);

  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d vers serveur\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));
  /*if the connection succeds, we start listening to the server
    to act accordingly to the data received*/
  if(connect >= 0){
  	strcpy(buffer,"connect mercenary 2");
  	int connection = send(sock, buffer, sizeof(buffer), 0);
  	recv(sock, buffer, sizeof(buffer), 0);
  	my_mercenary = atof(buffer);
  	printf("Votre numero de mercenaire est le %d\n",my_mercenary);

    int* ptr_socket = malloc(sizeof(int));
    *ptr_socket = sock;

  //création thread écoute//
 	  pthread_create(&thread,NULL,ecoute, ptr_socket);
  /* Fermeture de la socket client */
    while(1){
      sleep(1);
    }
  close(sock);

  return EXIT_SUCCESS;

  }
}
