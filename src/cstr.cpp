#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string>

namespace ds {

/**
 * @brief Trims leading and trailing spaces from a NULL terminated buffer.
 *
 * Modifies the input string that is passed to the function.
 *
 * @example
 * char temp[30];
 * char* bufptr;
 * strcpy(temp, "     Test String     ");
 * bufptr = dtrim(temp);  // results in string "Test String"
 *
 * @param buf A NULL terminated C string
 * @return A pointer to the modified buffer
 */
char *dtrim(char *buf) {
	if (buf == nullptr) {
		return nullptr;
	}

	int len = strlen(buf);
	if (len == 0) {
		return buf;
	}

	// Handle trailing spaces
	int end = len - 1;
	while (end >= 0 && isspace(buf[end])) {
		end--;
	}
	buf[end + 1] = '\0';

	// Handle leading spaces
	char *start = buf;
	while (*start && isspace(*start)) {
		start++;
	}

	// If there were leading spaces, shift the string
	if (start != buf) {
		char *dst = buf;
		while (*start) {
			*dst++ = *start++;
		}
		*dst = '\0';
	}

	return buf;
}

/**
 * @brief Copies the contents of a buffer into a string object.
 *
 * @param buf A pointer to the buffer to copy
 * @param size The number of bytes to copy into the string
 * @return A string object
 */
std::string moveBufferToString(const char *buf, ssize_t size) {
	if (buf == nullptr || size <= 0) {
		return "";
	}

	std::string s(size, '\0');
	std::memcpy(&s[0], buf, size);
	return s;
}

/**
 * @brief Replaces the carriage return/line feed (0xa,0xd) from the input
 * buffer.
 *
 * Changes these values to the space character. The input buffer is
 * changed in the operation.
 *
 * @param buf The input buffer to remove the CRLF from
 * @return The pointer to the original buffer with the CRLF items removed
 */
char *removeCRLF(char *buf) {
	char *bufptr = buf;

	if (buf == nullptr) {
		return nullptr;
	}

	while (*bufptr) {
		if (*bufptr == 0x0a) {
			*bufptr = ' ';
		} else if (*bufptr == 0x0d) {
			*bufptr = ' ';
		}

		bufptr++;
	}

	return (buf);
}

/**
 * @brief Removes a multiple set of characters from an input string.
 *
 * Modifies the original input string. If a null pointer is given in the
 * characters to remove, then the original string is returned unchanged.
 * If the input buffer is a null pointer, then a null pointer is returned.
 *
 * @param buf A null terminated string with characters to remove
 * @param charsToRemove The string of characters that should be removed
 * @return A pointer to the buf with the characters removed
 */
char *removeIt(char *buf, const char *charsToRemove) {
	char *bufptr = buf;
	const char *rem = nullptr;
	bool removeFlag;
	unsigned int offset;

	if (buf == nullptr) {
		return nullptr;
	}

	if (charsToRemove == nullptr) {
		return buf;
	}

	offset = 0;
	removeFlag = false;
	rem = charsToRemove;

	while (*bufptr) {
		/* search the characters for the removal. */
		while ((*rem) && (!removeFlag)) {
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

/**
 * @brief Replaces a character in a string with another in the entire string.
 *
 * Changes the original string that is passed to the function.
 *
 * @param buf The null terminated buffer to perform the replacement against
 * @param charToReplace The single character to find for replacement
 * @param replaceWith The character to change to
 * @return A pointer to buf with the characters replaced
 */
char *replaceIt(char *buf, char charToReplace, char replaceWith) {
	char *bufptr = buf;

	if (buf == nullptr) {
		return nullptr;
	}

	while (*bufptr) {
		if (*bufptr == charToReplace) {
			*bufptr = replaceWith;
		}

		bufptr++;
	}

	return (buf);
}

/**
 * @brief Performs a safe copy operation from a source to a destination buffer.
 *
 * Makes no assumptions about the NULL terminators in either string.
 * Uses the size variables of the src/dst and determines the smallest
 * and uses that as the upper bound.
 *
 * @param dst Pointer to the destination data location
 * @param dstSize The size of the destination buffer
 * @param src Pointer to the source of the data
 * @param srcSize The size of the source buffer
 * @return True if the data is copied, otherwise false
 */
bool safecopy(char *dst, ssize_t dstSize, const char *src, ssize_t srcSize) {
	if (dst == nullptr or src == nullptr or dstSize <= 0 or srcSize < 0) {
		return false;
	}

	size_t numToCopy = std::min(dstSize, srcSize);
	std::memcpy(dst, src, numToCopy * sizeof(char));
	return true;
}

/**
 * @brief Splits an incoming buffer into logical tokens by a user defined
 * delimiter.
 *
 * The incoming buffer is modified during tokenization.
 *
 * @param buf A null terminated string to break up into tokens
 * @param delimit The string that should be used to split on
 * @param databuf An array of pointers to store the tokens
 * @param maxTokens The maximum number of tokens to be parsed
 * @return The number of tokens created, or -1 on error
 */
int tokenSplit(char *buf, const char *delimit, char **databuf, int maxTokens) {
	if (buf == nullptr || databuf == nullptr || delimit == nullptr || maxTokens < 1) {
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

/**
 * @brief Converts the input string into all uppercase characters.
 *
 * Modifies the input string that is passed to the function, so it
 * cannot be a const char* string.
 *
 * @param buf A NULL terminated C string
 * @return An ASCII string converted to upper case
 */
char *upperCase(char *buf) {
	char *bufptr = nullptr;

	if (buf == nullptr) {
		return nullptr;
	}

	bufptr = buf;
	while (*bufptr) {
		*bufptr = toupper(*bufptr);
		bufptr++;
	}

	return (buf);
}

}  // namespace ds
