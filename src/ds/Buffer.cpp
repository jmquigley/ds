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

Buffer::Buffer(size_t blockSize)
	: _blockSize(blockSize), _capacity(blockSize), _size(0) {
	allocator("", 0, blockSize);
}

Buffer::Buffer(const char *s, size_t sSize, size_t blockSize)
	: _blockSize(blockSize), _capacity(blockSize), _size(0) {
	allocator(s, sSize, blockSize);
}

Buffer::Buffer(const std::string &s, size_t blockSize)
	: _blockSize(blockSize), _capacity(blockSize), _size(0) {
	allocator(s.c_str(), s.size(), blockSize);
}

Buffer::Buffer(Buffer &buf) {
	*this = buf;
}

Buffer::~Buffer() {
	if (this->buffer) {
		free(this->buffer);
		this->buffer = nullptr;
	}
}

Buffer &Buffer::operator~() {
	this->clear();
	return *this;
}

char Buffer::operator[](size_t index) {
	return at(index);
}

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

std::vector<char> Buffer::operator()(size_t start, size_t end) {
	return section(start, end);
}

bool Buffer::operator==(const Buffer &rhs) const {
	return this->compare(rhs);
}

bool Buffer::operator!=(const Buffer &rhs) const {
	return !this->compare(rhs);
}

Buffer &Buffer::operator+=(const char *s) {
	this->append(s, std::strlen(s));
	return *this;
}

Buffer &Buffer::operator=(const char *s) {
	this->clear();
	return this->operator+=(s);
}

Buffer &Buffer::operator<<(const char *s) {
	return this->operator+=(s);
}

Buffer &Buffer::operator+=(const std::string &s) {
	this->append(s);
	return *this;
}

Buffer &Buffer::operator=(const std::string &s) {
	this->clear();
	return this->operator+=(s);
}

Buffer &Buffer::operator<<(const std::string &s) {
	return this->operator+=(s);
}

void Buffer::allocator(const char *s, size_t sSize, size_t blockSize) {
	this->buffer = (char *)malloc(sizeof(char) * blockSize);
	memset(this->buffer, 0, sizeof(char) * blockSize);

	if (sSize > 0) {
		append(s, sSize);
	}
}

Buffer &Buffer::append(const char *s, size_t sLen) {
	// If the capacity size is exceeded by the new string, expand the buffer
	if (this->_size + sLen > this->_capacity) {
		expand(this->_size + sLen);
	}

	std::memcpy(&this->buffer[this->_size], s, sLen);
	this->_size += sLen;

	return *this;
}

Buffer &Buffer::append(const std::string &s) {
	return append(s.c_str(), s.size());
}

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

const char *Buffer::back() const {
	if (this->buffer != nullptr and this->_size > 0) {
		return this->buffer + (this->_size - 1);
	}

	return nullptr;
}

void Buffer::clear(bool deep, char init) {
	if (deep) {
		memset(this->buffer, init, this->_capacity);
	}

	this->_size = 0;
}

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

const char *Buffer::data() const {
	return this->buffer;
}

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

const char *Buffer::find(const std::string &search) {
	return this->find(search.c_str());
}

const char *Buffer::front() const {
	return this->data();
}

std::string Buffer::str() {
	return moveBufferToString(this->buffer, this->_size);
}

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

std::vector<char> Buffer::vec() {
	std::vector<char> v(this->_size);
	std::memcpy(&v[0], this->buffer, this->_size);

	return v;
}

bool Buffer::withinRange(size_t start, size_t end) {
	return (end >= start and start < this->_size and end < this->_size);
}

}  // namespace ds
