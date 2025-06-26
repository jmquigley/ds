#include <iostream>

#include "ds.h"

int main(int argc, char **argv) {
	std::cout << "Node size: " << sizeof(ds::Node<int>) << std::endl;
    std::cout << "unsigned int size: " << sizeof(int) << std::endl;
	return 0;
}
