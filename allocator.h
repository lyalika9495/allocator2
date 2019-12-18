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
    char* memory;

public:
    /*!
        Конструктор
        \param[in] size Размер резерва выделяемой памяти
    */
    explicit Allocator(int size);

    /*!
        Возвращает ветор пар, где каждая пара соответствует свободному блоку памяти и содержит расстояние от начала выделенной памяти и размер
        \param[out] Вектор пар, в каждой из которых хранится сдвиг от начала памяти и размер свободного блока
    */
    vector<pair<int, int>> show_free_blocks();

    /*!
        Возвращает ветор пар, где каждая пара соответствует занятому блоку памяти и содержит расстояние от начала выделенной памяти и размер
        \param[out] Вектор пар, в каждой из которых хранится сдвиг от начала памяти и размер занятого блока
    */
    vector<pair<int, int>>  show_busy_blocks();

    /*!
        Метод выделения памяти
        \param[in] size Размер выделяемой памяти
        \param[out] Объект CleverPtr
    */
    CleverPtr alloc(int size);

    /*!
        Метод очистки памяти
        \param[in] ссылка на объект CleverPtr
    */
    void free(CleverPtr&);

    /*!
        Метод объединяющий свободные соседние блоки памяти,
        для получения одного блока большего размера
    */
    void defrag();
};


#endif //ALLOCATORLT_ALLOCATOR_H
