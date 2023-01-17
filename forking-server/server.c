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

        // make msg buffer file
        FILE *fp;
        fp = fopen("SERVER_MESSAGES", "w");
        fclose(fp);

      for(;;) {
            //wait for next client
            int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);

            // request the client's username
            char *username = calloc(255, sizeof(char));
            read(client_socket, username, 255);
            printf("user %s has joined\n", username);

            int child = fork();
            all_children[n_child] = child;
            n_child++;

            if (child == 0) {
                char *read_msg = malloc(MSG_SIZE * sizeof(char));

                int inner_child = fork();

                for (;;) {

                    if (inner_child == 0) {
                        int server_read_fp = open("SERVER_MESSAGES", O_RDONLY);
                        for (;;) {
                            char *read_buff = malloc(MSG_SIZE);

                            while (read(server_read_fp, read_buff, MSG_SIZE) > 0) {
                                write(client_socket, read_buff, MSG_SIZE);
                            }
                        }
                    }

                    while (read(client_socket, read_msg, MSG_SIZE) > 0) {

                        FILE *server_fp;
                        server_fp = fopen("SERVER_MESSAGES", "a+");

                        // check to see if connection was closed
                        if (strcmp(read_msg, SIG_CLIENT_EXIT) == 0) {
                            printf("user %s has left\n", username);
                            exit(0);
                        }

                        // write message to buffer
                        fprintf(server_fp, "user %s> %s", username, read_msg);

                        int len = strlen(read_msg);
                        read_msg[len-1] = '\0';
                        printf("user %s> %s\n", username, read_msg);

                        fclose(server_fp);
                        // close(server_read_fp);
                    }
                }
            }
            // printf("num childrn: %d\n", n_child);
      }
      free(hints);
      freeaddrinfo(results);
      return 0;
  }