#pragma once

namespace ds {

/**
 * @class Comparable
 * @brief Abstract interface for implementing comparison operations between
 * objects
 *
 * The Comparable interface defines a complete set of comparison operators that
 * allow objects to be compared for equality and ordering relationships. Classes
 * implementing this interface must provide concrete implementations of all
 * comparison operators.
 *
 * Additionally, the interface provides a default implementation of the
 * compare() method that returns a three-way comparison result (-1, 0, 1) based
 * on the object's equality and ordering operators.
 *
 * @tparam T The type of objects that can be compared with instances of the
 * implementing class
 */
template<typename T>
class Comparable {
public:

	/**
	 * @brief Equality comparison operator
	 *
	 * Determines if this object is equal to another object of type T.
	 *
	 * @param other The object to compare with
	 * @return bool True if this object is equal to other, false otherwise
	 * @throws noexcept This function must not throw exceptions
	 */
	virtual bool operator==(const T &other) const noexcept = 0;

	/**
	 * @brief Inequality comparison operator
	 *
	 * Determines if this object is not equal to another object of type T.
	 *
	 * @param other The object to compare with
	 * @return bool True if this object is not equal to other, false otherwise
	 * @throws noexcept This function must not throw exceptions
	 */
	virtual bool operator!=(const T &other) const noexcept = 0;

	/**
	 * @brief Less-than comparison operator
	 *
	 * Determines if this object is less than another object of type T
	 * in a well-defined ordering.
	 *
	 * @param other The object to compare with
	 * @return bool True if this object is less than other, false otherwise
	 * @throws noexcept This function must not throw exceptions
	 */
	virtual bool operator<(const T &other) const noexcept = 0;

	/**
	 * @brief Less-than-or-equal comparison operator
	 *
	 * Determines if this object is less than or equal to another object of type
	 * T.
	 *
	 * @param other The object to compare with
	 * @return bool True if this object is less than or equal to other, false
	 * otherwise
	 * @throws noexcept This function must not throw exceptions
	 */
	virtual bool operator<=(const T &other) const noexcept = 0;

	/**
	 * @brief Greater-than comparison operator
	 *
	 * Determines if this object is greater than another object of type T
	 * in a well-defined ordering.
	 *
	 * @param other The object to compare with
	 * @return bool True if this object is greater than other, false otherwise
	 * @throws noexcept This function must not throw exceptions
	 */
	virtual bool operator>(const T &other) const noexcept = 0;

	/**
	 * @brief Greater-than-or-equal comparison operator
	 *
	 * Determines if this object is greater than or equal to another object of
	 * type T.
	 *
	 * @param other The object to compare with
	 * @return bool True if this object is greater than or equal to other, false
	 * otherwise
	 * @throws noexcept This function must not throw exceptions
	 */
	virtual bool operator>=(const T &other) const noexcept = 0;

	/**
	 * @brief Compares two data values and returns an integer that
	 * represents their relationship.
	 *
	 * This method provides a three-way comparison capability, similar to
	 * C++20's spaceship operator (<=>). It uses the equality and greater-than
	 * operators to determine the relationship between the objects.
	 *
	 * @param o1 Left hand side of the comparison
	 * @param o2 Right hand side of the comparison
	 * @returns Integer indicating the relationship:
	 *          - 0 if o1 and o2 are equal
	 *          - 1 if o1 is greater than o2
	 *          - -1 if o1 is less than o2
	 * @throws noexcept This function must not throw exceptions
	 */
	virtual int compare(const T &o1, const T &o2) const noexcept {
		if (o1 == o2) {
			return 0;
		} else if (o1 > o2) {
			return 1;
		}

		return -1;
	}

	/**
	 * @brief Virtual destructor
	 *
	 * Ensures proper cleanup of derived class resources when objects are
	 * destroyed through a pointer to the base class.
	 */
	virtual ~Comparable() {}
};

}  // namespace ds
