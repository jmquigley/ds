#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ds/constants.hpp>
#include <string>

constexpr auto CR = constants::CR;
constexpr auto DELIM = constants::DELIM;

namespace ds {

auto dtrim(char *buf) -> char * {
	if (buf == nullptr) {
		return nullptr;
	}

	size_t len = strlen(buf);
	if (len == 0) {
		return buf;
	}

	// Handle trailing spaces
	size_t end = len - 1;
	while (end >= 0 && isspace(buf[end]) != 0) {
		end--;
	}
	buf[end + 1] = '\0';

	// Handle leading spaces
	char *start = buf;
	while (*start != '\0' && isspace(*start) != 0) {
		start++;
	}

	// If there were leading spaces, shift the string
	if (start != buf) {
		char *dst = buf;
		while (*start != '\0') {
			*dst++ = *start++;
		}
		*dst = '\0';
	}

	return buf;
}

auto moveBufferToString(const char *buf, ssize_t size) -> std::string {
	if (buf == nullptr || size <= 0) {
		return "";
	}

	std::string s(size, '\0');
	std::memcpy(s.data(), buf, size);
	return s;
}

auto removeCRLF(char *buf) -> char * {
	char *bufptr = buf;

	if (buf == nullptr) {
		return nullptr;
	}

	while (*bufptr != '\0') {
		if (*bufptr == CR || *bufptr == DELIM) {
			*bufptr = ' ';
		}

		bufptr++;
	}

	return (buf);
}

auto removeIt(char *buf, const char *charsToRemove) -> char * {
	char *bufptr = buf;
	const char *rem = nullptr;
	bool removeFlag = false;
	unsigned int offset = 0;

	if (buf == nullptr) {
		return nullptr;
	}

	if (charsToRemove == nullptr) {
		return buf;
	}

	rem = charsToRemove;

	while (*bufptr != '\0') {
		/* search the characters for the removal. */
		while ((*rem != '\0') && (!removeFlag)) {
			if (*bufptr == *rem) {
				removeFlag = true;
			}
			rem++;
		}

		if (!removeFlag) {
			buf[offset++] = *bufptr;
		}

		bufptr++;
		rem = charsToRemove;
		removeFlag = false;
	}

	buf[offset] = '\0';
	return (buf);
}

auto replaceIt(char *buf, char charToReplace, char replaceWith) -> char * {
	char *bufptr = buf;

	if (buf == nullptr) {
		return nullptr;
	}

	while (*bufptr != '\0') {
		if (*bufptr == charToReplace) {
			*bufptr = replaceWith;
		}

		bufptr++;
	}

	return (buf);
}

auto safecopy(char *dst, ssize_t dstSize, const char *src, ssize_t srcSize)
	-> bool {
	if (dst == nullptr or src == nullptr or dstSize <= 0 or srcSize < 0) {
		return false;
	}

	size_t numToCopy = std::min(dstSize, srcSize);
	std::memcpy(dst, src, numToCopy * sizeof(char));
	return true;
}

auto tokenSplit(char *buf, const char *delimit, char **databuf, int maxTokens)
	-> int {
	if (buf == nullptr || databuf == nullptr || delimit == nullptr ||
		maxTokens < 1) {
		return -1;
	}

	int index = 0;
	char *token = strtok(buf, delimit);

	while (token != nullptr && index < maxTokens) {
		databuf[index++] = token;
		token = strtok(nullptr, delimit);
	}

	return index;
}

auto upperCase(char *buf) -> char * {
	char *bufptr = nullptr;

	if (buf == nullptr) {
		return nullptr;
	}

	bufptr = buf;
	while (*bufptr != '\0') {
		*bufptr = static_cast<char>(toupper(*bufptr));
		bufptr++;
	}

	return (buf);
}

}  // namespace ds
