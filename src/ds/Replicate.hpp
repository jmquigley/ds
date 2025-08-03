#pragma once

#include <memory>

namespace ds {

/**
 * @class Replicate
 * @brief Interface for replicable data structures
 *
 * @tparam T The type of data elements stored
 * @tparam Derived The actual derived class implementing the interface
 */
template<typename T, typename Derived>
class Replicate {
protected:

	Replicate() = default;
	virtual ~Replicate() = default;

public:

	/**
	 * @brief Creates a deep copy of the object
	 * @return std::shared_ptr<Derived> A shared pointer to the new copy
	 */
	virtual std::shared_ptr<Derived> deepcopy() = 0;

	/**
	 * @brief Creates a copy from another object
	 * @param other The source object to copy from
	 * @return Derived& A reference to this object after copying
	 */
	virtual Derived &copy(const Derived &other) = 0;

	/**
	 * @brief Moves resources from another object
	 * @param other The source object to move from
	 * @return Derived& A reference to this object after moving
	 */
	virtual Derived &move(Derived &&other) = 0;
};

}  // namespace ds
