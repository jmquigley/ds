#include "test_objects.h"

#include <iostream>
#include <string>

#include "list.hpp"

TestList::TestList(): TestingBase() {
	memset(temp, 0, sizeof(temp));
	bufptr = nullptr;
};

TEST_F(TestList, ListCreate) {
    ds::List<int> list;
    EXPECT_EQ(list.getLength(), 0);

    list.insert(1);
    EXPECT_EQ(list.getLength(), 1);  // root insert

    list.insert(2);
    EXPECT_EQ(list.getLength(), 2);  // second insert

    ds::List<int>::Iterator it(list.getFirst());

    auto it1 = list.begin();
    auto it2 = list.end();

    // std::cout << "(1): " << it << ", *: " << *it << std::endl;
    // std::cout << "(2): " << it.next() << ", *: " << *it << std::endl;

    // std::cout << "begin: " << list.begin() << ", end: " << list.end() << std::endl;

    for (auto it = list.begin(); it != list.end(); ++it) {
        // std::cout << "val: " << it << ", *: " << *it << std::endl;
    }

    for (auto it : list) {
        // std::cout << "it: " << it << std::endl;
    }

/*
    int i = 0;
    for (it = list.begin(); it != list.end(); it++) {
        std::cout << "it: " << *it << std::endl;

        if (i == 0) {
            EXPECT_EQ(*it, 1);
        } else if (i == 1) {
            EXPECT_EQ(*it, 2);
        }

        i++;
     }
*/

    list.clear();
};
