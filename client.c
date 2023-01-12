#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"

int sd;

void exitHandler(int sig) {
    write(sd, SIG_CLIENT_EXIT, strlen(SIG_CLIENT_EXIT));

    // char *pid_str = malloc(5);
    // sprintf(pid_str, "%d", getpid());
    // remove(pid_str);
    exit(0);
}

int main(int argc, char *argv[]){
    if(argc < 3) {
        printf("Provide server address and port as a parameters\n");
        exit(1);
    }
    printf("connecting to %s:%s\n",argv[1],argv[2]);


    struct addrinfo hints, *results;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err;
    //         getaddrinfo(address,port,...)
    if ((err = getaddrinfo(argv[1], argv[2], &hints, &results)) != 0) {
        printf("error %d : %s\n", err, strerror(err));
        return 1;
    }

    int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    if(sd < 0){
        printf("%s\n",strerror(errno));
        exit(1);
    }

    if ( connect(sd, results->ai_addr, results->ai_addrlen) < 0) {
        printf("Failed to connect\n");
        exit(1);
    }

    //DO STUFF
    int n;
    char buff[1025];
    strcpy(buff, "Hello");

  	if(n = write(sd, buff, sizeof(buff)) <= 0){
  		printf("\n Write error \n");
      exit(1);
  	}
    for (;;) {

        // if(read(client_wkp, read_buff, MSG_SIZE) == -1) {
        //     printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
        // }

        // while (read(client_wkp, read_buff, MSG_SIZE) > 0) {
        //     printf("read from server> %s\n", read_buff);
        // }

        signal(SIGINT, exitHandler);

        // printf("before fgets...\n");
        fgets(buff, MSG_SIZE, stdin);
        int len = strlen(buff);
        buff[len-1] = '\0';

        write(sd, buff, MSG_SIZE);

    }

    printf("%s",buff);
    printf("\n%d bytes read\n",n);

    freeaddrinfo(results);
    return 0;
}
