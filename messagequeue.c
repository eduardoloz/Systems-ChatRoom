#include <stdio.h>
#define SIZE 200


struct chat_list{
    struct chat_list* oldest;
    struct chat_list* newest;
};

struct chat_mssg{
    struct chat_list* old;
    struct chat_list* new;
    char* text;
};




void new_mssg(char* mssg, struct chat_list* list){
    struct chat_list* new_mssg = malloc(1*sizeof(struct chat_mssg));
    new_mssg -> text = mssg;
    new_mssg -> old = list -> newest;
    new_mssg -> new = NULL;
    chat_list -> newest = new_mssg;
 }
