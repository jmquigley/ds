#include <iostream>
#include <string>

#include "bitflag.hpp"
#include "testing_base.h"

class TestBitFlag : public TestingBase {
public:

	TestBitFlag() : TestingBase() {}
};

enum TestFlags : size_t {
	Color = (1 << 0),  // 0 = RED, 1 = BLACK
	State = (1 << 1),  // 0 = NONE, 1 = SOME
};

TEST_F(TestBitFlag, Create) {
	ds::WideFlag flag;

	EXPECT_EQ(flag.get(), 0);

	flag.set(TestFlags::Color);

	EXPECT_EQ(flag.get(), 1);

	flag.toggle(TestFlags::Color);

	EXPECT_EQ(flag.get(), 0);

	flag.toggle(TestFlags::Color);

	EXPECT_EQ(flag.get(), 1);
	EXPECT_TRUE(flag.has(TestFlags::Color));

	flag.toggle(TestFlags::Color);
	EXPECT_FALSE(flag.has(TestFlags::Color));
	flag.toggle(TestFlags::Color);

	flag.unset(TestFlags::Color);
	EXPECT_EQ(flag.get(), 0);
};

TEST_F(TestBitFlag, Constructors) {
	ds::BitFlag bf1(123);  // 0111 1011
	ds::BitFlag bf2(bf1);

	EXPECT_TRUE(bf1 == bf2);
	EXPECT_FALSE(bf1 != bf2);

	ds::BitFlag bf3(128);  // 1000 0000

	EXPECT_FALSE(bf1 == bf3);
	EXPECT_TRUE(bf1 != bf3);
};

TEST_F(TestBitFlag, HasABit) {
	ds::BitFlag bf(3);	// 0000 0011

	EXPECT_TRUE(bf.has(TestFlags::Color | TestFlags::State));

	bf.reset();

	EXPECT_FALSE(bf.has(TestFlags::Color | TestFlags::State));

	bf.setValue(1);

	EXPECT_TRUE(bf.has(TestFlags::Color));
	EXPECT_FALSE(bf.has(TestFlags::State));
};

TEST_F(TestBitFlag, ToString) {
	ds::ByteFlag bf1(123);	// 0111 1011
	EXPECT_EQ(bf1.str(), "01111011");
	std::cout << bf1 << std::endl;

	ds::ShortFlag bf2(123);	 // 0111 1011
	EXPECT_EQ(bf2.str(), "0000000001111011");

	ds::BitFlag bf3(123);  // 0111 1011
	EXPECT_EQ(bf3.str(), "00000000000000000000000001111011");

	ds::WideFlag bf4(123);	// 0111 1011
	EXPECT_EQ(bf4.str(), "0000000000000000000000000000000000000000000000000000000001111011");
};

TEST_F(TestBitFlag, BitAt) {
	ds::BitFlag bf(123);  // 0111 1011

	EXPECT_EQ(bf.at(0), 1);
	EXPECT_EQ(bf.at(1), 1);
	EXPECT_EQ(bf.at(2), 0);
	EXPECT_EQ(bf.at(3), 1);
	EXPECT_EQ(bf.at(4), 1);
	EXPECT_EQ(bf.at(5), 1);
	EXPECT_EQ(bf.at(6), 1);
	EXPECT_EQ(bf.at(7), 0);
	EXPECT_EQ(bf.at(8), 0);
	EXPECT_EQ(bf.at(31), 0);
	EXPECT_EQ(bf.at(999), 0);

	EXPECT_EQ(bf[0], 1);
	EXPECT_EQ(bf[1], 1);
	EXPECT_EQ(bf[2], 0);
	EXPECT_EQ(bf[3], 1);
	EXPECT_EQ(bf[4], 1);
	EXPECT_EQ(bf[5], 1);
	EXPECT_EQ(bf[6], 1);
	EXPECT_EQ(bf[7], 0);
	EXPECT_EQ(bf[8], 0);
	EXPECT_EQ(bf[31], 0);
	EXPECT_EQ(bf[999], 0);

	ds::BitFlag bf2(2147483648);  // 1000 0000 0000 0000 0000 0000 0000 0000

	EXPECT_EQ(bf2.at(0), 0);
	EXPECT_EQ(bf2[0], 0);
	EXPECT_EQ(bf2.at(31), 1);
	EXPECT_EQ(bf2[31], 1);
};

TEST_F(TestBitFlag, BitwiseOperators) {
	ds::ByteFlag bf1(42);  // 0010 1010
	ds::ByteFlag bf2(23);  // 0001 0111
	ds::ByteFlag bf3;

	bf3 = bf1 & bf2;  // 0000 0010 (2)
	EXPECT_EQ(bf3.get(), 2);

	bf3 = bf1 | bf2;  // 0011 1111 (63)
	EXPECT_EQ(bf3.get(), 63);

	bf3 = bf1 ^ bf2;  // 0011 1101 (61)
	EXPECT_EQ(bf3.get(), 61);

	bf3 = ~bf1;	 // 1101 0101 (213)
	EXPECT_EQ(bf3.get(), 213);

	bf3 = bf1 << 1;	 // 0101 0100 (84)
	EXPECT_EQ(bf3.get(), 84);

	bf3 = bf1 >> 1;	 // 0001 0101 (21)
	EXPECT_EQ(bf3.get(), 21);
}
