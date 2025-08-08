#pragma once

#include <algorithm>
#include <bitset>
#include <cstddef>
#include <ds/Replicate.hpp>
#include <ds/constants.hpp>
#include <ds/property.hpp>
#include <string>
#include <type_traits>

namespace ds {

/**
 * @class BaseBitFlag
 * @brief bit flag management class
 * @tparam T The integral type used to store the flags
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
 * flags.toggle(FLAG_READ | FLAG_EXECUTE);
 * // Now: READ is unset, WRITE is set, EXECUTE is set
 *
 * // Unset a flag
 * flags.unset(FLAG_WRITE);
 * // Now: All flags are unset except EXECUTE
 *
 * // Get the raw value
 * unsigned char rawValue = flags.get();  // Will be 0x04 (EXECUTE flag)
 */
template<typename T>
class BaseBitFlag : public Replicate<T, BaseBitFlag<T>> {
	// Static assertion to ensure T is an integral type
	static_assert(std::is_integral<T>::value, "T must be an integral type");

	/**
	 * @brief the underlying flag storage
	 */
	PROPERTY(flag, Flag, T);

public:

	/**
	 * @brief Default constructor, initializes flag to 0
	 */
	constexpr BaseBitFlag() noexcept : _flag(0) {}

	/**
	 * @brief Constructor with initial flag value
	 * @param flag Initial flag value
	 */
	constexpr explicit BaseBitFlag(const T &flag) noexcept : _flag(flag) {}

	/**
	 * @brief Copy constructor for bit flags
	 * @param bitFlag BitFlag to copy from
	 */
	constexpr BaseBitFlag(const BaseBitFlag &bitFlag) noexcept
		: _flag(bitFlag._flag) {}

	/**
	 * @brief Move constructor for bit flags
	 * @param bitFlag BitFlag to move from
	 */
	constexpr BaseBitFlag(BaseBitFlag &&bitFlag) noexcept
		: _flag(std::move(bitFlag._flag)) {}

	/**
	 * @brief Bit flag destructor
	 *
	 * Properly cleans up resources associated with this bitflag.  It uses
	 * the default destructor.
	 */
	virtual ~BaseBitFlag() = default;

	/**
	 * @brief Copy assignment operator
	 * @param bitFlag BitFlag to copy from
	 * @return Reference to this object
	 */
	BaseBitFlag &operator=(const BaseBitFlag<T> &bitFlag) noexcept {
		this->_flag = bitFlag._flag;
		return *this;
	}

	/**
	 * @brief Copy assignment operator using the base type
	 * @param bitFlag `T` value to copy from
	 * @return Reference to this object
	 */
	BaseBitFlag &operator=(const T &bitFlag) noexcept {
		this->_flag = bitFlag;
		return *this;
	}

	/**
	 * @brief Move assignment operator
	 * @param bitFlag BitFlag to move from
	 * @return Reference to this object
	 */
	BaseBitFlag &operator=(BaseBitFlag<T> &&bitFlag) noexcept {
		if (this != &bitFlag) {
			this->_flag = std::move(bitFlag._flag);
		}
		return *this;
	}

	/**
	 * @brief Overloads the stream insertion operator for BitFlag objects
	 *
	 * This will print the contents of an integer type object as a
	 * bit string representation of an 8, 16, 32, or 64-bit value.
	 *
	 * @code
	 * ds::BitFlag bf(123);
	 * std::cout << bf;
	 * // prints "01111011"
	 * @endcode
	 * @param st (`std::ostream`) the output stream
	 * @param bf (`BaseBitFlag<T> &`) the BaseBitFlag object to print
	 * @returns a reference to the `std::ostream` object
	 */
	friend std::ostream &operator<<(std::ostream &st,
									const BaseBitFlag<T> &bf) {
		return st << bf.str();
	}

	/**
	 * @brief Checks if the contents of two given bit flags are equal
	 * @param bf (`BaseBitFlag<T> &`) the bit flag to compare against
	 * @return true if both flags have the same values, otherwise false
	 */
	constexpr bool operator==(const BaseBitFlag<T> &bf) const noexcept {
		return this->_flag == bf._flag;
	}

	/**
	 * @brief Checks if the contents of two given bit flags are NOT equal
	 * @param bf (`BaseBitFlag<T> &`) the bit flag to compare against
	 * @return true if both flags have different values, otherwise false
	 */
	constexpr bool operator!=(const BaseBitFlag<T> &bf) const noexcept {
		return this->_flag != bf._flag;
	}

