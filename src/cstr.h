/**
 * @brief Provides utility functions for C-style string manipulation.
 *
 * This header defines a collection of functions that perform common string
 * operations on C-style (null-terminated) character arrays, as well as
 * conversions between C strings and C++ std::string objects.
 */

#pragma once

#include <string>

/**
 * @namespace ds
 * @brief Contains data structure and utility functions.
 */
namespace ds {

/**
 * @brief Trims leading and trailing spaces from a NULL terminated buffer.
 *
 * Modifies the input string that is passed to the function.
 *
 * @code
 * char temp[30];
 * char* bufptr;
 * strcpy(temp, "     Test String     ");
 * bufptr = dtrim(temp);  // results in string "Test String"
 * @endcode
 * @param buf A NULL terminated C string
 * @return A pointer to the modified buffer
 */
char *dtrim(char *buf);

/**
 * @brief Copies the contents of a buffer into a string object.
 * @param buf A pointer to the buffer to copy
 * @param size The number of bytes to copy into the string
 * @return A string object containing the copied data
 */
std::string moveBufferToString(const char *buf, ssize_t size);

/**
 * @brief Replaces carriage return/line feed characters (0xa,0xd) with spaces.
 *
 * Changes these values to the space character. The input buffer is
 * changed in the operation.
 *
 * @param buf The input buffer to remove the CRLF from
 * @return The pointer to the original buffer with the CRLF items removed
 */
char *removeCRLF(char *buf);

/**
 * @brief Removes specified characters from an input string.
 *
 * Modifies the original input string. If a null pointer is given in the
 * characters to remove, then the original string is returned unchanged.
 * If the input buffer is a null pointer, then a null pointer is returned.
 *
 * @param buf A null terminated string to remove characters from
 * @param charsToRemove The string of characters that should be removed
 * @return A pointer to the buf with the characters removed
 */
char *removeIt(char *buf, const char *charsToRemove);

/**
 * @brief Replaces a specific character with another throughout a string.
 *
 * Changes the original string that is passed to the function.
 *
 * @param buf The null terminated buffer to perform the replacement against
 * @param charToReplace The single character to find for replacement
 * @param replaceWith The character to change to
 * @return A pointer to buf with the characters replaced
 */
char *replaceIt(char *buf, char charToReplace, char replaceWith);

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
bool safecopy(char *dst, ssize_t dstSize, const char *src, ssize_t srcSize);

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
int tokenSplit(char *buf, const char *delimit, char **databuf, int maxTokens);

/**
 * @brief Converts the input string into all uppercase characters.
 *
 * Modifies the input string that is passed to the function, so it
 * cannot be a const char* string.
 *
 * @param buf A NULL terminated C string
 * @return An ASCII string converted to upper case
 */
char *upperCase(char *buf);

}  // namespace ds
