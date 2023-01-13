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


struct chat_mssg{
    struct chat_mssg* old;
    struct chat_mssg* new;
    char* text;
    int time;
    int usr;
};


struct chat_list* new_list(char* first_mssg);
void add_new_mssg(char* mssg, struct chat_list* list);
