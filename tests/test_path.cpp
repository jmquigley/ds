#include <testing_base.h>

#include <ds/Path.hpp>
#include <iostream>
#include <string>
#include <vector>

class TestPath : public TestingBase {
public:

	TestPath() : TestingBase() {}
};

TEST_F(TestPath, Create) {
	ds::Path path;
	EXPECT_EQ(path.str(), "");

	// create with const char *
	path.newPath("a", "b", "c");
	EXPECT_EQ(path.size(), 3);
	EXPECT_EQ(path.str(), "/a/b/c/");
	EXPECT_EQ(path.currentPath(), "/a/b/c/");
	EXPECT_EQ(path.path(), "/a/b/c/");
	EXPECT_EQ(path.at(0), "a");
	EXPECT_EQ(path.at(1), "b");
	EXPECT_EQ(path.at(2), "c");

	std::cout << path << std::endl;

	path.clear();
	EXPECT_EQ(path.size(), 0);

	// create with std::string
	std::string s1 = "x";
	std::string s2 = "y";
	std::string s3 = "z";

	ds::Path path2(s1, s2, s3);
	EXPECT_EQ(path2.size(), 3);
	EXPECT_EQ(path2.str(), "/x/y/z/");
	EXPECT_EQ(path2[0], "x");
	EXPECT_EQ(path2[1], "y");
	EXPECT_EQ(path2[2], "z");

	std::cout << path2 << std::endl;

	~path2;
	EXPECT_EQ(path2.size(), 0);

	path("p", "d", "q");

	EXPECT_EQ(path.size(), 3);
	EXPECT_EQ(path.str(), "/p/d/q/");
	EXPECT_EQ(path[0], "p");
	EXPECT_EQ(path[1], "d");
	EXPECT_EQ(path[2], "q");

	path.newPath("a", "b", "c");

	EXPECT_EQ(path.size(), 3);
	EXPECT_EQ(path.str(), "/a/b/c/");
	EXPECT_EQ(path.at(0), "a");
	EXPECT_EQ(path.at(1), "b");
	EXPECT_EQ(path.at(2), "c");
};

TEST_F(TestPath, InitializerList) {
	ds::Path path {"a", "b", "c"};
	EXPECT_EQ(path.size(), 3);
	EXPECT_EQ(path.str(), "/a/b/c/");
}

TEST_F(TestPath, CopyConstructor) {
	ds::Path path1("a", "b", "c");
	ds::Path path2(path1);
	ds::Path path3 = path1;

	EXPECT_EQ(path1.size(), 3);
	EXPECT_EQ(path1.str(), "/a/b/c/");

	EXPECT_EQ(path2.size(), 3);
	EXPECT_EQ(path2.str(), "/a/b/c/");

	EXPECT_EQ(path3.size(), 3);
	EXPECT_EQ(path3.str(), "/a/b/c/");
}

TEST_F(TestPath, Comparisons) {
	ds::Path path1 {"a", "b", "c"};
	ds::Path path2 {"x", "y", "z"};

	EXPECT_TRUE(path1 == path1);
	EXPECT_FALSE(path1 == path2);

	EXPECT_TRUE(path1 != path2);
	EXPECT_FALSE(path1 != path1);

	path1 = "a";
	path2 = "b";

	EXPECT_TRUE(path1 < path2);
	EXPECT_TRUE(path2 > path1);
}

TEST_F(TestPath, Parsing) {
	ds::Path path;
	path = std::string("/a/b/c/");

	EXPECT_EQ(path.size(), 3);
	EXPECT_EQ(path.str(), "/a/b/c/");
	EXPECT_EQ(path.at(0), "a");
	EXPECT_EQ(path.at(1), "b");
	EXPECT_EQ(path.at(2), "c");

	path = "x/y/z";

	EXPECT_EQ(path.size(), 3);
	EXPECT_EQ(path.str(), "/x/y/z/");
	EXPECT_EQ(path.at(0), "x");
	EXPECT_EQ(path.at(1), "y");
	EXPECT_EQ(path.at(2), "z");

	path = "/////\\a||||b\\/////\\||c\\\\\\";
	EXPECT_EQ(path.size(), 3);
	EXPECT_EQ(path.str(), "/a/b/c/");
	EXPECT_EQ(path.at(0), "a");
	EXPECT_EQ(path.at(1), "b");
	EXPECT_EQ(path.at(2), "c");
}

TEST_F(TestPath, Append) {
	ds::Path path;

	EXPECT_EQ(path.size(), 0);

	path += "a";
	path += "b";
	path += "c";
	path.append(std::string(1, 'd'));
	path.append(std::string(1, 'e'));

	EXPECT_EQ(path.size(), 5);
	EXPECT_EQ(path.str(), "/a/b/c/d/e/");
	EXPECT_EQ(path.at(0), "a");
	EXPECT_EQ(path.at(1), "b");
	EXPECT_EQ(path.at(2), "c");
	EXPECT_EQ(path.at(3), "d");
	EXPECT_EQ(path.at(4), "e");
}

TEST_F(TestPath, Remove) {
	ds::Path path {"a", "b", "c", "d", "e"};

	EXPECT_EQ(path.size(), 5);
	EXPECT_EQ(path.str(), "/a/b/c/d/e/");
	EXPECT_EQ(path.at(0), "a");
	EXPECT_EQ(path.at(1), "b");
	EXPECT_EQ(path.at(2), "c");
	EXPECT_EQ(path.at(3), "d");
	EXPECT_EQ(path.at(4), "e");

	path.removeIndex(0);

	EXPECT_EQ(path.size(), 4);
	EXPECT_EQ(path.str(), "/b/c/d/e/");
	EXPECT_EQ(path.at(0), "b");
	EXPECT_EQ(path.at(1), "c");
	EXPECT_EQ(path.at(2), "d");
	EXPECT_EQ(path.at(3), "e");

	path.removeValue("c");

	EXPECT_EQ(path.size(), 3);
	EXPECT_EQ(path.str(), "/b/d/e/");
	EXPECT_EQ(path.at(0), "b");
	EXPECT_EQ(path.at(1), "d");
	EXPECT_EQ(path.at(2), "e");
}
