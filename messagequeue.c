#include <stdio.h>
#define SIZE 200


struct chat_list{
    struct chat_list* oldest;
    struct chat_list* newest;
};

struct chat_mssg{
    struct chat_list* old;
    struct chat_list* new;
    int len;
    char* text;
};


struct chat_list* new_list(char* first_mssg){
    struct chat_list* new_list = malloc(1*sizeof(struct chat_list));
    new_list -> oldest = NULL;
    new_list -> newest = NULL;
    struct chat_mssg* new_mssg = new_mssg(first_mssg, new_list);
    new_list -> oldest = new_mssg;
    new_list -> len = 1;
    return new_list;
}


void new_mssg(char* mssg, struct chat_list* list){
    struct chat_mssg* new_mssg = malloc(1*sizeof(struct chat_mssg));
    new_mssg -> text = mssg;
    new_mssg -> old = list -> newest;
    new_mssg -> new = NULL;
    chat_list -> newest = new_mssg;
    if(chat_list->len>=200){
        
    } else {
        chat_list->len++;
    }
 }
