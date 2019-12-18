#include <cstdio>
#include <cstdlib>

#include "list.h"


struct list* list_init(char * ptr, int size){
    struct list *lst;
    lst = (struct list*)malloc(sizeof(struct list));

    auto *node = (struct memory_elem*)malloc(sizeof(struct memory_elem));
    node->ptr = ptr;
    node->size = size;

    lst->node = node;
    lst->next = nullptr;

    return(lst);
}


struct list* add_elem(list *lst, char * ptr, int size){
    struct list *temp, *p;
    temp = (struct list*)malloc(sizeof(list));
    p = lst->next;
    lst->next = temp;

    auto *node = (struct memory_elem*)malloc(sizeof(struct memory_elem));
    node->ptr = ptr;
    node->size = size;
    node->state = _busy;

    temp->node = node;
    temp->next = p;

    return(temp);
}

struct list* push_back(list* head, char * memory, int size) {
    struct list* tail = head;

    while(tail->next) tail = tail->next;

    return add_elem(tail, memory, size);
}

struct list* delete_elem(list *lst, list *head) {
    struct list *temp;
    temp = head;

    while (temp->next != lst)
    {
        temp = temp->next;
    }
    temp->next = lst->next;

    free(lst);

    return(temp);
}


struct list* best_fit(list* head, int size){
    struct list* ptr = head;
    struct list* best_elem = nullptr;
    int min_diff = INT32_MAX;

    while (ptr) {
        if (ptr->node->state == _free) {
            int diff = ptr->node->size - size;

            if (diff < min_diff){
                min_diff = diff;
                best_elem = ptr;
            }
        }

        ptr = ptr->next;
    }

    return (best_elem);
}

struct list* container_of(list* head, const char* memory) {
    struct list* ptr = head;

    while(ptr){
        if (ptr->node->ptr == memory)
            return (ptr);

        ptr = ptr->next;
    }

    return nullptr;
}