#include <testing_base.h>

#include <ds/helpers.hpp>
#include <iostream>
#include <memory>
#include <string>

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

TEST_F(TestHelpers, pointerToString) {
	std::shared_ptr<int> p = std::make_shared<int>(42);
	std::string s = ds::pointerToString(p);

	EXPECT_THAT(s, testing::ContainsRegex("0x\\w"));
}

TEST_F(TestHelpers, weakPointerToString) {
	std::shared_ptr<int> p = std::make_shared<int>(42);
	std::weak_ptr<int> wp = p;

	std::string s = ds::weakPointerToString(wp);

	EXPECT_THAT(s, testing::ContainsRegex("0x\\w"));
}

TEST_F(TestHelpers, InvalidWeakPointer) {
	std::weak_ptr<int> wp;

	std::string s = ds::weakPointerToString(wp);
	EXPECT_EQ(s, "invalid");

	s = ds::weakPointerToString(wp, "different message");
	EXPECT_EQ(s, "different message");
}

TEST_F(TestHelpers, CheckForAllGoodPointers) {
	std::shared_ptr<int> pa1 = std::make_shared<int>(1);
	std::shared_ptr<int> pa2 = std::make_shared<int>(2);
	std::shared_ptr<int> pa3 = std::make_shared<int>(3);
	std::shared_ptr<int> pa4;

	EXPECT_TRUE(ds::all(pa1, pa2, pa3));
	EXPECT_FALSE(ds::all(pa1, pa2, pa4));
	EXPECT_FALSE(ds::all(pa4, pa1, pa2));
}

TEST_F(TestHelpers, CheckForAnyGoodPointers) {
	std::shared_ptr<int> pa1;
	std::shared_ptr<int> pa2;
	std::shared_ptr<int> pa3 = std::make_shared<int>(3);
	std::shared_ptr<int> pa4 = std::make_shared<int>(4);

	EXPECT_TRUE(ds::any(pa1, pa2, pa3));
	EXPECT_FALSE(ds::any(pa1, pa2));
}

TEST_F(TestHelpers, TestDJB2Hash) {
	size_t hash;

	EXPECT_EQ(ds::djb2(nullptr), 0);			 // Bad pointer
	EXPECT_EQ(ds::djb2(""), 5381);				 // empty string
	EXPECT_EQ(ds::djb2("hello"), 210714636441);	 // simple string
	EXPECT_EQ(ds::djb2("Hello"), 210676686969);	 // show's case sensitivity

	// longer string test
	const char *str1 = "This is a longer string to test the hash function";
	hash = ds::djb2(str1);
	EXPECT_EQ(hash, 15351638478594043462ULL);

	// special characters test
	const char *str2 = "!@#$%^&*()_+";
	hash = ds::djb2(str2);
	EXPECT_EQ(hash, 11563447441663042651ULL);
}
