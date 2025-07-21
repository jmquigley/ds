#pragma once

#include <cstddef>
#include <ds/constants.hpp>
#include <ds/property.hpp>
#include <string>
#include <vector>

namespace ds {

/**
 * @brief A custom buffer class that will dynamically resize based on a defined
 * block size from the constructor.
 *
 * The `Buffer` class provides a flexible and efficient way to manage a sequence
 * of bytes. It dynamically expands its capacity in fixed-size blocks (defined
 * by `blockSize`) as more data is appended, avoiding frequent reallocations for
 * small additions. It offers functionalities for appending, retrieving,
 * searching, and comparing byte sequences, similar to a dynamic array or string
 * but for raw binary data.
 *
 * The block size can be changed after the buffer has been defined, but only
 * affects future expansions, not the current allocated capacity.
 *
 * Example:
 * @code
 * Buffer buffer(16);  // creates a buffer that expands in 16-byte blocks
 * Buffer buffer;      // creates a buffer with a default block size (e.g., 32k)
 *
 * buffer.append("Hello, ");
 * buffer.append("World!");
 * std::cout << buffer.str() << std::endl; // Output: Hello, World!
 *
 * Buffer otherBuffer("Test Data");
 * if (buffer == otherBuffer) {
 *     // ...
 * }
 * @endcode
 */
class Buffer {
	/**
	 * @brief The size of a single memory block that is allocated for expansion.
	 *
	 * When the buffer needs to grow, it expands its capacity by multiples of
	 * this size.
	 */
	PROPERTY(blockSize, BlockSize, size_t);

	/**
	 * @brief The total size of memory currently allocated for the buffer.
	 *
	 * This represents the allocated memory, which may be larger than the actual
	 * data size.
	 */
	PROPERTY_READONLY(capacity, Capacity, size_t);

	/**
	 * @brief The current size of the data actually stored in the buffer.
	 *
	 * This value is always less than or equal to `capacity`.
	 */
	PROPERTY_READONLY(size, Size, size_t);

private:

	char *buffer =
		nullptr;  ///< Pointer to the dynamically allocated memory block.

	/**
	 * @brief Allocates the initial internal space for the buffer and optionally
	 * assigns an initial value.
	 *
	 * @param s A byte string to assign to the initial buffer when it is
	 * created.
	 * @param sSize The size of the initial buffer in bytes.
	 * @param blockSize The size of each buffer memory block.
	 */
	void allocator(const char *s, size_t sSize, size_t blockSize);

	/**
	 * @brief Expands the current buffer's allocated capacity if the requested
	 * length exceeds it.
	 *
	 * If `len` is greater than the current `capacity`, the buffer's memory is
	 * reallocated to a new capacity, which is a multiple of `blockSize` that
	 * can accommodate `len`. If `len` is smaller than or equal to the current
	 * capacity, no action is taken.
	 *
	 * @param len The new minimum size that the buffer's capacity must be able
	 * to accommodate.
	 * @return A pointer reference to the (potentially reallocated) current
	 * buffer.
	 * @throws std::runtime_error if memory reallocation fails.
	 */
	const char *expand(size_t len);

	/**
	 * @brief Checks if the given start and end indices fall within the valid
	 * range of the current buffer's data size.
	 *
	 * @param start The starting index to check (inclusive).
	 * @param end The ending index to check (inclusive).
	 * @return `true` if both `start` and `end` are valid indices within `[0,
	 * size-1]` and `start <= end`, `false` otherwise.
	 */
	bool withinRange(size_t start, size_t end);

public:

	/**
	 * @brief Constructor for an empty Buffer with a specified block size.
	 *
	 * Initializes the buffer with a given block size, setting initial capacity
	 * and size to zero, and allocating the first block of memory.
	 *
	 * @param blockSize The size in bytes for each memory block. Defaults to
	 * `constants::READBUFSIZE`.
	 */
	Buffer(size_t blockSize = constants::READBUFSIZE);

	/**
	 * @brief Constructor for a Buffer initialized from a C-style string.
	 *
	 * Initializes the buffer with content from a C-style string and a specified
	 * block size.
	 *
	 * @param str A C-style string to initialize the buffer.
	 * @param sLen The size of the C-style string (number of bytes).
	 * @param blockSize The size in bytes for each memory block. Defaults to
	 * `constants::READBUFSIZE`.
	 */
	Buffer(const char *str, size_t sLen,
		   size_t blockSize = constants::READBUFSIZE);

	/**
	 * @brief Constructor for a Buffer initialized from a `std::string`.
	 *
	 * Initializes the buffer with content from a `std::string` and a specified
	 * block size.
	 *
	 * @param s A `std::string` to initialize the buffer.
	 * @param blockSize The size in bytes for each memory block. Defaults to
	 * `constants::READBUFSIZE`.
	 */
	Buffer(const std::string &s, size_t blockSize = constants::READBUFSIZE);

