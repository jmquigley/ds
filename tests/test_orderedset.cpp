#include <testing_base.h>

#include <ds/Match.hpp>
#include <ds/OrderedSet.hpp>
#include <iostream>
#include <string>

class TestOrderedSet : public TestingBase {
public:

	TestOrderedSet() : TestingBase() {}
};

TEST_F(TestOrderedSet, Create) {
	ds::OrderedSet<int> set {1, 1, 2, 3, 4, 5};

	EXPECT_EQ(set.size(), 5);
	EXPECT_EQ(set[0], 1);
	EXPECT_EQ(set[1], 2);
	EXPECT_EQ(set[2], 3);
	EXPECT_EQ(set[3], 4);
	EXPECT_EQ(set[4], 5);

	EXPECT_TRUE(set.contains(1));
	EXPECT_TRUE(set.contains(2));
	EXPECT_TRUE(set.contains(5));
	EXPECT_FALSE(set.contains(666));
}

TEST_F(TestOrderedSet, Constructors) {
	ds::OrderedSet<int> set1 {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};

	EXPECT_EQ(set1.size(), 5);
	EXPECT_EQ(set1[0], 1);
	EXPECT_EQ(set1[1], 2);
	EXPECT_EQ(set1[2], 3);
	EXPECT_EQ(set1[3], 4);
	EXPECT_EQ(set1[4], 5);

	// Copy constructor
	ds::OrderedSet<int> set2(set1);

	EXPECT_EQ(set1.size(), 5);
	EXPECT_EQ(set1[0], 1);
	EXPECT_EQ(set1[1], 2);
	EXPECT_EQ(set1[2], 3);
	EXPECT_EQ(set1[3], 4);
	EXPECT_EQ(set1[4], 5);

	EXPECT_EQ(set2.size(), 5);
	EXPECT_EQ(set2[0], 1);
	EXPECT_EQ(set2[1], 2);
	EXPECT_EQ(set2[2], 3);
	EXPECT_EQ(set2[3], 4);
	EXPECT_EQ(set2[4], 5);

	// Move constructor
	ds::SortedList<int> set3(std::move(set2));

	EXPECT_EQ(set3.size(), 5);
	EXPECT_EQ(set3[0], 1);
	EXPECT_EQ(set3[1], 2);
	EXPECT_EQ(set3[2], 3);
	EXPECT_EQ(set3[3], 4);
	EXPECT_EQ(set3[4], 5);

	EXPECT_EQ(set2.size(), 0);
	EXPECT_EQ(set2.root(), nullptr);
	EXPECT_EQ(set2.front().use_count(), 0);
	EXPECT_EQ(set2.back().use_count(), 0);
}

TEST_F(TestOrderedSet, Initializer) {
	ds::OrderedSet<int> set1 {5, 5, 1, 1, 3, 2, 3, 2, 4, 4};

	EXPECT_EQ(set1.size(), 5);
	EXPECT_EQ(set1[0], 1);
	EXPECT_EQ(set1[1], 2);
	EXPECT_EQ(set1[2], 3);
	EXPECT_EQ(set1[3], 4);
	EXPECT_EQ(set1[4], 5);

	ds::OrderedSet<int> set2 = {5, 5, 1, 1, 3, 2, 3, 2, 4, 4};

	EXPECT_EQ(set2.size(), 5);
	EXPECT_EQ(set2[0], 1);
	EXPECT_EQ(set2[1], 2);
	EXPECT_EQ(set2[2], 3);
	EXPECT_EQ(set2[3], 4);
	EXPECT_EQ(set2[4], 5);
}

TEST_F(TestOrderedSet, Contains) {
	ds::OrderedSet<int> set = {5, 5, 1, 1, 3, 2, 3, 2, 4, 4};

	EXPECT_EQ(set.size(), 5);
	EXPECT_TRUE(set.contains(1));
	EXPECT_TRUE(set.contains(5));
	EXPECT_TRUE(set.contains(2));
	EXPECT_FALSE(set.contains(7));

	ds::OrderedSet<int> set2;

	EXPECT_EQ(set2.size(), 0);
	EXPECT_FALSE(set2.contains(1));
	EXPECT_FALSE(set2.contains(999));
}

