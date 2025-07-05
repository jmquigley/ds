#include <iostream>
#include <memory>

class Base {
protected:

	int x;

public:

	Base() {
		x = 42;
	}

	virtual int get() {
		return x;
	}
};

class Derived : public Base {
public:

	Derived() : Base() {
		x = 24;
	}
};

int main(int argc, char **argv) {
	Base base;
	Derived derived;

	// A shared pointer to the base class using "base" variable
	std::shared_ptr<Base> bp(std::make_shared<Base>(base));
	std::cout << "bp: " << bp->get() << std::endl;

	// A shared pointer to the derived class using "derived" variable
	std::shared_ptr<Derived> dp(std::make_shared<Derived>(derived));
	std::cout << "dp: " << dp->get() << std::endl;

	// Casting the derived pointer to its base type
	std::shared_ptr<Base> p = std::static_pointer_cast<Base>(dp);
	std::cout << "p: " << p->get() << std::endl;

	return 0;
}
