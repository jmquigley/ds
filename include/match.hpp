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
	PROPERTY(data, Data, T);
    PROPERTY(found, found, bool);
	PROPERTY(index, Index, size_t);
};
}  // namespace ds
