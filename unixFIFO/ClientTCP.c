#include "serv_cli_socket.h"

main(){
/* Déclarations */
int d_question , d_reponse ;
int i ;
int socket_client;
struct sockaddr_in serverAddr;
struct questCli question ;
struct repServ reponse ;

printf ("\t\tMon PID --> %d\n",getpid());

/* Création  socket */
socket_client = socket (AF_INET, SOCK_STREAM, 0);
if (socket_client == -1){
     printf ("Impossible de créer un socket");
     exit(1);
	}
printf("Socket serveur créé\n");

/* Préparez la structure sockaddr_in ** assign IP, PORT*/
memset(&serverAddr, '\0', sizeof(serverAddr));
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(PORT);
serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

//connexion
	if(connect(socket_client, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Connected to Server.\n");


/* Construction et envoi d’une question */
srand(getpid());
question.pid_cli = getpid();
question.n = 1 + rand()%NMAX ;

write( socket_client ,&question , sizeof (struct questCli));

/* Attente de la réponse */
printf("\t\t Client en attente de la reponse \n");


/* Lecture de la réponse */
read ( socket_client  , &reponse , sizeof( struct repServ ) );




/* Traitement local de la réponse */
printf ("\t\tQuestion: %d\n", question.n );
printf("\t\t*******************\n");
 printf("\t\tRéponse: \n");
for ( i =0; i < question.n ; i ++)
printf (" %d | ", reponse.res [i]);
printf ("\n\t");
exit (0);
close (socket_client);
}
