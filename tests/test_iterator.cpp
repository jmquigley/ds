#include "test_objects.h"

#include <iostream>
#include <string>

#include "iterator.hpp"
#include "node.hpp"

TestIterator::TestIterator(): TestingBase() {
	memset(temp, 0, sizeof(temp));
	bufptr = nullptr;
};

class LocalIterator : public ds::IteratorBase<int> {
public:
	LocalIterator(std::weak_ptr<ds::Node<int>> lp) : ds::IteratorBase<int>(lp) {}
};

TEST_F(TestIterator, CreateIterator) {
    std::shared_ptr<ds::Node<int>> root = std::make_shared<ds::Node<int>>(1);
    root->setRight(std::make_shared<ds::Node<int>>(2));
    root->getRight()->setRight(std::make_shared<ds::Node<int>>(3));

    LocalIterator it(root);

    std::cout << "(1): " << *it << std::endl;
    EXPECT_EQ(*it, 1);
    it.next();
    std::cout << "(2): " << *it << std::endl;
    EXPECT_EQ(*it, 2);
    it.next();
    std::cout << "(3): " << *it << std::endl;
    EXPECT_EQ(*it, 3);
};
