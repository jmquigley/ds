#include <testing_base.h>

#include <ds/BaseIterator.hpp>
#include <ds/Node.hpp>
#include <iostream>
#include <stdexcept>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

class TestIterator : public TestingBase {
protected:

	std::shared_ptr<ds::Node<int>> root;
	std::shared_ptr<ds::Node<int>> n1;
	std::shared_ptr<ds::Node<int>> n2;
	std::shared_ptr<ds::Node<int>> n3;

	auto SetUp() -> void override {
		n1 = std::make_shared<ds::Node<int>>(1);
		n2 = std::make_shared<ds::Node<int>>(2);
		n3 = std::make_shared<ds::Node<int>>(3);

		n1->setRight(n2);
		n2->setRight(n3);
		n2->setLeft(n1);
		n3->setLeft(n2);

		this->root = n1;
	}

	void TearDown() override {
		n3->clear();
		n2->clear();
		n1->clear();
		root.reset();
	}

	static void validateRootIterator(ds::BaseIterator<int, ds::Node> &it) {
		std::cout << "it(1): " << *it << std::endl;
		EXPECT_EQ(*it, 1);
		it.next();
		std::cout << "it(2): " << *it << std::endl;
		EXPECT_EQ(*it, 2);
		it.next();
		std::cout << "it(3): " << *it << std::endl;
		EXPECT_EQ(*it, 3);
	}

public:

	TestIterator() = default;
};

class LocalIterator : public ds::BaseIterator<int, ds::Node> {
public:

	LocalIterator(std::weak_ptr<ds::Node<int>> lp)
		: ds::BaseIterator<int, ds::Node>(lp) {}

	LocalIterator() = default;
};

TEST_F(TestIterator, Create) {
	LocalIterator it(root);
	validateRootIterator(it);
};

TEST_F(TestIterator, CopyConstructor) {
	LocalIterator it1(root);
	LocalIterator it2(it1);

	EXPECT_TRUE(it1 == it2);

	validateRootIterator(it1);
	validateRootIterator(it2);
}

TEST_F(TestIterator, BadCopyConstructor) {
	LocalIterator it1;
	LocalIterator it2(it1);
	EXPECT_TRUE(it1 == it2);
}

TEST_F(TestIterator, MoveConstructor) {
	LocalIterator it1(root);
	LocalIterator it2(std::move(it1));
	validateRootIterator(it2);
	EXPECT_TRUE(it1.lp().expired());
}

TEST_F(TestIterator, BadMoveConstructor) {
	LocalIterator it1;
	LocalIterator it2(std::move(it1));
	EXPECT_TRUE(it1.lp().expired());
}

TEST_F(TestIterator, AssignmentOperators) {
	// Assignment operator
	LocalIterator it1(root);
	LocalIterator it2;

	it2 = it1;
	validateRootIterator(it2);

	// Move assignment operator
	LocalIterator it3(root);
	it2 = std::move(it3);
	validateRootIterator(it2);
	EXPECT_TRUE(it3.lp().expired());
}

TEST_F(TestIterator, Replication) {
	LocalIterator it(root);
	auto itc = *it.deepcopy().get();

	validateRootIterator(it);
	validateRootIterator(itc);
}

TEST_F(TestIterator, Each) {
	LocalIterator itr(root);

	itr.each([&](size_t index, auto &it) {
		if (index == 0) {
			EXPECT_EQ(*it, 1);
		} else if (index == 1) {
			EXPECT_EQ(*it, 2);
		} else if (index == 2) {
			EXPECT_EQ(*it, 3);
		}
	});
}

TEST_F(TestIterator, BadEach) {
	LocalIterator itr;
	itr.each([&](size_t index, auto &it) { EXPECT_TRUE(false); });
}

TEST_F(TestIterator, CallOperator) {
	LocalIterator it;
	it(root);
	validateRootIterator(it);
}

TEST_F(TestIterator, Compare) {
	LocalIterator it1(root);
	LocalIterator it2(root);

	EXPECT_TRUE(it1 == it2);
	EXPECT_FALSE(it1 != it2);

	LocalIterator it3(n1);
	LocalIterator it4(n2);

	EXPECT_FALSE(it3 == it4);
	EXPECT_TRUE(it3 != it4);
}

TEST_F(TestIterator, Boolean) {
	// simple logic truth
	LocalIterator it1(root);

	EXPECT_TRUE(it1);
	EXPECT_FALSE(!it1);

	// and
	LocalIterator it2(root);
	EXPECT_TRUE(it1 && it2);
}

TEST_F(TestIterator, Increment) {
	LocalIterator it(root);

	std::cout << "(1): " << *it << std::endl;
	EXPECT_EQ(*it, 1);
	it++;
	std::cout << "(2): " << *it << std::endl;
	EXPECT_EQ(*it, 2);
	it++;
	std::cout << "(3): " << *it << std::endl;
	EXPECT_EQ(*it, 3);
}

TEST_F(TestIterator, BadIncrement) {
	LocalIterator it;
	EXPECT_THROW(it++, std::runtime_error);
	EXPECT_THROW(++it, std::runtime_error);
}

TEST_F(TestIterator, Decrement) {
	LocalIterator it(root->getRight()->getRight());

	std::cout << "(1): " << *it << std::endl;
	EXPECT_EQ(*it, 3);
	it--;
	std::cout << "(2): " << *it << std::endl;
	EXPECT_EQ(*it, 2);
	it--;
	std::cout << "(3): " << *it << std::endl;
	EXPECT_EQ(*it, 1);
}

TEST_F(TestIterator, BadDecrement) {
	LocalIterator it;
	EXPECT_THROW(it--, std::runtime_error);
	EXPECT_THROW(--it, std::runtime_error);
}

TEST_F(TestIterator, ForLoop) {
	LocalIterator itb(root);
	LocalIterator ite;
	int i = 0;

	for (auto it = itb; it != ite; ++it) {
		if (i == 0) {
			EXPECT_EQ(*it, 1);
		} else if (i == 1) {
			EXPECT_EQ(*it, 2);
		} else if (i == 2) {
			EXPECT_EQ(*it, 3);
		}

		i++;
	}
}

TEST_F(TestIterator, Empty) {
	LocalIterator it;
	EXPECT_THROW(*it, std::runtime_error);
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
