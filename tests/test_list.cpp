#include "test_objects.h"

#include <iostream>
#include <string>

#include "list.hpp"

TestList::TestList(): TestingBase() {
	memset(temp, 0, sizeof(temp));
	bufptr = nullptr;
};

TEST_F(TestList, ListCreate) {
    EXPECT_TRUE(true);
};
