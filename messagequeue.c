#include "messagequeue.h"

struct chat_list* new_list(char* first_text){
    struct chat_list* new_list = malloc(1*sizeof(struct chat_list));
    new_list -> oldest = NULL;
    new_list -> newest = NULL;

    struct chat_mssg* first_mssg = malloc(1*sizeof(struct chat_mssg));
    first_mssg -> text = first_text;
    first_mssg -> new = NULL;
    first_mssg -> old = NULL;

    new_list -> oldest = first_mssg;
    new_list -> newest = first_mssg;
    new_list -> len = 1;

    return new_list;
}


void add_new_mssg(char* mssg, struct chat_list* chat){
    struct chat_mssg* new_mssg = malloc(1*sizeof(struct chat_mssg));
    new_mssg -> text = mssg;
    new_mssg -> old = chat -> newest;
    chat -> newest -> new = new_mssg;
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

 void print_chat(struct chat_list* chat){
     //MODIFY to format the chat
     struct chat_mssg* m = chat->oldest;
     while(m){
         printf("%s\n", m->text);
         m = m->new;
     }
 }

int main(int argc, char const *argv[]) {
    char* m = "hello";
    struct chat_list* list = new_list(m);
    // printf("%s\n", list->oldest->text);
    // printf("%s\n", list->newest->text);
    // printf("%d\n", list->len);
    // printf("=======\n");
    char* m2 = "goobye";
    char* m3 = "urmom";
    add_new_mssg(m2, list);
    // printf("%s\n", list->oldest->text);
    add_new_mssg(m3, list);
    // printf("%s\n", list->oldest->text);
    // printf("%s\n", list->newest->text);
    // printf("%d\n", list->len);
    // printf("=======\n");
    print_chat(list);
}
