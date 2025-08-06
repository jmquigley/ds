#include <ds/GeneralTreeNode.hpp>
#include <iostream>

int main(int argc, char **argv) {
	ds::GeneralTreeNode<int> gtn("a", 42, "a\\");
	ds::Match<int, ds::GeneralTreeNode> match;

	std::cout << sizeof(match) << std::endl;

	return 0;
}
