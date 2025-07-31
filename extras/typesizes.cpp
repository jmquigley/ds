#include <ds/ds.h>

#include <format>
#include <iostream>
#include <memory>

int main(int argc, char **argv) {
	std::shared_ptr<int> p = std::make_shared<int>(42);
	std::weak_ptr<int> wp = p;

	std::cout << std::format("Node size: {}", sizeof(ds::Node<int>))
			  << std::endl
			  << std::format("TreeNode size: {}", sizeof(ds::TreeNode<int>))
			  << std::endl
			  << std::format("GeneralTreeNode: {}",
							 sizeof(ds::GeneralTreeNode<int>))
			  << std::endl
			  << std::format("Path: {}", sizeof(ds::Path)) << std::endl
			  << std::format("unsigned int size: {}", sizeof(int)) << std::endl
			  << std::format("size_t size: {}", sizeof(int)) << std::endl
			  << std::format("shared ptr size: {}", sizeof(p)) << std::endl
			  << std::format("weak ptr size: {}", sizeof(wp)) << std::endl;

	return 0;
}
