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

    flag.toggle(TestFlags::Color);
    EXPECT_FALSE(flag.has(TestFlags::Color));
    flag.toggle(TestFlags::Color);

    flag.unset(TestFlags::Color);
    EXPECT_EQ(flag.get(), 0);
};

TEST_F(TestBitFlag, Constructors) {
    ds::BitFlag bf1 = 123;
    ds::BitFlag bf2(bf1);

    EXPECT_TRUE(bf1 == bf2);
    EXPECT_FALSE(bf1 != bf2);

    ds::BitFlag bf3(128);

    EXPECT_FALSE(bf1 == bf3);
    EXPECT_TRUE(bf1 != bf3);
};

TEST_F(TestBitFlag, HasABit) {
    ds::BitFlag bf(3);

    EXPECT_TRUE(bf.has(TestFlags::Color | TestFlags::State));

    bf.reset();

    EXPECT_FALSE(bf.has(TestFlags::Color | TestFlags::State));

    bf = 1;

    EXPECT_TRUE(bf.has(TestFlags::Color));
    EXPECT_FALSE(bf.has(TestFlags::State));
};

TEST_F(TestBitFlag, ToString) {
    ds::ByteBitFlag bf1 = 123;
    EXPECT_EQ(bf1.str(), "01111011");
    std::cout << bf1 << std::endl;

    ds::ShortBitFlag bf2 = 123;
    EXPECT_EQ(bf2.str(), "0000000001111011");

    ds::BitFlag bf3 = 123;
    EXPECT_EQ(bf3.str(), "00000000000000000000000001111011");

    ds::WideBitFlag bf4 = 123;
    EXPECT_EQ(bf4.str(), "0000000000000000000000000000000000000000000000000000000001111011");
};

TEST_F(TestBitFlag, BitAt) {
    ds::BitFlag bf = 123;

    EXPECT_EQ(bf.at(1), 1);
    EXPECT_EQ(bf.at(2), 1);
    EXPECT_EQ(bf.at(3), 0);
    EXPECT_EQ(bf.at(4), 1);
    EXPECT_EQ(bf.at(5), 1);
    EXPECT_EQ(bf.at(6), 1);
    EXPECT_EQ(bf.at(7), 1);
    EXPECT_EQ(bf.at(8), 0);
    EXPECT_EQ(bf.at(9), 0);
    EXPECT_EQ(bf.at(32), 0);
    EXPECT_EQ(bf.at(999), 0);

    EXPECT_EQ(bf[1], 1);
    EXPECT_EQ(bf[2], 1);
    EXPECT_EQ(bf[3], 0);
    EXPECT_EQ(bf[4], 1);
    EXPECT_EQ(bf[5], 1);
    EXPECT_EQ(bf[6], 1);
    EXPECT_EQ(bf[7], 1);
    EXPECT_EQ(bf[8], 0);
    EXPECT_EQ(bf[9], 0);
    EXPECT_EQ(bf[32], 0);
    EXPECT_EQ(bf[999], 0);
};
