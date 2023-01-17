#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXCLIENTS 200

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


    char buff[1025]="";

    fd_set read_fds;

    int connections[MAXCLIENTS];
    char* usernames[MAXCLIENTS];
    int users = 1;
    connections[0] = listen_socket;
    FD_ZERO(&read_fds);
    FD_SET(listen_socket, &read_fds);
    for(;;){
        int i = select(connections[users-1]+1, &read_fds, NULL, NULL, NULL);

        // if socket
        if (FD_ISSET(listen_socket, &read_fds)) {
            //accept the connection
            int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
            read(client_socket, buff, sizeof(buff));
            printf("New User %s Has Joined\n", buff);

            usernames[users] = malloc((strlen(buff)+1)*sizeof(char));
            strcpy(usernames[users], buff);

            connections[users] = client_socket;
            FD_SET(client_socket,&read_fds);
            users++;
        } else {
            for(int i = 1; i<users; i++){
                if(FD_ISSET(connections[i], &read_fds)){
                    read(connections[i],buff, sizeof(buff));
                    printf("%s> %s\n", usernames[i], buff);
                }
            }
        }
    }



    free(hints);
    freeaddrinfo(results);
    return 0;
}
