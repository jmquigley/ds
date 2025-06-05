#include "test_objects.h"

#include <iostream>
#include <string>

#include "helpers.hpp"

TestHelpers::TestHelpers(): TestingBase() {
	memset(temp, 0, sizeof(temp));
	bufptr = nullptr;
};

enum class TestEnum: char {
    P1 = 1,
    P2 = 2,
    P3 = 3
};

TEST_F(TestHelpers, ShowEnumerationNumbering) {
    EXPECT_EQ(ds::as_integer(TestEnum::P1), 1);
    EXPECT_EQ(ds::as_integer(TestEnum::P2), 2);
    EXPECT_EQ(ds::as_integer(TestEnum::P3), 3);
};
