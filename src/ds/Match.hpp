#pragma once

#include <ds/BaseNode.hpp>
#include <ds/Node.hpp>
#include <ds/Path.hpp>
#include <ds/Replicate.hpp>
#include <ds/property.hpp>
#include <memory>
#include <utility>

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
 * @tparam C The container/node template class that holds the data (e.g., Node,
 * TreeNode)
 */
template<typename T, template<class> class C>
class Match : private Replicate<T, Match<T, C>> {
	/// @brief The data value found during the search operation
	PROPERTY_WITH_DEFAULT_NO_CONST(data, Data, T, {});

	/// @brief Flag indicating whether the search operation was successful
	PROPERTY_WITH_DEFAULT(found, Found, bool, {false});

	/// @brief Weak pointer to the node containing the found value
	PROPERTY_WITH_DEFAULT(ptr, Ptr, std::weak_ptr<C<T>>,
						  {std::weak_ptr<C<T>>()});

	/// @brief The search string value used in the search operation
	PROPERTY_WITH_DEFAULT(search, Search, Path, {""});

private:

public:

	/**
	 * @brief Default constructor
	 *
	 * Initializes a Match object with default values indicating no match found
	 */
	constexpr Match() = default;

	constexpr ~Match() override = default;

	/**
	 * @brief Copy constructor for the Match object
	 *
	 * @param match The Match object to copy
	 */
	constexpr Match(Match<T, C> &match) noexcept
		: _data(match._data),
		  _found(match._found),
		  _ptr(match._ptr),
		  _search(match._search) {
		this->copy(match);
	}

	/**
	 * @brief Move constructor for the Match object
	 *
	 * @param match The Match object to move from
	 */
	constexpr Match(Match<T, C> &&match) noexcept
		: _data(std::move(match._data)),
		  _found(std::move(match._found)),
		  _ptr(std::move(match._ptr)),
		  _search(std::move(match._search)) {
		move(std::move(match));
	}

	/**
	 * @brief Copy assignment operator
	 *
	 * @param other The Match object to copy from
	 * @return Match<T, C>& Reference to this object after copying
	 */
	auto operator=(const Match<T, C> &other) noexcept -> Match<T, C> & {
		copy(other);
		return *this;
	}

	/**
	 * @brief Move assignment operator
	 *
	 * @param other The Match object to move from
	 * @return Match<T, C>& Reference to this object after moving
	 */
	auto operator=(Match<T, C> &&other) noexcept -> Match<T, C> & {
		move(std::move(other));
		return *this;
	}

	/**
	 * @brief Copies data from another Match object
	 *
	 * @param other The Match object to copy from
	 * @return Match<T, C>& Reference to this object after copying
	 */
	auto copy(const Match<T, C> &other) noexcept -> Match<T, C> & override {
		if (this != &other) {
			this->_data = other._data;
			this->_found = other._found;
			this->_ptr = other._ptr;
			this->_search = other._search;
		}
		return *this;
	}

	/**
	 * @brief Creates a deep copy of this Match object
	 *
	 * @return std::shared_ptr<Match<T, C>> A shared pointer containing the copy
	 */
	auto deepcopy() noexcept -> std::shared_ptr<Match<T, C>> override {
		auto copy = std::make_shared<Match<T, C>>();
		copy->_data = this->_data;
		copy->_found = this->_found;
		copy->_ptr = this->_ptr;
		copy->_search = this->_search;

		return copy;
	}

	/**
	 * @brief Moves data from another Match object
	 *
	 * @param other The Match object to move from
	 * @return Match<T, C>& Reference to this object after moving
	 */
	auto move(Match<T, C> &&other) noexcept -> Match<T, C> & override {
		if (this != &other) {
			this->_data = std::move(other._data);
			this->_found = std::move(other._found);
			this->_ptr = std::move(other._ptr);
			this->_search = std::move(other._search);

			// Reset moved-from object
			other._found = false;
			other._search = "";
			other._ptr.reset();
		}
		return *this;
	}

	/**
	 * @brief Retrieves the pointer to the node for this match object.
	 * @returns a `std::shared_ptr` to the node type object for this match
	 */
	auto pointer() -> std::shared_ptr<C<T>> {
		return this->_ptr.lock();
	}

	/**
	 * @brief Retrieves the value stored within the node (reference)
	 * @returns A reference to the value in the node that this match has found.
	 */
	auto reference() -> T & {
		if (!this->_found) {
			throw std::runtime_error("Cannot reference a failed match");
		}
		// Return a reference to the actual node in the container
		return this->pointer()->data();
	}
};

}  // namespace ds
