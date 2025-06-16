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

	EXPECT_EQ(slist.getSize(), 0);
}
