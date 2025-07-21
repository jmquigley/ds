/**
 * @brief Represents a dynamically-sized byte buffer.
 *
 * This class provides a flexible way to manage a sequence of bytes,
 * offering functionalities similar to a dynamic array or string for raw
 * byte data. It allocates memory in blocks to optimize reallocations
 * and provides methods for appending, retrieving, searching, and
 * comparing byte sequences.
 */
#include <ds/Buffer.h>
#include <ds/cstr.h>

#include <cmath>
#include <cstddef>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace ds {

/**
 * @brief Constructor for an empty Buffer with a specified block size.
 *
 * Initializes the buffer with a given block size, setting initial capacity
 * and size to zero, and allocating the first block of memory.
 *
 * @param blockSize The size in bytes for each memory block.
 */
Buffer::Buffer(size_t blockSize)
	: _blockSize(blockSize), _capacity(blockSize), _size(0) {
	allocator("", 0, blockSize);
}

/**
 * @brief Constructor for a Buffer initialized from a C-style string.
 *
 * Initializes the buffer with content from a C-style string and a specified
 * block size.
 *
 * @param s A C-style string to initialize the buffer.
 * @param sSize The size of the C-style string (number of bytes).
 * @param blockSize The size in bytes for each memory block.
 */
Buffer::Buffer(const char *s, size_t sSize, size_t blockSize)
	: _blockSize(blockSize), _capacity(blockSize), _size(0) {
	allocator(s, sSize, blockSize);
}

/**
 * @brief Constructor for a Buffer initialized from a `std::string`.
 *
 * Initializes the buffer with content from a `std::string` and a specified
 * block size.
 *
 * @param s A `std::string` to initialize the buffer.
 * @param blockSize The size in bytes for each memory block.
 */
Buffer::Buffer(const std::string &s, size_t blockSize)
	: _blockSize(blockSize), _capacity(blockSize), _size(0) {
	allocator(s.c_str(), s.size(), blockSize);
}

/**
 * @brief Copy constructor.
 *
 * Initializes a new Buffer object by copying the contents from an existing
 * Buffer object. This implementation relies on the copy assignment operator.
 *
 * @note This constructor takes a non-const reference, which prevents copying
 * from const Buffer objects or rvalues.
 *
 * @param buf The Buffer object to copy from.
 */
Buffer::Buffer(Buffer &buf) {
	*this = buf;
}

/**
 * @brief Destructor for the Buffer object.
 *
 * Frees the dynamically allocated memory for the internal buffer if it exists.
 */
Buffer::~Buffer() {
	if (this->buffer) {
		free(this->buffer);
		this->buffer = nullptr;
	}
}

/**
 * @brief Operator to clear the buffer.
 *
 * This is a convenience wrapper for the `clear` function, resetting the
 * buffer's size to zero.
 *
 * @return A reference to the current buffer object (`*this`).
 */
Buffer &Buffer::operator~() {
	this->clear();
	return *this;
}

/**
 * @brief Operator to access a character at a specific index.
 *
 * This is a convenience wrapper operator for the `at` function, providing
 * direct access to buffer elements.
 *
 * @param index The zero-based index of the character to retrieve.
 * @return The character at the specified index.
 */
char Buffer::operator[](size_t index) {
	return at(index);
}

/**
 * @brief Copy assignment operator.
 *
 * Clears the current buffer's contents, frees its existing internal memory,
 * and then re-allocates new memory to copy the contents of the right-hand side
 * buffer.
 *
 * @note This operator takes a non-const reference, which prevents assigning
 * from const Buffer objects or rvalues.
 *
 * @param rhs The buffer to copy from.
 * @return A reference to the current buffer object (`*this`).
 */
Buffer &Buffer::operator=(Buffer &rhs) {
	// It's crucial that 'this->buffer' is valid/initialized before 'clear' and
	// 'free' are called. In a typical assignment, 'this' would be a fully
	// constructed object.
	this->clear();
	free(this->buffer);	 // Free existing memory

	this->_blockSize = rhs.getBlockSize();
	this->_capacity = 0;  // Will be set by allocator based on rhs's capacity
	this->_size = 0;	  // Will be set by allocator/append

	this->allocator(rhs.data(), rhs.getSize(),
					rhs.getCapacity());	 // Re-allocate and copy content

	return *this;
}

