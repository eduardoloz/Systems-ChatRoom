#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

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
    char buff[1025];
    printf("Enter Username: ");
    fgets(buff, 1025, stdin);
    buff[strlen(buff)-1] = '\0';
    write(sd, buff, sizeof(buff));


    //DO STUFF
    int n;
    while(1){
        strcpy(buff, "Hello");
        buff[strlen(buff)] = '\0';

      	if((n = write(sd, buff, sizeof(buff))) <= 0){
      		printf("\n write error \n");
            exit(1);
      	}
        printf("Sent: %s\n",buff);
        sleep(2);

    }

    freeaddrinfo(results);
    return 0;
}
