#include <iostream>
#include <memory>

template<typename Derived>
class Base {
public:

	// Methods in Base can access members of Derived through static_cast<Derived*>(this)
	void baseMethod() {
		static_cast<Derived *>(this)->derivedSpecificMethod();
	}

public:

	// Public interface
};

class Derived : public Base<Derived> {
public:

	void derivedSpecificMethod() {
		// Implementation specific to Derived
		std::cout << "derivedSpecificMethod()" << std::endl;
	}
};

int main(int argc, char **argv) {
	Derived d;
	d.baseMethod();
}
