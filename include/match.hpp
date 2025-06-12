/**
 * @file match.hpp
 * @brief Defines the object that will hold search/find results
 */

#pragma once

#include "node.hpp"
#include "property.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Match
 * @brief A container class to hold the contents of a find operation
 * @tparam T The type of data stored within the Match
 */
template<typename T>
class Match {
	PROPERTY_D(data, Data, T, = 0);
	PROPERTY_D(found, found, bool, = false);
	PROPERTY_D(index, Index, size_t, = 0);
};
}  // namespace ds
