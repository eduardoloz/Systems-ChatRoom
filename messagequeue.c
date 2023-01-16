#include "messagequeue.h"

struct chat_list* new_list(struct chat_mssg* first_mssg){
    struct chat_list* list = malloc(1*sizeof(struct chat_list));
    list -> oldest = NULL;
    list -> newest = NULL;

    list -> oldest = first_mssg;
    list -> newest = first_mssg;
    list -> len = 1;

    return list;
}


void add_mssg(struct chat_mssg* mssg, struct chat_list* chat){
    mssg -> old = chat -> newest;
    chat -> newest -> new = mssg;
    mssg -> new = NULL;
    chat -> newest = mssg;
    if(chat->len>=SIZE){
        chat->oldest = (chat->oldest)->new;
        free((chat->oldest)->old);
        (chat->oldest)->old = NULL;
    } else {
        chat->len++;
    }
 }

struct chat_mssg* new_mssg(char* mssg, int my_time, char* user){
     struct chat_mssg* my_mssg = malloc(1*sizeof(struct chat_mssg));
     my_mssg -> text = mssg;
     my_mssg -> old = NULL;
     my_mssg -> new = NULL;
     my_mssg -> time = my_time;
     my_mssg -> usr = user;
     return my_mssg;
 }

void print_chat(struct chat_list* chat){
     //MODIFY to format the chat
     struct chat_mssg* m = chat->oldest;
     while(m){
         printf("<%s> %s %d\n", m->usr, m->text, m->time);
         m = m->new;
     }
 }

int main(int argc, char const *argv[]) {
    struct chat_mssg* m = new_mssg("hello", 10, "bobby");
    struct chat_list* list = new_list(m);
    print_chat(list);
    printf("=======\n");
    struct chat_mssg* m2 = new_mssg("goobye", 14, "jake");
    struct chat_mssg* m3 = new_mssg("urmom", 17, "bobby");
    add_mssg(m2, list);
    add_mssg(m3, list);
    print_chat(list);
}
