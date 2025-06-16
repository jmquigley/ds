/**
 * @brief An object that takes the data from nodes and peforms a comparison.
 *
 * When the elements in a collection class must be compared for equality
 * this object is used.  It checks if the objects are equal, greater than
 * or less than another element.
 */

#pragma once

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Comparator
 * @brief Used to compare two types through a common interface.
 *
 * This class provides a comparision function that can be used
 * to compare two elements.  This is used by each collection class
 * to do a comparison of the data contained within a Node without
 * needed to understand all of the internals of the data contained
 * in a node.
 *
 * The compare function should return one of three values:
 *
 * - 1 the first value is larger than the second value
 * - 0 the two values are equal
 * - -1 the first value is less than the second value
 *
 * @tparam T The type of data stored within the stack.
 */
template<typename T>
class Comparator {
public:

	/**
	 * @brief Compares two data values and returns an integer that
	 * represents their relationship.
	 * @param o1 (`T`) left hand side of the comparison
	 * @param o2 (`T`) right hand side of the comparison
	 * @returns 0 if `o1` and `o2` are equal, 1 if `o1` is greater
	 * than `o2`, or -1 if `o1` is less than `o2`.
	 */
	virtual int compare(T o1, T o2) {
		if (o1 == o2) {
			return 0;
		} else if (o1 > o2) {
			return 1;
		}

		return -1;
	}
};
}  // namespace ds
