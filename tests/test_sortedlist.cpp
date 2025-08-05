#include <testing_base.h>

#include <ds/Match.hpp>
#include <ds/SortedList.hpp>
#include <iostream>
#include <string>
#include <utility>

class TestSortedList : public TestingBase {
public:

	TestSortedList() : TestingBase() {}
};

TEST_F(TestSortedList, Create) {
	ds::SortedList<int> slist;

	EXPECT_EQ(slist.size(), 0);

	slist.insert(5);
	EXPECT_EQ(slist.size(), 1);
	EXPECT_EQ(slist.at(0), 5);
	EXPECT_EQ(**slist.getRoot(), 5);
	EXPECT_EQ(slist.minimum(), 5);
	EXPECT_EQ(slist.maximum(), 5);

	slist.insert(1);
	EXPECT_EQ(slist.size(), 2);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(slist.minimum(), 1);
	EXPECT_EQ(slist.maximum(), 5);

	slist.insert(3);
	EXPECT_EQ(slist.size(), 3);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 3);
	EXPECT_EQ(slist.at(2), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(slist.minimum(), 1);
	EXPECT_EQ(slist.maximum(), 5);

	slist.insert(2);
	EXPECT_EQ(slist.size(), 4);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 2);
	EXPECT_EQ(slist.at(2), 3);
	EXPECT_EQ(slist.at(3), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(slist.minimum(), 1);
	EXPECT_EQ(slist.maximum(), 5);

	slist.insert(4);
	EXPECT_EQ(slist.size(), 5);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 2);
	EXPECT_EQ(slist.at(2), 3);
	EXPECT_EQ(slist.at(3), 4);
	EXPECT_EQ(slist.at(4), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(slist.minimum(), 1);
	EXPECT_EQ(slist.maximum(), 5);

	slist.insert(6);
	EXPECT_EQ(slist.size(), 6);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 2);
	EXPECT_EQ(slist.at(2), 3);
	EXPECT_EQ(slist.at(3), 4);
	EXPECT_EQ(slist.at(4), 5);
	EXPECT_EQ(slist.at(5), 6);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(slist.minimum(), 1);
	EXPECT_EQ(slist.maximum(), 6);
}

TEST_F(TestSortedList, Constructors) {
	ds::SortedList<int> sl1 = {5, 1, 4, 2, 3};
	EXPECT_EQ(sl1.size(), 5);

	// Copy constructor
	ds::SortedList<int> sl2(sl1);
	EXPECT_EQ(sl1.size(), 5);
	EXPECT_EQ(sl1[0], 1);
	EXPECT_EQ(sl1[1], 2);
	EXPECT_EQ(sl1[2], 3);
	EXPECT_EQ(sl1[3], 4);
	EXPECT_EQ(sl1[4], 5);

	EXPECT_EQ(sl2.size(), 5);
	EXPECT_EQ(sl2[0], 1);
	EXPECT_EQ(sl2[1], 2);
	EXPECT_EQ(sl2[2], 3);
	EXPECT_EQ(sl2[3], 4);
	EXPECT_EQ(sl2[4], 5);

	// Move constructor
	ds::SortedList<int> sl3(std::move(sl2));

	EXPECT_EQ(sl3.size(), 5);
	EXPECT_EQ(sl3[0], 1);
	EXPECT_EQ(sl3[1], 2);
	EXPECT_EQ(sl3[2], 3);
	EXPECT_EQ(sl3[3], 4);
	EXPECT_EQ(sl3[4], 5);

	EXPECT_EQ(sl2.size(), 0);
	EXPECT_EQ(sl2.root(), nullptr);
	EXPECT_EQ(sl2.front().use_count(), 0);
	EXPECT_EQ(sl2.back().use_count(), 0);
}

TEST_F(TestSortedList, Initializer) {
	ds::SortedList<int> slist = {5, 1, 4, 2, 3};

	EXPECT_EQ(slist.size(), 5);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 2);
	EXPECT_EQ(slist.at(2), 3);
	EXPECT_EQ(slist.at(3), 4);
	EXPECT_EQ(slist.at(4), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(slist.minimum(), 1);
	EXPECT_EQ(slist.maximum(), 5);
}

TEST_F(TestSortedList, Contains) {
	ds::SortedList<int> slist = {2, 3, 1, 5, 4};

	EXPECT_EQ(slist.size(), 5);
	EXPECT_TRUE(slist.contains(1));
	EXPECT_TRUE(slist.contains(5));
	EXPECT_TRUE(slist.contains(2));
	EXPECT_FALSE(slist.contains(7));

	ds::SortedList<int> slist2;

	EXPECT_EQ(slist2.size(), 0);
	EXPECT_FALSE(slist2.contains(1));
	EXPECT_FALSE(slist2.contains(999));
}

TEST_F(TestSortedList, Search) {
	ds::SortedList<int> slist = {5, 4, 3, 2, 1};
	ds::Match<int, ds::Node> match;

	EXPECT_EQ(slist.size(), 5);

	match = slist.find(1);

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data(), 1);
	EXPECT_TRUE(match.reference() != nullptr);

	match = slist.find(5);

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data(), 5);
	EXPECT_TRUE(match.reference() != nullptr);

	match = slist.find(3);

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data(), 3);
	EXPECT_TRUE(match.reference() != nullptr);

	match = slist.find(999);

	EXPECT_FALSE(match.found());
	EXPECT_EQ(match.data(), 0);
	EXPECT_TRUE(match.reference() == nullptr);

	ds::SortedList<int> slist2;

	EXPECT_EQ(slist2.size(), 0);

	match = slist2.find(1);

	EXPECT_FALSE(match.found());
	EXPECT_EQ(match.data(), 0);
	EXPECT_TRUE(match.reference() == nullptr);

	match = slist2.find(999);

	EXPECT_FALSE(match.found());
	EXPECT_EQ(match.data(), 0);
	EXPECT_TRUE(match.reference() == nullptr);
}

TEST_F(TestSortedList, ComplexSearch) {
	ds::SortedList<TestSearchClass> list;
	ds::Match<TestSearchClass, ds::Node> match;
	ds::SortedList<TestSearchClass>::Iterator it;

	list.insert(TestSearchClass("c"));
	list.insert(TestSearchClass("b"));
	list.insert(TestSearchClass("a"));

	EXPECT_EQ(list.size(), 3);

	it = list.begin();
	EXPECT_EQ((*it).data(), "a");
	EXPECT_EQ((*it.next()).data(), "b");
	EXPECT_EQ((*it.next()).data(), "c");
	EXPECT_EQ((*it.next()).data(), "");

	it = list.begin();
	TestSearchClass a = *it;
	EXPECT_EQ(a.data(), "a");

	match = list.find(TestSearchClass("a"));

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data().data(), "a");
	EXPECT_TRUE(match.reference() != nullptr);

	match = list.find(TestSearchClass("c"));

	EXPECT_TRUE(match.found());
	EXPECT_EQ(match.data().data(), "c");
	EXPECT_TRUE(match.reference() != nullptr);

	match = list.find(TestSearchClass("z"));

	EXPECT_FALSE(match.found());
	EXPECT_EQ(match.data().data(), "");
	EXPECT_TRUE(match.reference() == nullptr);
}

TEST_F(TestSortedList, EmptySearch) {
	ds::SortedList<TestSearchClass> list;
	ds::Match<TestSearchClass, ds::Node> match;

	EXPECT_EQ(list.size(), 0);

	match = list.find(TestSearchClass(""));
	EXPECT_FALSE(match.getFound());

	match = list.find(TestSearchClass("z"));
	EXPECT_FALSE(match.getFound());
}
