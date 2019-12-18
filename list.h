#ifndef ALLOCATORLK_LIST_H
#define ALLOCATORLK_LIST_H

enum states{
    _free=0,
    _busy=1
};

struct memory_elem{
    char *ptr;
    int size;
    states state;
};

struct list
{
    struct memory_elem* node;
    struct list* next;
};

struct list* list_init(char * ptr, int size);
struct list* add_elem(list *lst, char * ptr, int size);
struct list* push_back(list* head, char * memory, int size);
struct list* delete_elem(list *lst, list *head);

struct list* best_fit(list* head, int size);
struct list* container_of(list* head, const char* memory);

#endif //ALLOCATORLK_LIST_H
