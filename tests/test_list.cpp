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
};
