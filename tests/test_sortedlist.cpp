#include <iostream>
#include <string>

#include "sortedlist.hpp"
#include "testing_base.h"

class TestSortedList : public TestingBase {
public:

	TestSortedList() : TestingBase() {}
};

TEST_F(TestSortedList, CreateList) {
	ds::SortedList<int> slist;

	EXPECT_EQ(slist.size(), 0);

	slist.insert(5);
	EXPECT_EQ(slist.size(), 1);
	EXPECT_EQ(slist.at(0), 5);
	EXPECT_EQ(**slist.getRoot(), 5);
	EXPECT_EQ(**slist.getFront(), 5);
	EXPECT_EQ(**slist.getBack(), 5);

	slist.insert(1);
	EXPECT_EQ(slist.size(), 2);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(**slist.getFront(), 1);
	EXPECT_EQ(**slist.getBack(), 5);

	slist.insert(3);
	EXPECT_EQ(slist.size(), 3);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 3);
	EXPECT_EQ(slist.at(2), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(**slist.getFront(), 1);
	EXPECT_EQ(**slist.getBack(), 5);

	slist.insert(2);
	EXPECT_EQ(slist.size(), 4);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 2);
	EXPECT_EQ(slist.at(2), 3);
	EXPECT_EQ(slist.at(3), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(**slist.getFront(), 1);
	EXPECT_EQ(**slist.getBack(), 5);

	slist.insert(4);
	EXPECT_EQ(slist.size(), 5);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 2);
	EXPECT_EQ(slist.at(2), 3);
	EXPECT_EQ(slist.at(3), 4);
	EXPECT_EQ(slist.at(4), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(**slist.getFront(), 1);
	EXPECT_EQ(**slist.getBack(), 5);

	slist.insert(6);
	EXPECT_EQ(slist.size(), 6);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 2);
	EXPECT_EQ(slist.at(2), 3);
	EXPECT_EQ(slist.at(3), 4);
	EXPECT_EQ(slist.at(4), 5);
	EXPECT_EQ(slist.at(5), 6);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(**slist.getFront(), 1);
	EXPECT_EQ(**slist.getBack(), 6);
}

TEST_F(TestSortedList, SortedListInitializer) {
	ds::SortedList<int> slist = {5, 1, 4, 2, 3};

	EXPECT_EQ(slist.size(), 5);
	EXPECT_EQ(slist.at(0), 1);
	EXPECT_EQ(slist.at(1), 2);
	EXPECT_EQ(slist.at(2), 3);
	EXPECT_EQ(slist.at(3), 4);
	EXPECT_EQ(slist.at(4), 5);
	EXPECT_EQ(**slist.getRoot(), 1);
	EXPECT_EQ(**slist.getFront(), 1);
	EXPECT_EQ(**slist.getBack(), 5);
}

TEST_F(TestSortedList, SortedListCopyConstructor) {
	ds::SortedList<int> sl1 = {5, 1, 4, 2, 3};
	EXPECT_EQ(sl1.size(), 5);

	ds::SortedList<int> sl2(sl1);
	EXPECT_EQ(sl2.size(), 5);
	EXPECT_EQ(sl2.at(0), 1);
	EXPECT_EQ(sl2.at(1), 2);
	EXPECT_EQ(sl2.at(2), 3);
	EXPECT_EQ(sl2.at(3), 4);
	EXPECT_EQ(sl2.at(4), 5);
}

TEST_F(TestSortedList, Contains) {
	ds::List<int> slist = {1, 2, 3, 4, 5};

	EXPECT_EQ(slist.size(), 5);
	EXPECT_TRUE(slist.contains(1));
	EXPECT_FALSE(slist.contains(7));
}
