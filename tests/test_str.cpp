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
	EXPECT_EQ(ds::join(inp, "/"), "/a/b/c/d");
	EXPECT_EQ(ds::join(inp, "/", true, true), "/a/b/c/d/");
	EXPECT_EQ(ds::join(inp, "/", false, true), "a/b/c/d/");
	EXPECT_EQ(ds::join(inp, "/", false, true), "a/b/c/d/");
	EXPECT_EQ(ds::join(inp, "/", false, false), "a/b/c/d");
}

TEST_F(TestStr, JoinStringsEmpty) {
	std::vector<std::string> inp;

	EXPECT_EQ(inp.size(), 0);
	EXPECT_EQ(ds::join(inp, "/"), "");
	EXPECT_EQ(ds::join(inp, "/", true, true), "");
	EXPECT_EQ(ds::join(inp, "/", false, true), "");
	EXPECT_EQ(ds::join(inp, "/", true, false), "");
	EXPECT_EQ(ds::join(inp, "/", false, false), "");
}

TEST_F(TestStr, RemoveStringOccurrences) {
	std::vector<std::string> v {"a", "b", "c", "d", "e", "c"};

	EXPECT_EQ(v.size(), 6);
	EXPECT_EQ(v[0], "a");
	EXPECT_EQ(v[1], "b");
	EXPECT_EQ(v[2], "c");
	EXPECT_EQ(v[3], "d");
	EXPECT_EQ(v[4], "e");
	EXPECT_EQ(v[5], "c");

	ds::removeFirstOccurrence(v, "c");

	EXPECT_EQ(v.size(), 5);
	EXPECT_EQ(v[0], "a");
	EXPECT_EQ(v[1], "b");
	EXPECT_EQ(v[2], "d");
	EXPECT_EQ(v[3], "e");
	EXPECT_EQ(v[4], "c");
}

TEST_F(TestStr, RemoveStringOccurrencesEmpty) {
	std::vector<std::string> v {"a", "b", "c", "d", "e", "c"};

	EXPECT_EQ(v.size(), 6);
	EXPECT_EQ(v[0], "a");
	EXPECT_EQ(v[1], "b");
	EXPECT_EQ(v[2], "c");
	EXPECT_EQ(v[3], "d");
	EXPECT_EQ(v[4], "e");
	EXPECT_EQ(v[5], "c");

	ds::removeFirstOccurrence(v, "");

	EXPECT_EQ(v.size(), 6);
	EXPECT_EQ(v[0], "a");
	EXPECT_EQ(v[1], "b");
	EXPECT_EQ(v[2], "c");
	EXPECT_EQ(v[3], "d");
	EXPECT_EQ(v[4], "e");
	EXPECT_EQ(v[5], "c");

	v.clear();

	EXPECT_EQ(v.size(), 0);

	ds::removeFirstOccurrence(v, "42");
	ds::removeFirstOccurrence(v, "");

	EXPECT_EQ(v.size(), 0);
}

TEST_F(TestStr, ContainsSubstring) {
	std::string s = "a/b/c/d";
	std::vector<std::string> sub1 {"/", "%", "5"};
	std::vector<std::string> sub2 {"|", "%", "5"};

	EXPECT_TRUE(ds::containsAnySubstring(s, sub1));
	EXPECT_FALSE(ds::containsAnySubstring(s, sub2));
}

TEST_F(TestStr, ContainsSubstringEmpty) {
	std::string s = "";
	std::vector<std::string> sub1 {"", "1"};
	std::vector<std::string> sub2 {};

	EXPECT_FALSE(ds::containsAnySubstring(s, sub1));
	EXPECT_FALSE(ds::containsAnySubstring(s, sub2));
	EXPECT_FALSE(ds::containsAnySubstring("abc", sub2));
}