/**
 * @brief Operator to extract a section of the buffer.
 *
 * This is a convenience wrapper for the `section` method, allowing for
 * extracting a sub-sequence of bytes using function call syntax.
 *
 * @param start The starting index of the section (inclusive).
 * @param end The ending index of the section (inclusive).
 * @return A `std::vector<char>` containing the bytes from the specified
 * section.
 */
std::vector<char> Buffer::operator()(size_t start, size_t end) {
	return section(start, end);
}

/**
 * @brief Equality comparison operator.
 *
 * Compares the contents of two Buffer objects for equality. The comparison
 * is based on both the size and the byte-for-byte content of the buffers.
 *
 * @param rhs The buffer to compare with.
 * @return `true` if the buffers have the same size and byte content, `false`
 * otherwise.
 */
bool Buffer::operator==(const Buffer &rhs) const {
	return this->compare(rhs);
}

/**
 * @brief Inequality comparison operator.
 *
 * Compares the contents of two Buffer objects for inequality.
 * This is the logical negation of the equality operator.
 *
 * @param rhs The buffer to compare with.
 * @return `true` if the buffers have different sizes or byte content, `false`
 * otherwise.
 */
bool Buffer::operator!=(const Buffer &rhs) const {
	return !this->compare(rhs);
}

/**
 * @brief Appends a C-style string to the buffer.
 *
 * This is a convenience wrapper for the `append` method, allowing for
 * concatenation using the `+=` operator.
 *
 * @param s The null-terminated C-style string to append.
 * @return A reference to the current buffer object (`*this`).
 */
Buffer &Buffer::operator+=(const char *s) {
	this->append(s, std::strlen(s));
	return *this;
}

/**
 * @brief Assignment operator for a C-style string.
 *
 * Clears the current buffer and then appends the given C-style string
 * as its new content.
 *
 * @param s The null-terminated C-style string to assign.
 * @return A reference to the current buffer object (`*this`).
 */
Buffer &Buffer::operator=(const char *s) {
	this->clear();
	return this->operator+=(s);
}

/**
 * @brief Stream insertion operator for a C-style string.
 *
 * Appends the given C-style string to the buffer. This is a convenience
 * wrapper for `operator+=`, mimicking stream output.
 *
 * @param s The null-terminated C-style string to append.
 * @return A reference to the current buffer object (`*this`).
 */
Buffer &Buffer::operator<<(const char *s) {
	return this->operator+=(s);
}

/**
 * @brief Appends a `std::string` to the buffer.
 *
 * This is a convenience wrapper for the `append` method, allowing for
 * concatenation using the `+=` operator.
 *
 * @param s The `std::string` to append.
 * @return A reference to the current buffer object (`*this`).
 */
Buffer &Buffer::operator+=(const std::string &s) {
	this->append(s);
	return *this;
}

/**
 * @brief Assignment operator for a `std::string`.
 *
 * Clears the current buffer and then appends the given `std::string`
 * as its new content.
 *
 * @param s The `std::string` to assign.
 * @return A reference to the current buffer object (`*this`).
 */
Buffer &Buffer::operator=(const std::string &s) {
	this->clear();
	return this->operator+=(s);
}

/**
 * @brief Stream insertion operator for a `std::string`.
 *
 * Appends the given `std::string` to the buffer. This is a convenience
 * wrapper for `operator+=`, mimicking stream output.
 *
 * @param s The `std::string` to append.
 * @return A reference to the current buffer object (`*this`).
 */
Buffer &Buffer::operator<<(const std::string &s) {
	return this->operator+=(s);
}

/**
 * @brief Allocates the internal space and assigns an initial value if one is
 * given for the buffer.
 *
 * @param s (`const char*`) a byte string to assign to the initial
 *        buffer when it is created.
 * @param sSize (`size_t`) the size of the initial buffer
 * @param blockSize (`size_t`) the size of each buffer memory block
 * @returns Nothing
 */
void Buffer::allocator(const char *s, size_t sSize, size_t blockSize) {
	this->buffer = (char *)malloc(sizeof(char) * blockSize);
	memset(this->buffer, 0, sizeof(char) * blockSize);

	if (sSize > 0) {
		append(s, sSize);
	}
}

