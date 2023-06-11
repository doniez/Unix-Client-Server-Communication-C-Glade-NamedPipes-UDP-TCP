#include "serv_cli_socket.h"

// Driver code
int main() {
    int sockfd;
    int i;
	pid_t pidFils ;
	struct questCli question ;
	struct repServ reponse ;
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);  //len is value/result

while(1){


    n = recvfrom(sockfd, (char*) &question, sizeof(question),
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);


    /* construction de la réponse */
	for(i=0; i<question.n; i++)
	 reponse.res[i]= rand()%NMAX;

    sendto(sockfd, (char*) &reponse, sizeof(reponse),
    MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);



}
}
