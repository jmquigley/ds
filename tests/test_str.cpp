#include <ds/str.h>
#include <testing_base.h>

class TestStr : public TestingBase {
public:

	TestStr() : TestingBase() {}
};

TEST_F(TestStr, SplitString) {
	std::vector<std::string> delimiters {"/", "\\", "|"};
	std::string s = "a/b/c/d";
	std::vector<std::string> out;

	out = ds::splitStringOnDelimiters(s, delimiters);

	EXPECT_EQ(out.size(), 4);
	EXPECT_EQ(out[0], "a");
	EXPECT_EQ(out[1], "b");
	EXPECT_EQ(out[2], "c");
	EXPECT_EQ(out[3], "d");
};

TEST_F(TestStr, SplitStringMultipleDelimiters) {
	std::vector<std::string> delimiters {"/", "\\", "|"};
	std::string s = "a/b\\c|d";
	std::vector<std::string> out;

	out = ds::splitStringOnDelimiters(s, delimiters);

	EXPECT_EQ(out.size(), 4);
	EXPECT_EQ(out[0], "a");
	EXPECT_EQ(out[1], "b");
	EXPECT_EQ(out[2], "c");
	EXPECT_EQ(out[3], "d");
};

TEST_F(TestStr, SplitStringEmpty) {
	std::vector<std::string> delimiters {"/", "\\", "|"};
	std::string s = "";
	std::vector<std::string> out;

	out = ds::splitStringOnDelimiters(s, delimiters);

	EXPECT_EQ(out.size(), 0);
}

TEST_F(TestStr, SplitStringEmptyDelimiters) {
	std::vector<std::string> delimiters {};
	std::string s = "a/b/c/d";
	std::vector<std::string> out;

	out = ds::splitStringOnDelimiters(s, delimiters);

	EXPECT_EQ(out.size(), 1);
	EXPECT_EQ(out[0], "a/b/c/d");
}

TEST_F(TestStr, SplitStringAllEmpty) {
	std::vector<std::string> delimiters {};
	std::string s = "";
	std::vector<std::string> out;

	out = ds::splitStringOnDelimiters(s, delimiters);

	EXPECT_EQ(out.size(), 0);
}
