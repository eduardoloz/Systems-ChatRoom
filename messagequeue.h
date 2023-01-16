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
#define SIZE 200

struct chat_list{
    struct chat_mssg* oldest;
    struct chat_mssg* newest;
    int len;
};


struct chat_mssg {
    struct chat_mssg* old;
    struct chat_mssg* new;
    char* text;
    int time;
    char* usr;
};


struct chat_list* new_list(struct chat_mssg* first_mssg);
void add_mssg(struct chat_mssg* mssg, struct chat_list* chat);
struct chat_mssg* new_mssg(char* mssg, int my_time, char* user);
void print_chat(struct chat_list* chat);