	/**
	 * @brief a convenience operator for the at().
	 * @param index (`size_t`) the location of the bit within the number
	 * @returns a 0 or 1 for the index position.
	 */
	unsigned char operator[](size_t index) const noexcept {
		return at(index);
	}

	/**
	 * @brief Performs a bitwise AND operation with another BitFlag
	 * @param bf The BitFlag to AND with
	 * @return A new BitFlag containing the result of the AND operation
	 */
	constexpr BaseBitFlag<T> operator&(
		const BaseBitFlag<T> &bf) const noexcept {
		return BaseBitFlag<T>(this->_flag & bf._flag);
	}

	/**
	 * @brief Performs a bitwise AND operation and assigns the result
	 * @param bf The BitFlag to AND with
	 * @return Reference to this object after the operation
	 */
	BaseBitFlag<T> &operator&=(const BaseBitFlag<T> &bf) noexcept {
		this->_flag &= bf._flag;
		return *this;
	}

	/**
	 * @brief Performs a bitwise OR operation with another BitFlag
	 * @param bf The BitFlag to OR with
	 * @return A new BitFlag containing the result of the OR operation
	 */
	constexpr BaseBitFlag<T> operator|(
		const BaseBitFlag<T> &bf) const noexcept {
		return BaseBitFlag<T>(this->_flag | bf._flag);
	}

	/**
	 * @brief Performs a bitwise OR operation and assigns the result
	 * @param bf The BitFlag to OR with
	 * @return Reference to this object after the operation
	 */
	BaseBitFlag<T> &operator|=(const BaseBitFlag<T> &bf) noexcept {
		this->_flag |= bf._flag;
		return *this;
	}

	/**
	 * @brief Performs a bitwise XOR operation with another BitFlag
	 * @param bf The BitFlag to XOR with
	 * @return A new BitFlag containing the result of the XOR operation
	 */
	constexpr BaseBitFlag<T> operator^(
		const BaseBitFlag<T> &bf) const noexcept {
		return BaseBitFlag<T>(this->_flag ^ bf._flag);
	}

	/**
	 * @brief Performs a bitwise XOR operation and assigns the result
	 * @param bf The BitFlag to XOR with
	 * @return Reference to this object after the operation
	 */
	BaseBitFlag<T> &operator^=(const BaseBitFlag<T> &bf) noexcept {
		this->_flag ^= bf._flag;
		return *this;
	}

	/**
	 * @brief Performs a bitwise NOT operation on this BitFlag
	 * @return A new BitFlag containing the result of the NOT operation
	 */
	constexpr BaseBitFlag<T> operator~() const noexcept {
		return BaseBitFlag<T>(~this->_flag);
	}

	/**
	 * @brief Performs a left shift operation on the bits
	 * @param places Number of positions to shift left
	 * @return A new BitFlag with the bits shifted left
	 */
	constexpr BaseBitFlag<T> operator<<(size_t places) const noexcept {
		return BaseBitFlag<T>(this->_flag << places);
	}

	/**
	 * @brief Performs a left shift operation and assigns the result
	 * @param places Number of positions to shift left
	 * @return Reference to this object after the operation
	 */
	BaseBitFlag<T> &operator<<=(size_t places) noexcept {
		this->_flag <<= places;
		return *this;
	}

	/**
	 * @brief Performs a right shift operation on the bits
	 * @param places Number of positions to shift right
	 * @return A new BitFlag with the bits shifted right
	 */
	constexpr BaseBitFlag<T> operator>>(size_t places) const noexcept {
		return BaseBitFlag<T>(this->_flag >> places);
	}

	/**
	 * @brief Performs a right shift operation and assigns the result
	 * @param places Number of positions to shift right
	 * @return Reference to this object after the operation
	 */
	BaseBitFlag<T> &operator>>=(size_t places) noexcept {
		this->_flag >>= places;
		return *this;
	}

	/**
	 * @brief retrieves a single bit from the given location within the number
	 *
	 * If the index is out of range (greater than the size of T in bits),
	 * it returns 0.
	 *
	 * @param index (`size_t`) the location of the bit within the number
	 * (0-based)
	 * @returns a 0 or 1 for the index position.
	 */
	unsigned short int at(size_t index) const noexcept {
		index = std::min((sizeof(T) * constants::BYTESIZE) - 1, index);
		return (unsigned short int)((this->_flag >> index) & 0x1);
	}

