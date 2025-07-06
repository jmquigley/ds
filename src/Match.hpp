#pragma once

#include <Node.hpp>
#include <memory>
#include <property.hpp>

namespace ds {

/**
 * @class Match
 * @brief A container class to hold the contents of a find operation
 * @tparam T The type of data stored within the Match
 */
template<typename T>
class Match {
	PROPERTY_D(data, Data, T, = 0);
	PROPERTY_D(_found, Found, bool, = false);
	PROPERTY_D(index, Index, size_t, = 0);
	PROPERTY(node, Node, std::weak_ptr<Node<T>>);

public:

	/**
	 * @brief A convenience function to return the found value
	 * @returns true if this Match object holds a found value, otherwise false
	 */
	inline bool found() const {
		return this->getFound();
	}
};
}  // namespace ds
