#include <iostream>
#include <string>

#include "bitflag.hpp"
#include "testing_base.h"

class TestBitFlag : public TestingBase {
public:

	TestBitFlag() : TestingBase() {}
};

enum TestFlags : size_t {
    Color = (1 << 0),    // 0 = RED, 1 = BLACK
    State = (1 << 1),    // 0 = NONE, 1 = SOME
};


TEST_F(TestBitFlag, Create) {
    ds::WideBitFlag flag;

    EXPECT_EQ(flag.get(), 0);

    flag.set(TestFlags::Color);

    EXPECT_EQ(flag.get(), 1);

    flag.flipflop(TestFlags::Color);

    EXPECT_EQ(flag.get(), 0);

    flag.flipflop(TestFlags::Color);

    EXPECT_EQ(flag.get(), 1);
    EXPECT_TRUE(flag.has(TestFlags::Color));

    flag.unset(TestFlags::Color);
    EXPECT_EQ(flag.get(), 0);
};
