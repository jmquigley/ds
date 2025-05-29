#pragma once


// Creates a getter function for the given variable
#define ACCESSOR(variable, fn) \
    public: auto get##fn() const {return this->variable;}

// Creates a setter function for the given variable
#define MUTATOR(variable, fn, dtype) \
    public: void set##fn(dtype value) { \
        this->variable = value; \
    };

/**
 * Creates a variable within a class as a property with a get/set function
 * Just note that this macro adds scope operators to the class, so
 * once the macro finishes the current scope after the macro will be
 * public.
 *
 * Example:
 *
 *    class Foo {
 *        PROPERTY(bar, Bar, unsigned int);
 *        PROPERTY_D(baz, Baz, std::string, ="something");
 *        PROPERTY_D(zab, Zab, int, =99);
 *    }
 *
 * Parameters:
 *     - variable (`string`) -- the name of the variable to create
 *     - fn (`string`) -- the Pascal case function name of the get/set function
 *     - dtype (`string`) -- the data type for the variable
 *     - def (`string`) -- a default value initializer for the variable
 *
 * Returns:
 *     n/a
 */
#define PROPERTY_SCOPED_D(variable, fn, dtype, scope, def) \
    scope dtype variable def; \
    ACCESSOR(variable, fn); \
    MUTATOR(variable, fn, dtype);

#define PROPERTY_SCOPED(variable, fn, dtype, scope) \
    PROPERTY_SCOPED_D(variable, fn, dtype, scope, );

#define PROPERTY_D(variable, fn, dtype, def) \
    PROPERTY_SCOPED_D(variable, fn, dtype, private:, def);

#define PROPERTY(variable, fn, dtype) \
    PROPERTY_D(variable, fn, dtype, );

#define PROPERTY_READONLY_D(variable, fn, dtype, def) \
    private: dtype variable def; \
    ACCESSOR(variable, fn);

#define PROPERTY_READONLY(variable, fn, dtype) \
    PROPERTY_READONLY_D(variable, fn, dtype, );
