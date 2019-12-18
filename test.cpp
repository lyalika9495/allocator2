#include <cassert>
#include "test.h"
#include "allocator.h"

bool test::test_alloc() {
    Allocator allocator = Allocator(100);

    CleverPtr clptr = allocator.alloc(10);
    CleverPtr clptr1 = allocator.alloc(10);
    CleverPtr clptr2 = allocator.alloc(10);
    CleverPtr clptr3 = allocator.alloc(10);

    vector<pair<int, int>> busy_blocks = allocator.show_busy_blocks();

    assert(busy_blocks.size()==4);

    return true;
}

bool test::test_free(){
    Allocator allocator = Allocator(100);

    CleverPtr clptr = allocator.alloc(10);
    CleverPtr clptr1 = allocator.alloc(10);
    CleverPtr clptr2 = allocator.alloc(10);
    CleverPtr clptr3 = allocator.alloc(10);

    allocator.free(clptr);
    allocator.free(clptr2);

    vector<pair<int, int>> busy_blocks = allocator.show_busy_blocks();

    assert(busy_blocks.size()==2);

    return true;
}

bool test::test_defrag(){
    Allocator allocator = Allocator(100);

    CleverPtr clptr = allocator.alloc(10);
    CleverPtr clptr1 = allocator.alloc(10);
    CleverPtr clptr2 = allocator.alloc(10);
    CleverPtr clptr3 = allocator.alloc(10);

    allocator.free(clptr1);
    allocator.free(clptr2);

    vector<pair<int, int>> free_blocks = allocator.show_free_blocks();

    assert(free_blocks.size() == 3);

    allocator.defrag();

    vector<pair<int, int>> free_blocks1 = allocator.show_free_blocks();

    assert(free_blocks1.size() == 2);

    return true;
}
