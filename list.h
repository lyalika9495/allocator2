#ifndef ALLOCATORLK_LIST_H
#define ALLOCATORLK_LIST_H

enum states{
    _free=0,
    _busy=1
};

struct list
{
    struct list* next;
    void *ptr;
    int size;
    states state;
};

struct list* list_init(void * ptr, int size);
void add_before(list* head, list* old_lst, list* new_lst);
void push_back(list* head, list* new_lst);
struct list* get_prev(list* head, list* lst);
struct list* delete_elem(list *lst, list *head);

struct list* best_fit(list* head, int size);
struct list* container_of(list* head, const char* memory);

#endif //ALLOCATORLK_LIST_H
