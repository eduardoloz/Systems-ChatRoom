#include "header.h"

  int main(){
        struct addrinfo * hints, * results;
        hints = calloc(1,sizeof(struct addrinfo));

        hints->ai_family = AF_INET;
        hints->ai_socktype = SOCK_STREAM; //TCP socket
        hints->ai_flags = AI_PASSIVE; //only needed on server
        getaddrinfo(NULL, "4040" , hints, &results);  //NULL is localhost or 127.0.0.1

        //create socket
        int listen_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
        bind(listen_socket, results->ai_addr, results->ai_addrlen);
        listen(listen_socket, 10);//10 clients can wait to be processed

        socklen_t sock_size;
        struct sockaddr_storage client_address;
        sock_size = sizeof(client_address);

        printf("====== CHATROOM ======\n\n");

        int *all_children = malloc(100 * sizeof(int));
        int n_child = 0;

        int server_wkp;
        mkfifo("SERVER_WKP", 0777);
        server_wkp = open("SERVER_WKP", O_RDWR);

      for(;;) {

            //wait for next client
            int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);

            // request the client's pid
            char *client_pid = malloc(6);
            read(client_socket, client_pid, 6);
            printf("user %s has joined\n", client_pid);

            int child = fork();
            all_children[n_child] = child;
            n_child++;

            if (child == 0) {

                // printf("opened client pipe %d...\n", client_pid);
                // int client_wkp = open(client_pid, O_WRONLY);

                char *read_msg = malloc(MSG_SIZE * sizeof(char));
                for (;;) {
                    while (read(client_socket, read_msg, MSG_SIZE) > 0) {
                        // check to see if connection was closed
                        if (strcmp(read_msg, SIG_CLIENT_EXIT) == 0) {
                            printf("user %s has left\n", client_pid);
                            exit(0);
                        }

                        // write message to server
                        for (int i = 0; i < n_child; i++) {
                            // printf("writing...\n");
                            write(server_wkp, read_msg, strlen(read_msg));
                        }

                        // read from server, write message back to client
                        char *read_server = malloc(MSG_SIZE);
                        read(server_wkp, read_server, MSG_SIZE);
                        // printf("wrote %s to child...\n", read_server);
                        // write(client_wkp, read_server, strlen(read_server));


                        printf("user %s> %s\n", client_pid, read_msg);
                    }
                }
            }
            // printf("num childrn: %d\n", n_child);
      }
      free(hints);
      freeaddrinfo(results);
      return 0;
  }