#pragma once

#include <any>
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
class Match : public Replicate<T, Match<T, C>> {
	/// @brief The data value found during the search operation
	PROPERTY_WITH_DEFAULT(data, Data, T, {});

	/// @brief Flag indicating whether the search operation was successful
	PROPERTY_WITH_DEFAULT(found, Found, bool, {false});

	/// @brief Weak pointer to the node containing the found value
	PROPERTY(ref, Ref, std::weak_ptr<C<T>>);

	/// @brief The search string value used in the search operation
	PROPERTY_WITH_DEFAULT(search, Search, Path, {""});

private:

	/**
	 * @brief Creates a deep copy of this Match object
	 *
	 * @return std::shared_ptr<Match<T, C>> A shared pointer containing the copy
	 */
	std::shared_ptr<Match<T, C>> deepcopy() noexcept override {
		auto copy = std::make_shared<Match<T, C>>();
		copy->_data = this->_data;
		copy->_found = this->_found;
		copy->_ref = this->_ref;
		copy->_search = this->_search;

		return copy;
	}

	/**
	 * @brief Copies data from another Match object
	 *
	 * @param other The Match object to copy from
	 * @return Match<T, C>& Reference to this object after copying
	 */
	Match<T, C> &copy(const Match<T, C> &other) noexcept override {
		if (this != &other) {
			this->_data = other._data;
			this->_found = other._found;
			this->_ref = other._ref;
			this->_search = other._search;
		}
		return *this;
	}

	/**
	 * @brief Moves data from another Match object
	 *
	 * @param other The Match object to move from
	 * @return Match<T, C>& Reference to this object after moving
	 */
	Match<T, C> &move(Match<T, C> &&other) noexcept override {
		if (this != &other) {
			this->_data = std::move(other._data);
			this->_found = std::move(other._found);
			this->_ref = std::move(other._ref);
			this->_search = std::move(other._search);

			// Reset moved-from object
			other._found = false;
			other._search = "";
			other._ref.reset();
		}
		return *this;
	}

public:

	/**
	 * @brief Default constructor
	 *
	 * Initializes a Match object with default values indicating no match found
	 */
	Match()
		: _data {}, _found(false), _ref(std::weak_ptr<C<T>>()), _search("") {}

	/**
	 * @brief Copy constructor for the Match object
	 *
	 * @param match The Match object to copy
	 */
	Match(Match<T, C> &match) noexcept
		: _data(match._data),
		  _found(match._found),
		  _ref(match._ref),
		  _search(match._search) {
		this->copy(match);
	}

	/**
	 * @brief Move constructor for the Match object
	 *
	 * @param match The Match object to move from
	 */
	Match(Match<T, C> &&match) noexcept
		: _data(std::move(match._data)),
		  _found(std::move(match._found)),
		  _ref(std::move(match._ref)),
		  _search(std::move(match._search)) {
		move(std::move(match));
	}

	/**
	 * @brief Destructor for Match
	 */
	virtual ~Match() {}

	/**
	 * @brief Copy assignment operator
	 *
	 * @param other The Match object to copy from
	 * @return Match<T, C>& Reference to this object after copying
	 */
	Match<T, C> &operator=(const Match<T, C> &other) noexcept {
		return copy(other);
	}

	/**
	 * @brief Move assignment operator
	 *
	 * @param other The Match object to move from
	 * @return Match<T, C>& Reference to this object after moving
	 */
	Match<T, C> &operator=(Match<T, C> &&other) noexcept {
		return move(std::move(other));
	}

	/**
	 * @brief Retrieves the current shared pointer value stored within the match
	 *
	 * @returns A std::shared_ptr<C<T>> that references the node that this
	 * match has found. A nullptr will be returned if the reference is no longer
	 * valid.
	 */
	std::shared_ptr<C<T>> reference() const {
		return this->_ref.lock();
	}
};

}  // namespace ds