/**
 * Appends the given character array to the current buffer at the
 * current size + 1 position.  If the buffer is too small to accept
 * string, then it is resized by reallocating the memory by a multiple
 * of the blocksize.  The given input buffer is NOT a NULL terminated
 * string and uses the size value to determine the number of bytes that
 * should be written.
 *
 * Parameters:
 *     - s (`const char *`) -- a byte array to append
 *     - sLen (`size_t`) -- the size of the byte array to append
 *
 * Returns:
 *     A reference to the current buffer object.
 */
Buffer &Buffer::append(const char *s, size_t sLen) {
	// If the capacity size is exceeded by the new string, expand the buffer
	if (this->_size + sLen > this->_capacity) {
		expand(this->_size + sLen);
	}

	std::memcpy(&this->buffer[this->_size], s, sLen);
	this->_size += sLen;

	return *this;
}

/**
 * A convenience method to call append with a string reference
 *
 * Parameters:
 *     - s (`string&`) -- a string to append to the buffer.
 * Returns:
 *     A reference to the current buffer object.
 */
Buffer &Buffer::append(const std::string &s) {
	return append(s.c_str(), s.size());
}

/**
 * Retrieves the single byte character at the given index location.
 * If outside of the range an *out_of_range* exception is thrown.
 * The index is zero based.
 *
 * Parameters:
 *     - index (`size_t`) -- the location within the buffer
 *
 * Returns:
 *     a single byte character at the given position.
 */
char Buffer::at(size_t index) {
	std::stringstream ss;

	if (index < 0 or
		index >
			this->_size - 1) {	// Note: index < 0 is always false for size_t
		ss << "invalid index given at(" << index << ")";
		throw std::out_of_range(ss.str());
	}

	return this->buffer[index];
}

/**
 * Returns:
 *     a pointer to the end of the current data buffer.  If the buffer
 *     is bad or empty a nullptr is returned.
 */
const char *Buffer::back() const {
	if (this->buffer != nullptr and this->_size > 0) {
		return this->buffer + (this->_size - 1);
	}

	return nullptr;
}

/**
 * Sets the size of the buffer to 0, which effectively empties the
 * buffer.  It does NOT free the associated memory buffer.  When the
 * deep flag is used, then the contents of the whole buffer, based on
 * its capacity, are set to a specified character.
 *
 * Parameters:
 *     - deep (`bool`) -- if true, all values in the allocated capacity are set
 * to zero. The default is to not perform that operation.
 *     - init (`char`) -- the character to use when using the deep
 *       option.
 *
 * Returns:
 *     Nonthing
 */
void Buffer::clear(bool deep, char init) {
	if (deep) {
		memset(this->buffer, init, this->_capacity);
	}

	this->_size = 0;
}

/**
 * Compares two buffers to determine if their contents are the same.
 * If the sizes are different it will immediately fail.
 *
 * Parameters:
 *     - rhs (`const Buffer&`) -- the right hand side of the comparison
 *
 * Returns:
 *     True if the buffers are equal in size and contents.
 */
bool Buffer::compare(const Buffer &rhs) const {
	if (this->_size != rhs.getSize()) {
		return false;
	}

	char *lptr = this->buffer;
	const char *rptr = rhs.data();

	for (size_t i = 0; i < this->_size; i++) {
		if (*lptr++ != *rptr++) {
			return false;
		}
	}

	return true;
}

/**
 * Returns:
 *     A pointer to the data at the front of the buffer
 */
const char *Buffer::data() const {
	return this->buffer;
}

/**
 * Expands the current buffer by the given size as long as the given size is
 * greater than the current capacity.  If the size is smaller than the current
 * capacity, then no action is taken.  This is an internal convenience method.
 *
 * Parameters:
 *     - len (`size_t`) -- the new size that the current capacity will be
 * expanded to
 *
 * Returns:
 *     Returns a pointer reference to the current buffer
 */
