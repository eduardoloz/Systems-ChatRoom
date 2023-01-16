#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "header.h"



int main(){
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));
    char* PORT = "9998";


    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; //TCP socket
    hints->ai_flags = AI_PASSIVE; //only needed on server
    getaddrinfo(NULL, PORT , hints, &results);  //NULL is localhost or 127.0.0.1

    //create socket
    int listen_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);\

    //this code allows the port to be freed after program exit.  (otherwise wait a few minutes)
    int yes = 1;
    if ( setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1 ) {
        printf("sockopt  error\n");
        printf("%s\n",strerror(errno));
        exit(-1);
    }

    int err = bind(listen_socket, results->ai_addr, results->ai_addrlen);
    if(err == -1){
        printf("Error binding: %s",strerror(errno));
        exit(1);
    }
    listen(listen_socket, 3);//3 clients can wait to be processed
    printf("Listening on port %s\n",PORT);

    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);

    fd_set read_fds;

    char buff[1025]="";

    for(;;){
        printf("Happening again\n");
        FD_ZERO(&read_fds);
        printf("This step isn't reached\n");
        //FD_SET(STDIN_FILENO, &read_fds);
        //printf("This step isn't reached\n");
        FD_SET(listen_socket,&read_fds);
        printf("This step isn't reached\n");

        int i = select(listen_socket + 1, &read_fds, NULL, NULL, NULL);
        
        printf("i is currently: %d\n", i);
        // if socket
        if (FD_ISSET(listen_socket, &read_fds)) {
            //accept the connection
            int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
            printf("Connected, waiting for data.\n");

            //read the whole buff
            read(client_socket,buff, MSG_SIZE);
            //trim the string
            printf("\nRecieved from client '%s'\n",buff);
        }
        printf("SPAM MESSAGE\n");
    }
    
    free(hints);
    freeaddrinfo(results);
    return 0;
}
