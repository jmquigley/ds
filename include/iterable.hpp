/**
 * @file iterable.hpp
 * @brief Defines the interface that is used by all iterable data structures.
 */

#pragma once

#include "match.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

enum class Position:int {
    FRONT = 0,
    BACK = -1
};

/**
 * @class Iterable
 * @brief An interface definition for all iterable collections.
 *
 * @tparam T The type of data stored within the collection.
 */
template <typename T>
class Iterable {

public:

    inline static char FRONT = 0;
    inline static char BACK = -1;

    /**
     * @brief Find function for iterable collection classes.
     * @pure
     */
    virtual Match<T> find(T data) = 0;

    /**
     * @brief insert the given data into a collection.
     * @pure
     */
    virtual void insert(T data, ssize_t idx = 0, Position position = Position::BACK) = 0;

    /**
     * @brief Removes the given data element from the structure if it
     *        exists.
     * @pure
     */
    virtual void remove(T data) = 0;

};
}
