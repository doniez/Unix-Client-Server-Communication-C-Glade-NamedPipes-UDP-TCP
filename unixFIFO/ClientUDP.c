#include "serv_cli_socket.h"
// Driver code
int main() {

    struct questCli question ;
	struct repServ reponse ;
	int i ;
    int sockfd;
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    /* Construction et envoi d’une question */
	srand(getpid());
	question.pid_cli = getpid();
	question.n = 1 + rand()%NMAX ;

    sendto(sockfd, (char*) &question, sizeof(question),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));

    n = recvfrom(sockfd, (char*) &reponse, sizeof(reponse),
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    /* Traitement local de la réponse */
	printf ("\t\tQuestion: %d\n", question.n );
	printf("\t\t*******************\n");
	 printf("\t\tRéponse: \n");
	for ( i =0; i < question.n ; i ++)
	printf (" %d | ", reponse.res [i]);
	printf ("\n\t");
	exit (0);


    close(sockfd);
    return 0;
}
