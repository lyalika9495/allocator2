#include <cstdio>
#include <cstdlib>
#include "iostream"

#include "list.h"


struct list* list_init(void * memory, int size) {
    struct list *lst;
    void * memory_ptr = (void*)((char*)memory + sizeof(list));
    lst = static_cast<struct list*>(memory);
    lst->ptr = memory_ptr;
    lst->size = size;
    lst->next = nullptr;

    return(lst);
}

void add_before(list* head, list* old_lst, list* new_lst){
    struct list* lst = head;

    while(lst->next != old_lst){
        lst = lst->next;
    }

    lst->next = new_lst;
    new_lst->next = old_lst;
}

void push_back(list* head, list* new_lst) {
    struct list* tail = head;

    while(tail->next) tail = tail->next;

    tail->next = new_lst;
}

struct list* delete_elem(list *lst, list *head) {
    struct list *temp;
    temp = head;

    while (temp->next != lst)
    {
        temp = temp->next;
    }
    temp->next = lst->next;

    return (temp);
}

struct list* best_fit(list* head, int size) {
    struct list* ptr = head;
    struct list* best_elem = nullptr;
    int min_diff = INT32_MAX;

    while (ptr) {
        if (ptr->state == _free) {
            int diff = ptr->size - size;

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
        if (ptr->ptr == memory)
            return (ptr);

        ptr = ptr->next;
    }

    return nullptr;
}

struct list* get_prev(list* head, list* lst){
    struct list* tmp = head;

    if (lst == head)
        return nullptr;

    while(tmp->next != lst) tmp = tmp->next;

    return tmp;
}
