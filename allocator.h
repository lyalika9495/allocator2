#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

#include "list.h"

#ifndef ALLOCATORLT_ALLOCATOR_H
#define ALLOCATORLT_ALLOCATOR_H

using namespace std;

/*!
 *  \brief Класс-обертка для указателя на выделенную память
 */
class CleverPtr {
    void* data; ///< Указатель на выделенную память

public:
    void* get() const; ///< Возвращает указатель на выделенную память
    explicit CleverPtr(void* data): data(data){}///< Конструктор
};

/*!
 *  \brief Класс аллокатор
 *
 *  Предназначен для выделения, очищения и работы с выделенной памятью
 *
 */
class Allocator {
    list* head;
    void* common_memory;
    void* support_memory;
    void* support_ptr;

    void* support_malloc();
    void union_free_blocks();
public:
    /*!
        Конструктор
        \param[in] size Размер резерва выделяемой памяти
    */
    explicit Allocator(int size);
    ~Allocator() {
        std::free(this->common_memory);
    }

    /*!
        Возвращает ветор пар, где каждая пара соответствует свободному блоку памяти и содержит расстояние от начала выделенной памяти и размер
        \return Вектор пар, в каждой из которых хранится сдвиг от начала памяти и размер свободного блока
    */
    void show_free_blocks(vector<pair<void*, int>>* free_blocks);

    /*!
        Возвращает ветор пар, где каждая пара соответствует занятому блоку памяти и содержит расстояние от начала выделенной памяти и размер
        \return Вектор пар, в каждой из которых хранится сдвиг от начала памяти и размер занятого блока
    */
    void show_busy_blocks(vector<pair<void*, int>>* busy_blocks);

    /*!
        Метод выделения памяти
        \param[in] size Размер выделяемой памяти
        \return Объект CleverPtr
    */
    CleverPtr alloc(const int size);

    /*!
        Метод очистки памяти
        \param[in] ссылка на объект CleverPtr
    */
    void free(CleverPtr&);

    /*!
        Метод выполняющий дефрагментацию основного блока памяти
    */
    void defrag();
};


#endif //ALLOCATORLT_ALLOCATOR_H
