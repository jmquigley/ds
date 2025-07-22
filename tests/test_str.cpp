#include <ds/str.h>
#include <testing_base.h>

#include <string>
#include <vector>

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

TEST_F(TestStr, SplitStringMultipleConsecutiveDelimiters) {
	std::vector<std::string> delimiters {"/", "\\", "|"};
	std::string s = "a////b\\\\\\\\c||||d";
	std::vector<std::string> out;

	out = ds::splitStringOnDelimiters(s, delimiters);

	EXPECT_EQ(out.size(), 4);
	EXPECT_EQ(out[0], "a");
	EXPECT_EQ(out[1], "b");
	EXPECT_EQ(out[2], "c");
	EXPECT_EQ(out[3], "d");
}

TEST_F(TestStr, SplitStringDelimitersAtFrontBack) {
	std::vector<std::string> delimiters {"/", "\\", "|"};
	std::string s = "//////a////b\\\\\\\\c||||d||/|";
	std::vector<std::string> out;

	out = ds::splitStringOnDelimiters(s, delimiters);

	EXPECT_EQ(out.size(), 4);
	EXPECT_EQ(out[0], "a");
	EXPECT_EQ(out[1], "b");
	EXPECT_EQ(out[2], "c");
	EXPECT_EQ(out[3], "d");
}

TEST_F(TestStr, JoinStrings) {
	std::vector<std::string> inp {"a", "b", "c", "d"};

	EXPECT_EQ(inp.size(), 4);
	EXPECT_EQ(ds::join(inp), "abcd");
	EXPECT_EQ(ds::join(inp, "/"), "a/b/c/d");
	EXPECT_EQ(ds::join(inp, "/", true), "a/b/c/d/");
}

TEST_F(TestStr, JoinStringsEmpty) {
	std::vector<std::string> inp;

	EXPECT_EQ(inp.size(), 0);
	EXPECT_EQ(ds::join(inp, "/"), "");
	EXPECT_EQ(ds::join(inp, "/", true), "");
}
