#include <iostream>
#include "allocator.h"

void* CleverPtr::get() const {
    return data;
}


Allocator::Allocator(int size) {
    //1 байт между каждым экземпляром структуры list и 1 байт между основным и вспомогательным массивом
    this->common_memory = malloc(size + (size + 1) * sizeof(struct list) + 1);

    this->support_memory = (void*)((uintptr_t)this->common_memory + size + 1);
    this->support_ptr = this->support_memory;

    this->head = static_cast<struct list*>(support_malloc());
    this->head->ptr = this->common_memory;
    this->head->size = size;
    this->head->state = _free;
    this->head->next = nullptr;
}

void* Allocator::support_malloc() {
    void* ptr = this->support_ptr;
    this->support_ptr = (void*)((uintptr_t)this->support_ptr + sizeof(struct list) + 1);

    return (ptr);
}

CleverPtr Allocator::alloc(const int size) {
    list *elem = best_fit(this->head, size);

    if (elem) {
        list *nwelem = static_cast<struct list*>(support_malloc());
        nwelem->ptr = elem->ptr;
        nwelem->size = size;
        nwelem->state = _busy;
        nwelem->next = nullptr;

        if (this->head == elem){ //push_front
            nwelem->next = this->head;
            this->head = nwelem;
        }
        else{
            add_before(this->head, elem, nwelem);
        }

        elem->ptr = (char*)((uintptr_t)(elem->ptr) + size);
        elem->size -= size;

        return CleverPtr{nwelem->ptr};
    }

    return CleverPtr(nullptr);
}

void Allocator::free(CleverPtr &ptr) {
    struct list* container = container_of(this->head, (static_cast<char*>(ptr.get())));

    container->state = _free;

    union_free_blocks();
}

void Allocator::union_free_blocks() {
    struct list* elem = this->head;

    while(elem) {
        if (elem->next and elem->state == _free) {
            if (elem->next->state == _free) {
                elem->size += elem->next->size;
                elem->next = elem->next->next;
                //delete_elem(elem->next, this->head);
            }
        }

        elem = elem->next;
    }
}

void Allocator::defrag() {
    struct list* lst = head;
    struct list *free_block1 = nullptr, *free_block2 = nullptr;

    while(lst){
        if (lst->state == _free) {
            if (!free_block1)
                free_block1 = lst;
            else {
                free_block2 = lst;

                struct list *tmp = free_block1->next;
                void *src = tmp->ptr;
                void *dest = free_block1->ptr;
                int size = (int) ((uintptr_t) free_block2->ptr - (uintptr_t) tmp->ptr);

                memmove(dest, src, size);

                while (tmp != free_block2) {
                    tmp->ptr = (void *) ((uintptr_t) tmp->ptr - free_block1->size);
                    tmp = tmp->next;
                }
                free_block1->ptr = (void *) ((uintptr_t) free_block2->ptr - free_block1->size);

                struct list *free_block1_prev = get_prev(this->head, free_block1);
                struct list *free_block2_prev = get_prev(this->head, free_block2);

                if (!free_block1_prev)
                    this->head = free_block1->next;
                else
                    free_block1_prev->next = free_block1->next;

                free_block1->next = free_block2;
                free_block2_prev->next = free_block1;

                free_block1->size += free_block2->size;
                delete_elem(free_block2, this->head);
                free_block2 = nullptr;
            }
        }
        lst = lst->next;
    }
}

void  Allocator::show_free_blocks(vector<pair<void*, int>>* free_blocks) {
    struct list * elem = this->head;

    while(elem) {
        if (elem->state == _free) {
            pair<void*, int> p = {(elem->ptr), elem->size};
            free_blocks->push_back(p);
        }
        elem = elem->next;
    }
}

void Allocator::show_busy_blocks(vector<pair<void*, int>>* busy_blocks) {
    struct list * elem = this->head;

    while(elem) {
        if (elem->state == _busy) {
            pair<void*, int> p = {(elem->ptr), elem->size};
            busy_blocks->push_back(p);
        }
        elem = elem->next;
    }
}
