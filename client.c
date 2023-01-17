#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define MSG_SIZE 1025

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


    //I CARE

    int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    if(sd < 0){
        printf("%s\n",strerror(errno));
        exit(1);
    }

    if ( connect(sd, results->ai_addr, results->ai_addrlen) < 0) {
        printf("Failed to connect\n");
        exit(1);
    }
    char buff[MSG_SIZE];
    printf("Enter Username: ");
    fgets(buff, MSG_SIZE, stdin);
    buff[strlen(buff)-1] = '\0';
    write(sd, buff, sizeof(buff));


    //DO STUFF
    int n;

    fd_set read_fds;

    while(1){
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(sd,&read_fds);
        int i = select(sd+1, &read_fds, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &read_fds)){
            fgets(buff, MSG_SIZE, stdin);
            buff[strlen(buff)-1] = '\0';
            write(sd, buff, MSG_SIZE);
        }
        if(FD_ISSET(sd, &read_fds)){
            read(sd, buff, MSG_SIZE);
            printf("%s\n", buff);
        }

        sleep(1);

    }

    freeaddrinfo(results);
    return 0;
}
