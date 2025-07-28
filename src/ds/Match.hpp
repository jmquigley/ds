#pragma once

#include <ds/BaseNode.hpp>
#include <ds/Node.hpp>
#include <ds/property.hpp>
#include <memory>

namespace ds {

/**
 * @class Match
 * @brief A container class to hold the results of a find operation in a data
 * structure
 *
 * Match is designed to provide a consistent interface for returning search
 * results. It not only indicates whether an item was found, but also provides
 * additional context such as the value found, the node containing the value,
 * and its position in the data structure.
 *
 * @tparam T The type of data stored within the Match
 */
template<typename T, template<class> class C>
class Match {
	/// @brief The data value found during the search operation
	PROPERTY(data, Data, T);

	/// @brief Flag indicating whether the search operation was successful
	PROPERTY_WITH_DEFAULT(found, Found, bool, {false});

	/// @brief The position or index where the item was found (if applicable)
	PROPERTY_WITH_DEFAULT(index, Index, size_t, {0});

	/// @brief Weak pointer to the node containing the found value
	PROPERTY(ref, Ref, std::weak_ptr<C<T>>);

	/// @brief The search string value used in the search operation
	PROPERTY(search, Search, std::string);

public:

	Match()
		: _data {},
		  _found(false),
		  _index(0),
		  _ref(std::weak_ptr<C<T>>()),
		  _search("") {}

	/**
	 * @brief a copy constructor for the Match object
	 * @param match the `Match` object to copy
	 */
	Match(Match &match) : Match<T, C>() {
		this->_data = match._data;
		this->_found = match._found;
		this->_index = match._index;
		this->_search = match._search;
		this->_ref = match._ref;
	}

	virtual ~Match() {}

	/**
	 * @brief retrieves the current shared pointer value stored within the
	 * the match.
	 * @returns a `std::shared_ptr<C<T>>` that refereces the node that this
	 * match has found.  A nullptr will be returned i
	 */
	std::shared_ptr<C<T>> reference() {
		return this->_ref.lock();
	}
};
}  // namespace ds
