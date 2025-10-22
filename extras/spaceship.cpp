#include <compare>
#include <iostream>

class A {
public:

	unsigned int x;
	unsigned int y;

	A(unsigned int x, unsigned int y) : x {x}, y {y} {};

	auto operator<=>(const A &other) const = default;
};

class B {
public:

	unsigned int x;

	B(unsigned int x) : x {x} {};

	std::strong_ordering operator<=>(const B &other) const {
		std::strong_ordering order = std::strong_ordering::greater;

		if (x < other.x) {
			order = std::strong_ordering::less;
		} else if (x == other.x) {
			order = std::strong_ordering::equal;
		}

		return order;
	}

	bool operator==(const B &other) const {
		return this->x == other.x;
	}
};

int main(int argc, char **argv) {
	std::cout << "spaceship comparison test" << std::endl;

	A a {1, 2};
	A b {2, 3};
	A c {1, 2};

	if (a == b) {
		std::cout << "A: a and b are equal" << std::endl;
	} else {
		std::cout << "A: a and b are NOT equal" << std::endl;
	}

	if (a == a) {
		std::cout << "B: a == a are equal" << std::endl;
	}

	if (a == c) {
		std::cout << "B: a and c are equal" << std::endl;
	} else {
		std::cout << "B: a and c are NOT equal" << std::endl;
	}

	B d {1};
	B e {2};

	if (d == d) {
		std::cout << "B: d == d are equal" << std::endl;
	}

	return 0;
}
