#include <cassert>
#include "test.h"
#include "allocator.h"


bool test::test_alloc() {
    Allocator allocator = Allocator(100);

    CleverPtr clptr = allocator.alloc(10);
    CleverPtr clptr1 = allocator.alloc(11);
    CleverPtr clptr2 = allocator.alloc(12);
    CleverPtr clptr3 = allocator.alloc(13);

    vector<pair<void*, int>>* busy_blocks = new vector<pair<void*, int>>();
    allocator.show_busy_blocks(busy_blocks);
    assert(busy_blocks->size()==4);

    int result_size = 0;
    for (auto v: *(busy_blocks)) {
        result_size += v.second;
    }
    assert(result_size==46);

    cout << "test alloc done" << endl;

    return true;
}

bool test::test_free(){
    Allocator allocator = Allocator(100);

    CleverPtr clptr = allocator.alloc(10);
    CleverPtr clptr1 = allocator.alloc(11);
    CleverPtr clptr2 = allocator.alloc(12);
    CleverPtr clptr3 = allocator.alloc(13);

    allocator.free(clptr);
    allocator.free(clptr2);

    vector<pair<void*, int>>* busy_blocks = new vector<pair<void*, int>>();
    allocator.show_busy_blocks(busy_blocks);

    assert(busy_blocks->size()==2);

    int result_size = 0;
    for (auto v: *(busy_blocks)) {
        result_size += v.second;
    }
    assert(result_size==24);

    cout << "test free done" << endl;

    return true;
}

bool test::test_defrag(){
    Allocator allocator = Allocator(100);

    CleverPtr clptr = allocator.alloc(10);
    CleverPtr clptr1 = allocator.alloc(11);
    CleverPtr clptr2 = allocator.alloc(12);
    CleverPtr clptr3 = allocator.alloc(13);

    allocator.free(clptr1);
    allocator.free(clptr2);

    vector<pair<void*, int>>* free_blocks = new vector<pair<void*, int>>();
    allocator.show_free_blocks(free_blocks);

    assert(free_blocks->size() == 2);

    int result_size = 0;
    for (auto v: *(free_blocks)) {
        result_size += v.second;
    }
    assert(result_size==77);

    allocator.defrag();

    vector<pair<void*, int>>* free_blocks1 = new vector<pair<void*, int>>();
    allocator.show_free_blocks(free_blocks1);

    assert(free_blocks1->size() == 1);

    result_size = 0;
    for (auto v: *(free_blocks)) {
        result_size += v.second;
    }
    assert(result_size==77);

    cout << "test defrag done" << endl;

    return true;
}
