#pragma once

#include <any>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace ds {

/**
 * @brief Checks if all provided pointer-like objects are valid (non-null)
 * with short-circuit evaluation
 * @returns true if all values are valid, otherwise false
 */
template<typename P, typename... Ptrs>
[[nodiscard]] constexpr inline bool all(const P &p,
										const Ptrs &...ptrs) noexcept {
	if (!bool(p)) {
		return false;
	}
	if constexpr (sizeof...(ptrs) == 0) {
		return true;
	} else {
		return all(ptrs...);
	}
}

/**
 * @brief Checks if any of the provided pointer-like objects are valid
 * (non-null) with short-circuit evaluation
 * @returns true if any pointer in the list is valid, otherwise false.
 */
template<typename P, typename... Ptrs>
[[nodiscard]] constexpr inline bool any(const P &p,
										const Ptrs &...ptrs) noexcept {
	if (bool(p)) {
		return true;
	}
	if constexpr (sizeof...(ptrs) == 0) {
		return false;
	} else {
		return any(ptrs...);
	}
}

/**
 * @brief Converts an enumeration value to its underlying integer type.
 *
 * This template function safely converts an enum class value to its underlying
 * integer representation using static_cast with type safety.
 *
 * @tparam Enumeration The enumeration type to convert from
 * @param value The enumeration value to convert
 * @return The integer representation of the enumeration value
 */
template<typename Enumeration>
auto as_integer(Enumeration const value) ->
	typename std::underlying_type<Enumeration>::type {
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
};

/**
 * @brief Implements the djb2 hash algorithm
 *
 * The djb2 algorithm is a simple and efficient hash function created by Daniel
 * J. Bernstein. It starts with an initial hash value of 5381 and for each
 * character in the input string:
 * - Shifts the current hash value left by 5 bits
 * - Adds the original hash value to this shifted value (hash * 33)
 * - Adds the ASCII value of the current character
 *
 * This can be expressed as: hash = ((hash << 5) + hash) + c
 * Which is equivalent to: hash = hash * 33 + c
 *
 * The algorithm has good distribution and speed on many types of string inputs.
 *
 * @param str The input C-string to hash
 * @return A size_t hash value of the input string, or 0 if the input is NULL
 */
size_t djb2(const char *str);

/**
 * @brief Converts a shared pointer to a string representation
 *
 * This function extracts the raw memory address of the object pointed to by
 * the shared pointer and converts it to a string representation, typically
 * in hexadecimal format.
 *
 * @tparam T The type of object pointed to by the shared pointer
 * @param p The shared pointer to convert to a string
 * @return A string representation of the pointer's memory address
 */
template<typename T>
std::string pointerToString(std::shared_ptr<T> p) {
	std::stringstream ss;
	void *rawAddress = static_cast<void *>(p.get());
	ss << rawAddress;
	return ss.str();
}

template<typename T>
std::weak_ptr<std::any> to_weak_any(std::shared_ptr<T> original) {
	auto any_shared = std::make_shared<std::any>(*original);
	return std::weak_ptr<std::any>(any_shared);
}

/**
 * @brief Converts a weak pointer to a string representation
 *
 * This function attempts to lock the weak pointer and obtain a string
 * representation of the pointed-to object. If the weak pointer is expired
 * (i.e., the object has been deleted), it returns "invalid".
 *
 * @tparam T The type of object pointed to by the weak pointer
 * @param wp The weak pointer to convert to a string
 * @param message The message to return when the pointer is invalid
 * @return A string representation of the pointer address or "invalid" if
 * expired
 */
template<typename T>
std::string weakPointerToString(std::weak_ptr<T> wp,
								std::string message = "invalid") {
	std::shared_ptr<T> p = wp.lock();

	if (p) {
		return pointerToString(p);
	}

	return message;
}

}  // namespace ds
