#include <iostream>
#include "allocator.h"

void* CleverPtr::get() const {
    return data;
}


Allocator::Allocator(int size) {
    this->memory = (char*)malloc(size);
    this->head = list_init(this->memory, size);
}

CleverPtr Allocator::alloc(int size) {
    list *elem = best_fit(this->head, size);

    if (elem) {
        list *nwelem = push_back(this->head, elem->node->ptr, size);

        elem->node->ptr = (char*)((uintptr_t)(elem->node->ptr) + size);
        elem->node->size -= size;

        return CleverPtr{nwelem->node->ptr};
    }

    return CleverPtr(nullptr);
}

void Allocator::free(CleverPtr &ptr) {
    struct list* container = container_of(this->head, ((char*)ptr.get()));

    container->node->state = _free;
}

void Allocator::defrag() {
    struct list* elem = this->head;

    while(elem) {
        if (elem->next) {
            if (elem->next->node->state == _free) {
                elem->node->size += elem->next->node->size;
                delete_elem(elem->next, this->head);
            }
        }
    }
}

vector<pair<int, int>>  Allocator::show_free_blocks() {

    vector<pair<int, int>> free_blocks = vector<pair<int, int>>();
    struct list * elem = head;

    while(elem) {
        if (elem->node->state == _free) {
            pair<int, int> p = {(this->head->node->ptr - elem->node->ptr), elem->node->size};
            free_blocks.emplace_back(p);
        }
        elem = elem->next;
    }

    return (free_blocks);
}

vector<pair<int, int>>  Allocator::show_busy_blocks() {

    vector<pair<int, int>> free_blocks = vector<pair<int, int>>();
    struct list * elem = head;

    while(elem) {
        if (elem->node->state == _busy) {
            pair<int, int> p = {(this->head->node->ptr - elem->node->ptr), elem->node->size};
            free_blocks.emplace_back(p);
        }
        elem = elem->next;
    }

    return (free_blocks);
}
