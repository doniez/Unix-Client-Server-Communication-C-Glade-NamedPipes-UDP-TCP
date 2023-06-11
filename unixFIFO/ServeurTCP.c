#include "serv_cli_socket.h"

int main(void){
/*Déclarations */
int sig,i;
struct questCli question ; 
struct repServ reponse ;

int socket_server,newSocket;
struct sockaddr_in serverAddr,newAddr;
socklen_t addr_size=sizeof(newAddr);
pid_t pidFils ;


/* Création  socket */
socket_server = socket (AF_INET, SOCK_STREAM, 0);
if (socket_server == -1){
     printf ("Impossible de créer un socket");
     exit(1);
	}
printf("Socket serveur créé\n");

/* Préparez la structure sockaddr_in ** assign IP, PORT*/
memset(&serverAddr, '\0', sizeof(serverAddr));
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(PORT);
serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

/*Lier*/
 if ((bind(socket_server, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) != 0) { 

        printf("Échec de la liaison...\n"); 
        exit(0); 
    } 
printf("Socket successfully binded..\n");

//listen
if ((listen(socket_server, 5)) != 0) { 

        printf("Listen failed...\n"); 

        exit(1); 

    } 
printf("Server listening..\n"); 
		


/*initialisation du générateur de nombres aléatoires*/


reponse.pid_serv = getpid();



printf ("**** Serveur de PID --> %d à l'écoute ****\n",getpid());

while(1){
//accept
newSocket = accept(socket_server, (struct sockaddr*)&newAddr, &addr_size);
	if(newSocket < 0){
           printf("server accept failed...\n"); 
           exit(1);
           }
printf("server accept the client...\n"); 
//creation fils
pidFils = fork(); 

if(pidFils == 0)
{srand(getpid());
/* lecture d’une question */
read(newSocket, &question, sizeof(struct questCli));

/* construction de la réponse */
for(i=0; i<question.n; i++)
 reponse.res[i]= rand()%NMAX;

/* envoi de la réponse */
printf ("** Envoi de réponse au client de pid %d\n",question.pid_cli);
write (newSocket,&reponse , sizeof ( struct repServ ));

}else
  {close(newSocket);}


}
close(newSocket);
close(socket_server);
}
