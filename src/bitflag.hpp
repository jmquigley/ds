/**
 * @brief bit flag management class
 *
 * @example
 * // Basic usage example:
 * ds::BitFlag flags;
 *
 * // Define some bit flags
 * const unsigned char FLAG_READ    = 0x01;  // 00000001
 * const unsigned char FLAG_WRITE   = 0x02;  // 00000010
 * const unsigned char FLAG_EXECUTE = 0x04;  // 00000100
 *
 * // Set individual flags
 * flags.set(FLAG_READ | FLAG_WRITE);
 *
 * // Check if flags are set
 * if (flags.has(FLAG_READ)) {
 *     // This will execute
 *     std::cout << "Read permission is set" << std::endl;
 * }
 *
 * if (flags.has(FLAG_READ | FLAG_WRITE)) {
 *     // This will execute
 *     std::cout << "Read and Write permissions are set" << std::endl;
 * }
 *
 * if (flags.has(FLAG_EXECUTE)) {
 *     // This will NOT execute
 *     std::cout << "Execute permission is set" << std::endl;
 * }
 *
 * // Toggle flags
 * flags.flipflop(FLAG_READ | FLAG_EXECUTE);
 * // Now: READ is unset, WRITE is set, EXECUTE is set
 *
 * // Unset a flag
 * flags.unset(FLAG_WRITE);
 * // Now: All flags are unset except EXECUTE
 *
 * // Get the raw value
 * unsigned char rawValue = flags.get();  // Will be 0x04 (EXECUTE flag)
 */

#pragma once

#include <cstddef>
#include <type_traits>

/**
 * @namespace ds
 * @brief Contains data structure related utilities and helper functions.
 */
namespace ds {

/**
 * @brief Template class for managing bit flags of any integral type
 *
 * @tparam T The integral type used to store the flags
 */
template<typename T>
struct BaseBitFlag {
	// Static assertion to ensure T is an integral type
	static_assert(std::is_integral<T>::value, "T must be an integral type");

	T flag;	 ///< The underlying flag storage

	/**
	 * @brief Default constructor, initializes flag to 0
	 */
	BaseBitFlag() : flag(0) {};

	/**
	 * @brief Constructor with initial flag value
	 * @param flag Initial flag value
	 */
	BaseBitFlag(T flag) : flag(flag) {}

	/**
	 * @brief Copy constructor
	 * @param bitFlag BitFlag to copy from
	 */
	BaseBitFlag(BaseBitFlag &bitFlag) {
		this->flag = bitFlag.flag;
	}

	/**
	 * @brief Get the current flag value
	 * @return Current flag value
	 */
	T get() const {
		return flag;
	}

	/**
	 * @brief Toggle specified bits in the flag
	 * @param flag Bits to toggle
	 */
	void flipflop(T flag) {
		this->flag ^= flag;
	}

	/**
	 * @brief Check if specified bits are set
	 * @param flag Bits to check
	 * @return true if all specified bits are set, false otherwise
	 */
	bool has(T flag) const {
		return (this->flag & flag) == flag;
	}

	/**
	 * @brief resets the bit flag to all zeroes
	 */
	void reset() {
		this->flag = 0;
	}

	/**
	 * @brief Set specified bits in the flag
	 * @param flag Bits to set
	 */
	void set(T flag) {
		this->flag |= flag;
	}

	/**
	 * @brief Toggle specified bits in the flag.  This is an alias to the
	 * flipflop().
	 * @param flag Bits to toggle
	 */
	void toggle(T flag) {
		flipflop(flag);
	}

	/**
	 * @brief Clear specified bits in the flag
	 * @param flag Bits to clear
	 */
	void unset(T flag) {
		this->flag &= ~flag;
	}
};

/**
 * @brief BitFlag implementation using size_t for maximum width on the platform
 */
typedef struct BaseBitFlag<size_t> WideBitFlag;

/**
 * @brief BitFlag implementation using unsigned char (8 bits)
 */
typedef struct BaseBitFlag<unsigned char> BitFlag;

}  // namespace ds