	/**
	 * @brief Copy constructor.
	 *
	 * Initializes a new Buffer object by copying the contents from an existing
	 * Buffer object. This constructor performs a deep copy of the buffer's
	 * contents.
	 *
	 * @note This constructor takes a non-const reference (`Buffer&`). This
	 * means it cannot be used to copy from `const Buffer` objects or rvalues
	 * (temporary objects).
	 *
	 * @param buf The Buffer object to copy from.
	 */
	Buffer(Buffer &buf);

	/**
	 * @brief Destructor for the Buffer object.
	 *
	 * Frees the dynamically allocated memory for the internal buffer if it
	 * exists.
	 */
	~Buffer();

	/**
	 * @brief Operator to clear the buffer.
	 *
	 * This is a convenience wrapper for the `clear()` function, resetting the
	 * buffer's `size` to zero. It does not free the allocated memory.
	 *
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &operator~();

	/**
	 * @brief Copy assignment operator.
	 *
	 * Clears the current buffer's contents, frees its existing internal memory,
	 * and then re-allocates new memory to copy the contents of the right-hand
	 * side buffer.
	 *
	 * @note This operator takes a non-const reference (`Buffer&`). This means
	 * it cannot be used to assign from `const Buffer` objects or rvalues
	 * (temporary objects).
	 *
	 * @param buf The Buffer object to copy from.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &operator=(Buffer &buf);

	/**
	 * @brief Operator to access a character at a specific index.
	 *
	 * This is a convenience wrapper for the `at()` function, providing
	 * direct read access to buffer elements. It performs bounds checking.
	 *
	 * @param index The zero-based index of the character to retrieve.
	 * @return The character at the specified index.
	 * @throws std::out_of_range if `index` is outside the valid data range `[0,
	 * size-1]`.
	 */
	char operator[](size_t index);

	/**
	 * @brief Operator to extract a section of the buffer.
	 *
	 * This is a convenience wrapper for the `section()` method, allowing for
	 * extracting a sub-sequence of bytes using function call syntax.
	 *
	 * @param start The starting index of the section (inclusive).
	 * @param end The ending index of the section (inclusive).
	 * @return A `std::vector<char>` containing the bytes from the specified
	 * section.
	 * @throws std::out_of_range if the requested range `[start, end]` is
	 * invalid or out of buffer bounds.
	 */
	std::vector<char> operator()(size_t start, size_t end);

	/**
	 * @brief Equality comparison operator.
	 *
	 * Compares the contents of two Buffer objects for equality. The comparison
	 * is based on both the `size` and the byte-for-byte content of the buffers.
	 *
	 * @param rhs The buffer to compare with.
	 * @return `true` if the buffers have the same size and byte content,
	 * `false` otherwise.
	 */
	bool operator==(const Buffer &rhs) const;

	/**
	 * @brief Inequality comparison operator.
	 *
	 * Compares the contents of two Buffer objects for inequality.
	 * This is the logical negation of the equality operator (`operator==`).
	 *
	 * @param rhs The buffer to compare with.
	 * @return `true` if the buffers have different sizes or byte content,
	 * `false` otherwise.
	 */
	bool operator!=(const Buffer &rhs) const;

	/**
	 * @brief Assignment operator for a C-style string.
	 *
	 * Clears the current buffer and then appends the given C-style string
	 * as its new content.
	 *
	 * @param s The null-terminated C-style string to assign.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &operator=(const char *s);

	/**
	 * @brief Appends a C-style string to the buffer.
	 *
	 * This is a convenience wrapper for the `append()` method, allowing for
	 * concatenation using the `+=` operator. The null terminator is not
	 * included in the appended data.
	 *
	 * @param s The null-terminated C-style string to append.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &operator+=(const char *s);

	/**
	 * @brief Stream insertion operator for a C-style string.
	 *
	 * Appends the given C-style string to the buffer. This is a convenience
	 * wrapper for `operator+=`, mimicking stream output. The null terminator is
	 * not included in the appended data.
	 *
	 * @param s The null-terminated C-style string to append.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &operator<<(const char *s);

	/**
	 * @brief Assignment operator for a `std::string`.
	 *
	 * Clears the current buffer and then appends the given `std::string`
	 * as its new content.
	 *
	 * @param s The `std::string` to assign.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &operator=(const std::string &s);

	/**
	 * @brief Appends a `std::string` to the buffer.
	 *
	 * This is a convenience wrapper for the `append()` method, allowing for
	 * concatenation using the `+=` operator.
	 *
	 * @param s The `std::string` to append.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &operator+=(const std::string &s);

	/**
	 * @brief Stream insertion operator for a `std::string`.
	 *
	 * Appends the given `std::string` to the buffer. This is a convenience
	 * wrapper for `operator+=`, mimicking stream output.
	 *
	 * @param s The `std::string` to append.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &operator<<(const std::string &s);

	/**
	 * @brief Retrieves the single byte character at the given index location.
	 *
	 * The index is zero-based. Performs bounds checking.
	 *
	 * @param index The zero-based index of the character to retrieve.
	 * @return The character at the specified index.
	 * @throws std::out_of_range if `index` is outside the valid data range `[0,
	 * size-1]`.
	 */
	char at(size_t index);

