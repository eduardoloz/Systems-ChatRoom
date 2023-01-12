#include "messagequeue.h"

struct chat_list* new_list(char* first_mssg){
    struct chat_list* new_list = malloc(1*sizeof(struct chat_list));
    new_list -> oldest = NULL;
    new_list -> newest = NULL;
    new_mssg(first_mssg, new_list);
    new_list -> oldest = new_list -> newest;
    new_list -> len = 1;
    return new_list;
}


void new_mssg(char* mssg, struct chat_list* chat){
    struct chat_mssg* new_mssg = malloc(1*sizeof(struct chat_mssg));
    new_mssg -> text = mssg;
    new_mssg -> old = chat -> newest;
    new_mssg -> new = NULL;
    chat -> newest = new_mssg;
    if(chat->len>=200){
        chat->oldest = (chat->oldest)->new;
        free((chat->oldest)->old);
        (chat->oldest)->old = NULL;
    } else {
        chat->len++;
    }
 }