TEST_F(TestOrderedSet, Search) {
	ds::OrderedSet<int> set = {5, 4, 3, 2, 1};
	ds::Match<int, ds::Node> match;

	EXPECT_EQ(set.size(), 5);

	match = set.find(1);

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data(), 1);
	EXPECT_TRUE(match.pointer() != nullptr);

	match = set.find(5);

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data(), 5);
	EXPECT_TRUE(match.pointer() != nullptr);

	match = set.find(3);

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data(), 3);
	EXPECT_TRUE(match.pointer() != nullptr);

	match = set.find(999);

	EXPECT_FALSE(match.found());
	EXPECT_EQ(match.data(), 0);
	EXPECT_TRUE(match.pointer() == nullptr);

	ds::OrderedSet<int> set2;

	EXPECT_EQ(set2.size(), 0);

	match = set2.find(1);

	EXPECT_FALSE(match.found());
	EXPECT_EQ(match.data(), 0);
	EXPECT_TRUE(match.pointer() == nullptr);

	match = set2.find(999);

	EXPECT_FALSE(match.found());
	EXPECT_EQ(match.data(), 0);
	EXPECT_TRUE(match.pointer() == nullptr);
}

TEST_F(TestOrderedSet, ComplexTypeSearch) {
	ds::OrderedSet<TestSearchClass> set;
	ds::Match<TestSearchClass, ds::Node> match;
	ds::OrderedSet<TestSearchClass>::Iterator it;

	set.insert(TestSearchClass("c"));
	set.insert(TestSearchClass("c"));
	set.insert(TestSearchClass("a"));
	set.insert(TestSearchClass("a"));
	set.insert(TestSearchClass("b"));
	set.insert(TestSearchClass("b"));

	EXPECT_EQ(set.size(), 3);

	it = set.begin();
	EXPECT_EQ((*it).data(), "a");
	EXPECT_EQ((*it.next()).data(), "b");
	EXPECT_EQ((*it.next()).data(), "c");
	EXPECT_EQ((*it.next()).data(), "");

	match = set.find(TestSearchClass("a"));

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data().data(), "a");
	EXPECT_TRUE(match.pointer() != nullptr);

	match = set.find(TestSearchClass("c"));

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data().data(), "c");
	EXPECT_TRUE(match.pointer() != nullptr);

	match = set.find(TestSearchClass("z"));

	EXPECT_FALSE(match.found());
	EXPECT_EQ(match.data().data(), "");
	EXPECT_TRUE(match.pointer() == nullptr);
}

TEST_F(TestOrderedSet, EmptySearch) {
	ds::OrderedSet<TestSearchClass> set;
	ds::Match<TestSearchClass, ds::Node> match;

	EXPECT_EQ(set.size(), 0);

	match = set.find(TestSearchClass(""));
	EXPECT_FALSE(match.getFound());

	match = set.find(TestSearchClass("z"));
	EXPECT_FALSE(match.getFound());
}

TEST_F(TestOrderedSet, Iterator) {
	ds::OrderedSet<int> set {4, 5, 2, 1, 1, 2, 2, 3};

	EXPECT_EQ(set.size(), 5);

	size_t i = 0;
	for (const auto &it: set) {
		std::cout << "it: " << it << std::endl;

		switch (i) {
			case 0:
				EXPECT_EQ(it, 1);
				break;

			case 1:
				EXPECT_EQ(it, 2);
				break;

			case 2:
				EXPECT_EQ(it, 3);
				break;

			case 3:
				EXPECT_EQ(it, 4);
				break;

			case 4:
				EXPECT_EQ(it, 5);
				break;
		}

		i++;
	}
}

TEST_F(TestOrderedSet, Each) {
	ds::OrderedSet<int> set {1, 5, 4, 3, 4, 2, 5};

	EXPECT_EQ(set.size(), 5);
	EXPECT_EQ(set[0], 1);
	EXPECT_EQ(set[1], 2);
	EXPECT_EQ(set[2], 3);
	EXPECT_EQ(set[3], 4);
	EXPECT_EQ(set[4], 5);

	set.each([&](size_t index, auto &x) { x *= 2; });

	EXPECT_EQ(set.size(), 5);
	EXPECT_EQ(set[0], 2);
	EXPECT_EQ(set[1], 4);
	EXPECT_EQ(set[2], 6);
	EXPECT_EQ(set[3], 8);
	EXPECT_EQ(set[4], 10);
}

TEST_F(TestOrderedSet, EmptyEach) {
	ds::OrderedSet<int> set {};

	EXPECT_EQ(set.size(), 0);
	set.each([&](size_t index, auto &x) { x *= 2; });
	EXPECT_EQ(set.size(), 0);
}
