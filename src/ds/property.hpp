/**
 * @brief Macros used to define data values in a class along with their
 * getters and setters.
 */

#pragma once

// Creates a getter function for the given variable
#define ACCESSOR(variable, fn, dtype)        \
                                             \
public:                                      \
                                             \
	auto get##fn() const noexcept -> dtype { \
		return this->_##variable;            \
	}                                        \
                                             \
	auto variable() const -> const dtype & { \
		return this->_##variable;            \
	}

#define ACCESSOR_NO_CONST(variable, fn, dtype) \
                                               \
public:                                        \
                                               \
	auto get##fn() noexcept -> dtype {         \
		return this->_##variable;              \
	}                                          \
                                               \
	auto variable() noexcept -> dtype & {      \
		return this->_##variable;              \
	}

// Creates a setter function for the given variable
#define MUTATOR(variable, fn, dtype)             \
                                                 \
public:                                          \
                                                 \
	auto set##fn(dtype value) noexcept -> void { \
		this->_##variable = value;               \
	};

/**
 * Creates a variable within a class as a property with a get/set function
 * Just note that this macro adds scope operators to the class, so
 * once the macro finishes the current scope after the macro will be
 * public.
 *
 * The accessor/mutators are always public.
 *
 * There are six types of property macros:
 *
 * 1. PROPERTY - a defines a variable and getter/setter
 * 2. PROPERTY_NO_CONST - defaults a variable getter/setter, where the getter
 *    reference is not marked as a const function
 * 3. PROPERTY_WITH_DEFAULT - same as PROPERTY with a default value initializer
 * 4. PROPERTY_WITH_DEFAULT_NO_CONST - same as PROPERT_NO_CONST with a default
 *    value initializer.
 * 5. PROPERTY_READONLY - a property with only an accessor, but not setter
 * 6. PROPERTY_READONLY_WITH_DEFAULT - same as PROPERTY_READONLY with a default
 *    value initializer
 * 7. PROPERTY_SCOPED - a property where the default variable scope can
 *    be changed from private.
 * 8. PROPERTY_SCOPED_NO_CONST - same as PROPERTY_SCOPED, but the getter is not
 *    a const function
 * 9. PROPERTY_SCOPED_WITH_DEFAULT - same as PROPERTY_SCOPED with a default
 *    value initializer
 *
 * Example:
 *
 *    class Foo {
 *        PROPERTY(bar, Bar, unsigned int);
 *        PROPERTY_WITH_DEFAULT(baz, Baz, std::string, ="something");
 *        PROPERTY_WITH_DEFAULT(zab, Zab, int, =99);
 *        PROPERTY_SCOPED(foo, Foo, unsigned int, properties:);
 *    }
 *
 *   In the example above, the variable `_bar` is created.
 *   There are two getter functions created: `getBar()` and `bar()`
 *   There is one setter function created: `setBar({value})`
 *
 * Parameters:
 *     - variable (`string`) -- the name of the variable to create
 *     - fn (`string`) -- the Pascal case function name of the get/set function
 *     - dtype (`string`) -- the data type for the variable
 *     - scope (``) -- the access scope level of the variable
 *     - def (`string`) -- a default value initializer for the variable
 *
 * Returns:
 *     n/a
 */
#define PROPERTY_SCOPED_WITH_DEFAULT(variable, fn, dtype, scope, def) \
	scope dtype _##variable def;                                      \
	ACCESSOR(variable, fn, dtype);                                    \
	MUTATOR(variable, fn, dtype);

#define PROPERTY_SCOPED_WITH_DEFAULT_NO_CONST(variable, fn, dtype, scope, def) \
	scope dtype _##variable def;                                               \
	ACCESSOR_NO_CONST(variable, fn, dtype);                                    \
	MUTATOR(variable, fn, dtype);

#define PROPERTY_SCOPED(variable, fn, dtype, scope) \
	PROPERTY_SCOPED_WITH_DEFAULT(variable, fn, dtype, scope, );

#define PROPERTY_SCOPED_NO_CONST(variable, fn, dtype, scope) \
	PROPERTY_SCOPED_WITH_DEFAULT_NO_CONST(variable, fn, dtype, scope)

#define PROPERTY_WITH_DEFAULT(variable, fn, dtype, def) \
	PROPERTY_SCOPED_WITH_DEFAULT(variable, fn, dtype, private:, def);

#define PROPERTY_WITH_DEFAULT_NO_CONST(variable, fn, dtype, def) \
	PROPERTY_SCOPED_WITH_DEFAULT_NO_CONST(variable, fn, dtype, private:, def);

#define PROPERTY(variable, fn, dtype) \
	PROPERTY_WITH_DEFAULT(variable, fn, dtype, );

#define PROPERTY_NO_CONST(variable, fn, dtype) \
	PROPERTY_WITH_DEFAULT_NO_CONST(variable, fn, dtype, );

#define PROPERTY_READONLY_WITH_DEFAULT(variable, fn, dtype, def) \
                                                                 \
private:                                                         \
                                                                 \
	dtype _##variable def;                                       \
	ACCESSOR(variable, fn, dtype);

#define PROPERTY_READONLY(variable, fn, dtype) \
	PROPERTY_READONLY_WITH_DEFAULT(variable, fn, dtype, );
