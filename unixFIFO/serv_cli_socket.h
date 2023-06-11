


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netdb.h>
#define NMAX 10
#define PORT 1200


/*declaration of the question struct*/
struct questCli{
int pid_cli;
int n;
} ;
/*declaration of the response struct*/
struct repServ{
int pid_serv;
int res[NMAX];

} ;






