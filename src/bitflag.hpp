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

#include <algorithm>
#include <bitset>
#include <cstddef>
#include <string>
#include <type_traits>

#include "constants.hpp"

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
	 * @brief Overloads the stream insertion operator for BitFlag objects
	 *
	 * This will print the contents of an integer type object as a
	 * bit string representation of an 8, 16, 32, or 64-bit value.
	 *
	 * @example
	 *    ds::BitFlag bf(123);
	 *    std::cout << bf;
	 *    // prints "01111011"
	 *
	 * @param st (`std::ostream`) the output stream
	 * @param bf (`BaseBitFlag<T> &`) the BaseBitFlag object to print
	 * @returns a reference to the `std::ostream` object
	 */
	friend std::ostream &operator<<(std::ostream &st, const BaseBitFlag<T> &bf) {
		return st << bf.str();
	}

	/**
	 * @brief sets the value of the flag to the given parameter
	 * @param flag (`T`) the flag value to set to
	 * @return a reference to the current flag object
	 */
	BaseBitFlag &operator=(const T flag) {
		this->set(flag);
		return *this;
	}

	/**
	 * @brief Checks if the contents of two given bit flags are equal
	 * @param bf (`BaseBitFlag<T> &`) the bit flag to compare against
	 * @return true if both flags have the same values, otherwise false
	 */
	bool operator==(const BaseBitFlag<T> &bf) const {
		return this->flag == bf.flag;
	}

	/**
	 * @brief Checks if the contents of two given bit flags are NOT equal
	 * @param bf (`BaseBitFlag<T> &`) the bit flag to compare against
	 * @return true if both flags have different values, otherwise false
	 */
	bool operator!=(const BaseBitFlag<T> &bf) const {
		return this->flag != bf.flag;
	}

	/**
	 * @brief a convenience operator for the at().
	 * @param index (`size_t`) the location of the bit within the number
	 * @returns a 0 or 1 for the index position.
	 */
	unsigned char operator[](size_t index) {
		return at(index);
	}

	/**
	 * @brief retrieves a single bit from the given locaiton within the number
	 * If the number is greater than the size of the number, then the max
	 * size of the number is used as the index value.
	 * @param index (`size_t`) the location of the bit within the number
	 * @returns a 0 or 1 for the index position.
	 */
	unsigned short int at(size_t index) {
		index = std::min((sizeof(T) * constants::BYTESIZE), index);
		return (unsigned short int)((this->flag >> (index - 1)) & 0x1);
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
	 * @returns the new overall bit flag value
	 */
	T flipflop(T flag) {
		this->flag ^= flag;
		return this->flag;
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
	 * @returns the new flag value set within the object
	 */
	T set(T flag) {
		this->flag |= flag;
		return this->flag;
	}

	/**
	 * @brief Prints out a string that represents the binary bit pattern
	 * of the flag.
	 * @returns a std::string that represents the number in binary format
	 */
	std::string str() const {
		size_t &&totalBits = sizeof(this->flag) * constants::BYTESIZE;

		switch (totalBits) {
			case constants::BYTESIZE:
				return std::bitset<8>(this->flag).to_string();
			case constants::BYTESIZE * 2:
				return std::bitset<16>(this->flag).to_string();
			case constants::BYTESIZE * 4:
				return std::bitset<32>(this->flag).to_string();
		}

		return std::bitset<64>(this->flag).to_string();
	}

	/**
	 * @brief Toggle specified bits in the flag.  This is an alias to the
	 * flipflop().
	 * @param flag Bits to toggle
	 * @returns the new overall bit flag value
	 */
	T toggle(T flag) {
		return flipflop(flag);
	}

	/**
	 * @brief Clear specified bits in the flag
	 * @param flag Bits to clear
	 * @returns the new overall bit flag value
	 */
	T unset(T flag) {
		this->flag &= ~flag;
		return this->flag;
	}
};

/**
 * @brief BitFlag implementation using unsigned char (8 bits)
 */
typedef struct BaseBitFlag<unsigned char> ByteBitFlag;

/**
 * @brief BitFlag implementation using unsigned short int (16 bits)
 */
typedef struct BaseBitFlag<unsigned short int> ShortBitFlag;

/**
 * @brief BitFlag implementation using unsigned int (32 bits)
 */
typedef struct BaseBitFlag<unsigned int> BitFlag;

/**
 * @brief BitFlag implementation using size_t for maximum width on the platform
 */
typedef struct BaseBitFlag<size_t> WideBitFlag;

}  // namespace ds
