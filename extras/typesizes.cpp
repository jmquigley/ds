#include <format>
#include <iostream>
#include <memory>

#include "ds.h"

int main(int argc, char **argv) {
	std::shared_ptr<int> p = std::make_shared<int>(42);
	std::weak_ptr<int> wp = p;

	std::cout << std::format("Node size: {}", sizeof(ds::Node<int>)) << std::endl;
	std::cout << std::format("unsigned int size: {}", sizeof(int)) << std::endl;
	std::cout << std::format("size_t size: {}", sizeof(int)) << std::endl;
	std::cout << std::format("shared ptr size: {}", sizeof(p)) << std::endl;
	std::cout << std::format("weak ptr size: {}", sizeof(wp)) << std::endl;

	return 0;
}
