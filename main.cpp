#include <iostream>
#include "test.h"

using namespace std;

int main() {
    test tester = test();

    if (tester.test_alloc() and tester.test_free() and tester.test_defrag())
        cout << "Done";

    return 0;
}