	/**
	 * @brief Copies the given bit flag structure into this one
	 * @param other (`BaseBitFlag<T> &`) reference to the bit flag object to
	 * copy
	 * @return Referece to this object after the operation
	 */
	virtual BaseBitFlag<T> &copy(const BaseBitFlag<T> &other) override {
		this->_flag = other._flag;
		return *this;
	}

	/**
	 * @brief Creates a deep copy of the bit flag object
	 * @return std::shared_ptr<BaseBitFlag<T>> A shared pointer to the new copy
	 */
	virtual std::shared_ptr<BaseBitFlag<T>> deepcopy() override {
		return std::make_shared<BaseBitFlag<T>>(this->_flag);
	}

	/**
	 * @brief Get the current flag value
	 * @return Current flag value
	 */
	constexpr T get() const noexcept {
		return _flag;
	}

	/**
	 * @brief moves the resources from one object to another.
	 * in this function it is effectively the same as the copy operation as
	 * there are no memory resources to move.
	 * @param other (`BaseBitFlag<T> &`) a reference to an object to move.
	 * @return Referece to this object after the operation
	 */
	virtual BaseBitFlag<T> &move(BaseBitFlag<T> &&other) override {
		this->_flag = other._flag;
		return *this;
	}

	/**
	 * @brief Check if specified bits are set
	 * @param mask Bits to check
	 * @return true if all specified bits are set, false otherwise
	 */
	constexpr bool has(T mask) const noexcept {
		return (this->_flag & mask) == mask;
	}

	/**
	 * @brief Check if any of the specified bits are set
	 * @param mask Bits to check
	 * @return true if any of the specified bits are set, false otherwise
	 */
	constexpr bool hasAny(T mask) const noexcept {
		return (this->_flag & mask) != 0;
	}

	/**
	 * @brief resets the bit flag to all zeroes
	 */
	void reset() noexcept {
		this->_flag = 0;
	}

	/**
	 * @brief Set specified bits in the flag
	 * @param mask Bits to set
	 * @returns the new flag value set within the object
	 */
	T set(T mask) noexcept {
		this->_flag |= mask;
		return this->_flag;
	}

	/**
	 * @brief Explicitly sets the flag value
	 * @param value The value to set the flag to
	 * @return A reference to this object
	 */
	BaseBitFlag &setValue(T value) noexcept {
		this->_flag = value;
		return *this;
	}

	/**
	 * @brief Prints out a string that represents the binary bit pattern
	 * of the flag.
	 * @returns a std::string that represents the number in binary format
	 */
	std::string str() const {
		const size_t totalBits = sizeof(this->_flag) * constants::BYTESIZE;

		switch (totalBits) {
			case constants::BYTESIZE:
				return std::bitset<8>(this->_flag).to_string();
			case constants::BYTESIZE * 2:
				return std::bitset<16>(this->_flag).to_string();
			case constants::BYTESIZE * 4:
				return std::bitset<32>(this->_flag).to_string();
			case constants::BYTESIZE * 8:
				return std::bitset<64>(this->_flag).to_string();
			default:
				// For any non-standard size, use a 64-bit representation
				return std::bitset<64>(this->_flag).to_string();
		}
	}

	/**
	 * @brief Toggle specified bits in the flag
	 * @param mask Bits to toggle
	 * @returns the new overall bit flag value
	 */
	T toggle(T mask) noexcept {
		this->_flag ^= mask;
		return this->_flag;
	}

	/**
	 * @brief Clear specified bits in the flag
	 * @param mask Bits to clear
	 * @returns the new overall bit flag value
	 */
	T unset(T mask) noexcept {
		this->_flag &= ~mask;
		return this->_flag;
	}
};

/**
 * @brief BitFlag implementation using unsigned char (8 bits)
 */
using ByteFlag = BaseBitFlag<unsigned char>;

/**
 * @brief BitFlag implementation using unsigned short int (16 bits)
 */
using ShortFlag = BaseBitFlag<unsigned short int>;

/**
 * @brief BitFlag implementation using unsigned int (32 bits)
 */
using BitFlag = BaseBitFlag<unsigned int>;

/**
 * @brief BitFlag implementation using size_t for maximum width on the platform
 */
using WideFlag = BaseBitFlag<size_t>;

}  // namespace ds
