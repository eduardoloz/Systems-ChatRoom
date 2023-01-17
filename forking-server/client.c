#include "header.h"

int sd;

void exitHandler(int sig) {
    write(sd, SIG_CLIENT_EXIT, strlen(SIG_CLIENT_EXIT));

    char *pid_str = malloc(6);
    sprintf(pid_str, "%d", getpid());
    remove(pid_str);
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

    sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    if(sd < 0){
        printf("%s\n",strerror(errno));
        exit(1);
    }

    if ( connect(sd, results->ai_addr, results->ai_addrlen) < 0) {
        printf("Failed to connect\n");
        exit(1);
    }

    // sent pid to server
    char *pid_str = malloc(5);
    sprintf(pid_str, "%d", getpid());
    write(sd, pid_str, 6);

    //DO STUFF
    int n;
    char *buff = malloc(MSG_SIZE * sizeof(char));
    char *read_buff = malloc(MSG_SIZE);

    int flags = fcntl(sd, F_GETFL, 0);
    fcntl(sd, F_SETFL, flags | O_NONBLOCK);

    for (;;) {

        // here use select
        while (read(sd, read_buff, MSG_SIZE) > 0) {
            printf("read from server: %s\n", read_buff);
        }

        signal(SIGINT, exitHandler);

        // printf("before fgets...\n");
        fgets(buff, MSG_SIZE, stdin);

        write(sd, buff, MSG_SIZE);

    }


    freeaddrinfo(results);
    return 0;
}