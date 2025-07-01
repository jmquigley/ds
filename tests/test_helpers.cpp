#include <iostream>
#include <memory>
#include <string>

#include "helpers.hpp"
#include "testing_base.h"

class TestHelpers : public TestingBase {
public:

	TestHelpers() : TestingBase() {}
};

enum class TestEnum : char { P1 = 1, P2 = 2, P3 = 3 };

TEST_F(TestHelpers, ShowEnumerationNumbering) {
	EXPECT_EQ(ds::as_integer(TestEnum::P1), 1);
	EXPECT_EQ(ds::as_integer(TestEnum::P2), 2);
	EXPECT_EQ(ds::as_integer(TestEnum::P3), 3);
};

TEST_F(TestHelpers, weakPointerToString) {
	std::shared_ptr<int> p = std::make_shared<int>(10);
	std::weak_ptr<int> wp = p;

	std::string s = ds::weakPointerToString(wp);

	EXPECT_THAT(s, testing::ContainsRegex("0x\\w"));
}