const char *Buffer::expand(size_t len) {
	if (len > 0 and len > this->_capacity) {
		// compute a new capacity size as a multiple of blockSize.
		size_t newCapacity = std::ceil(static_cast<float>(len) /
									   static_cast<float>(this->_blockSize)) *
							 this->_blockSize;
		char *newBuffer = (char *)realloc(this->buffer, newCapacity);

		if (newBuffer == nullptr) {
			throw std::runtime_error("Memory error expanding buffer");
		} else {
			this->buffer = newBuffer;
			this->_capacity = newCapacity;
		}
	}

	return this->buffer;
}

/**
 * Searches through the buffer to find the given search pattern string.  The
 * search string should be null terminated. An out of range error exception will
 * be thrown if the end of the buffer is smaller than the start.
 *
 * Parameters:
 *     - search (`const char *`) -- the string of bytes to find within the
 * buffer.
 *
 * Returns:
 *     A pointer to the first location within the buffer where the seardh string
 * is found.  If not found, then nullptr is returned.
 */
const char *Buffer::find(const char *search) {
	if (search == nullptr) {
		return nullptr;
	}

	ssize_t slen = strlen(search);
	ssize_t start = 0;
	ssize_t end = this->_size - slen;

	if (end < start) {
		std::stringstream ss;
		ss << "invalid searh range, start:" << start << ", end:" << end;
		throw std::out_of_range(ss.str());
	}

	char *bufptr = this->buffer;
	for (ssize_t i = 0; i < end; i++) {
		if (!std::memcmp(bufptr, search, slen)) {
			return bufptr;
		}

		bufptr++;
	}

	return nullptr;
}

/**
 * A convenience wrapper to pass a c style string to the find function.
 *
 * Parameters:
 *     - search (`std::string &`) -- the string to search for in the buffer
 *
 * Returns:
 *     A pointer to the first location within the buffer where the seardh string
 * is found.  If not found, then nullptr is returned.
 */
const char *Buffer::find(const std::string &search) {
	return this->find(search.c_str());
}

/**
 * Convenience wrapper for the data command to get a pointer to the
 * front of the buffer.
 *
 * Returns:
 *     A const char pointer to the front of the buffer
 */
const char *Buffer::front() const {
	return this->data();
}

/**
 * Takes the current buffer and returns it as a string object
 * equivalent.
 *
 * Returns:
 *     A string object representing the buffer.
 */
std::string Buffer::str() {
	return moveBufferToString(this->buffer, this->_size);
}

/**
 * Retrieves a section of a buffer between a start/end point.  It will check the
 * range and throw an out of range exception if any values fall outside.  A
 * copy of the data is made in this call.
 *
 * Parameters:
 *     - start (`size_t`) -- starting index position within the buffer
 * (inclusive)
 *     - end (`size_t`) -- ending index position within the buffer (inclusive)
 *
 * Returns:
 *     A standard vector that contains the bytes in the buffer from the start to
 *     end position.
 */
std::vector<char> Buffer::section(size_t start, size_t end) {
	std::stringstream ss;

	if (!withinRange(start, end)) {
		ss << "invalid section requested at start:" << start << ", end:" << end;
		throw std::out_of_range(ss.str());
	}

	size_t len = end - start + 1;
	std::vector<char> v(len);
	char *bufptr = buffer + start;
	std::memcpy(&v[0], bufptr, len);

	return v;
}

/**
 * Converts the buffer into a vector and returns it as a copy.  This is an
 * expensive operation because the vector is allocated, copied, and then copied
 * on return after it has been created. Changes to the buffer will NOT be
 * reflected within this vector.
 *
 * Returns:
 *     A new standard vector that contains the current contents of the buffer.
 */
std::vector<char> Buffer::vec() {
	std::vector<char> v(this->_size);
	std::memcpy(&v[0], this->buffer, this->_size);

	return v;
}

/**
 * Checks if the start/end values fall within the range of the current buffer.
 *
 * Parameters:
 *     - start (`size_t`) -- The starting index to check.
 *     - end (`size_t`) -- The ending index to check.
 *
 * Returns:
 *     true if both `start` and `end` are valid indices and `start` is less than
 * or equal to `end`, otherwise false.
 */
bool Buffer::withinRange(size_t start, size_t end) {
	return (end >= start and start < this->_size and end < this->_size);
}

}  // namespace ds