	/**
	 * @brief Appends the given character array (raw bytes) to the current
	 * buffer.
	 *
	 * If the buffer's current capacity is too small to accept the new data,
	 * it is resized by reallocating memory by a multiple of the `blockSize`.
	 * The input `s` is treated as a raw byte array, not necessarily
	 * null-terminated; `sLen` specifies the number of bytes to write.
	 *
	 * @param s A byte array to append.
	 * @param sLen The size of the byte array to append.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &append(const char *s, size_t sLen);

	/**
	 * @brief Appends a `std::string` to the buffer.
	 *
	 * This is a convenience method that calls `append(const char*, size_t)`.
	 *
	 * @param s A `std::string` to append to the buffer.
	 * @return A reference to the current buffer object (`*this`).
	 */
	Buffer &append(const std::string &s);

	/**
	 * @brief Returns a pointer to the last byte of the current data in the
	 * buffer.
	 *
	 * @return A `const char*` pointer to the last byte of data. If the buffer
	 * is empty or not initialized (`nullptr`), a `nullptr` is returned.
	 */
	const char *back() const;

	/**
	 * @brief Clears the buffer, effectively setting its `size` to 0.
	 *
	 * This method does NOT free the associated memory buffer.
	 *
	 * @param deep If `true`, the entire allocated capacity of the buffer is
	 * filled with the `init` character. Defaults to `false`.
	 * @param init The character to use when the `deep` option is `true`.
	 * Defaults to `0`.
	 */
	void clear(bool deep = false, char init = 0);

	/**
	 * @brief Compares two buffers to determine if their contents are the same.
	 *
	 * If the `size` of the two buffers are different, the comparison
	 * immediately fails. Otherwise, a byte-for-byte comparison is performed.
	 *
	 * @param rhs The buffer to compare with.
	 * @return `true` if the buffers are equal in size and content, `false`
	 * otherwise.
	 */
	bool compare(const Buffer &rhs) const;

	/**
	 * @brief Returns a constant pointer to the raw byte data at the front of
	 * the buffer.
	 *
	 * This pointer provides direct read-only access to the internal data array.
	 * The data is not guaranteed to be null-terminated unless explicitly added.
	 *
	 * @return A `const char*` pointer to the start of the buffer's data. Can be
	 * `nullptr` if the buffer is uninitialized.
	 */
	const char *data() const;

	/**
	 * @brief Searches through the buffer to find the first occurrence of a
	 * given C-style search pattern.
	 *
	 * @param search The null-terminated C-style string of bytes to find within
	 * the buffer.
	 * @return A `const char*` pointer to the first location within the buffer
	 * where the search string is found. If not found, `nullptr` is returned. If
	 * `search` is an empty string, returns a pointer to the start of the
	 * buffer.
	 */
	const char *find(const char *search);

	/**
	 * @brief Searches through the buffer to find the first occurrence of a
	 * given `std::string` search pattern.
	 *
	 * This is a convenience wrapper that converts the `std::string` to a
	 * C-style string and calls `find(const char*)`.
	 *
	 * @param search The `std::string` to search for in the buffer.
	 * @return A `const char*` pointer to the first location within the buffer
	 * where the search string is found. If not found, `nullptr` is returned.
	 */
	const char *find(const std::string &search);

	/**
	 * @brief Returns a constant pointer to the raw byte data at the front of
	 * the buffer.
	 *
	 * This is a convenience wrapper for `data()`.
	 *
	 * @return A `const char*` pointer to the front of the buffer.
	 */
	const char *front() const;

	/**
	 * @brief Retrieves a section (sub-sequence) of the buffer between a start
	 * and end index.
	 *
	 * This method performs bounds checking on the given range. A copy of the
	 * data is made and returned in a `std::vector<char>`.
	 *
	 * @param start The starting index position within the buffer (inclusive).
	 * @param end The ending index position within the buffer (inclusive).
	 * @return A `std::vector<char>` that contains the bytes in the buffer from
	 * the `start` to `end` position.
	 * @throws std::out_of_range if the requested range `[start, end]` is
	 * invalid or out of buffer bounds.
	 */
	std::vector<char> section(size_t start, size_t end);

	/**
	 * @brief Converts the buffer's contents into a `std::string` object.
	 *
	 * This operation creates a copy of the buffer's data. If the buffer
	 * contains non-printable characters or is not null-terminated, the
	 * resulting string might contain garbage or be unexpectedly
	 * truncated/extended.
	 *
	 * @return A `std::string` object representing the current contents of the
	 * buffer.
	 */
	std::string str();

	/**
	 * @brief Converts the buffer's contents into a `std::vector<char>`.
	 *
	 * This is an expensive operation as a new vector is allocated, its contents
	 * are copied from the buffer, and then potentially copied again on return.
	 * Changes to the `Buffer` object will NOT be reflected in the returned
	 * `std::vector<char>`.
	 *
	 * @return A new `std::vector<char>` that contains a copy of the current
	 * contents of the buffer.
	 */
	std::vector<char> vec();
};

}  // namespace ds
