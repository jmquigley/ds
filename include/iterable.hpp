/**
 * @file iterable.hpp
 * @brief Defines the interface that is used by all iterable data structures.
 */

#pragma once

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Iterable
 * @brief An interface definition for all iterable collections.
 *
 * @tparam T The type of data stored within the collection.
 */
template <typename T>
class Iterable {

public:

    /**
     * @brief Find function for iterable collection classes.
     * @pure
     */
    Node<T> find(T data) = 0;

    /**
     * @brief insert the given data into a collection.
     * @pure
     */
    void insert(T data) = 0;

    /**
     * @brief Removes the given data element from the structure if it
     *        exists.
     * @pure
     */
    void remove(T data) = 0;

};
}
