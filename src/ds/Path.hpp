#pragma once

#include <ds/str.h>

#include <cstddef>
#include <ds/constants.hpp>
#include <ds/property.hpp>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace ds {

/**
 * @class Path
 * @brief A class for manipulating file system paths or other hierarchical path
 * structures
 *
 * The Path class provides functionality for working with path strings,
 * including operations for path construction, manipulation, and parsing. It
 * handles multiple path delimiter styles (forward slash \, backslash /, pipe |)
 * and provides methods for appending, accessing, and removing path elements.
 * When appended together the backslash is used to represent the path.
 *
 * This is a helper class for the GeneralTree object.
 *
 * Paths are stored internally as a sequence of elements (path components) which
 * can be accessed and manipulated individually.
 *
 * Example usage:
 * @code{.cpp}
 * // Create a path from components
 * ds::Path path("home", "user", "documents");  // results in
 * "/home/user/documents/"
 *
 * // Append to a path
 * path += "level";  // now "/home/user/documents/level/"
 *
 * // Access path components
 * std::string value = path[3];  // gets "level"
 * @endcode
 */
class Path final {
	/**
	 * @brief Property for the current full path string
	 */
	PROPERTY(currentPath, CurrentPath, std::string);

	/**
	 * @brief Property for the vector of path elements
	 */
	PROPERTY(elements, Elements, std::vector<std::string>);

private:

	const static inline std::vector<std::string> _delimiters {"\\", "/", "|"};

	/**
	 * @brief Builds a path string from the current elements
	 *
	 * Joins all path elements with the separator defined in
	 * constants::SEPARATOR and updates the _currentPath property.
	 *
	 * @return The built path string
	 */
	std::string buildPath() {
		this->_currentPath =
			join(this->_elements, constants::SEPARATOR, true, true);
		return this->_currentPath;
	}

public:

	/**
	 * @brief Default constructor
	 *
	 * Creates an empty path with no elements.
	 */
	Path() : _currentPath("") {}

	/**
	 * @brief Variadic constructor to create a path from multiple components
	 *
	 * This constructor will only allow the variables to be of type std::string
	 *
	 * @tparam Args Variadic template parameter for different argument types
	 * @param args Variable number of arguments representing path components
	 * @throws an assertion error if any of the parameters given are not
	 * std::string
	 */
	template<typename... Args>
	explicit Path(Args... args) : Path() {
		this->newPath(args...);
	}

	/**
	 * @brief Copy constructor
	 *
	 * Creates a new Path object as a copy of the provided Path.
	 *
	 * @param path The Path object to copy
	 */
	Path(const Path &path)
		: _currentPath(path._currentPath), _elements(path._elements) {}

	/**
	 * @brief an initializer list to build a path
	 * @param il (`std::initializer_list`) a list of values to seed the path
	 */
	explicit Path(std::initializer_list<std::string> il) : Path() {
		for (auto &it: il) {
			this->append(it);
		}
		this->buildPath();
	}

	/**
	 * @brief A basic destructor for the Path class
	 */
	~Path() {
		this->clear();
	}

	/**
	 * @brief Unary operator to clear the path
	 *
	 * Using the ~ operator on a Path object clears all its elements.
	 */
	void operator~() {
		this->clear();
	}

	/**
	 * @brief Array subscript operator to access path elements
	 *
	 * @param index The index of the element to access
	 * @return The path element at the specified index
	 * @throws std::out_of_range if the index is invalid
	 */
	std::string operator[](size_t index) const {
		return this->at(index);
	}

	/**
	 * @brief Function call operator to create a new path
	 *
	 * Allows using the Path object like a function to create a new path.
	 *
	 * @tparam Args Variadic template parameter for different argument types
	 * @param args Variable number of arguments representing path components
	 * @return The new path string
	 */
	template<typename... Args>
	std::string operator()(Args... args) {
		return this->newPath(args...);
	}

	/**
	 * @brief Addition assignment operator to append a path element
	 *
	 * @param val The path element to append
	 * @return Reference to this Path object after appending
	 */
	Path &operator+=(const std::string val) {
		this->append(val);
		return *this;
	}

	/**
	 * @brief Subtraction assignment operator to remove a path element
	 *
	 * @param val The path element to append
	 * @return Reference to this Path object after removing
	 */
	Path &operator-=(const std::string val) {
		this->removeValue(val);
		return *this;
	}

	/**
	 * @brief Assignment operator to set the path from a string
	 *
	 * @param path The path string to parse and assign
	 * @return Reference to this Path object after assignment
	 */
	Path &operator=(const std::string path) {
		this->parse(path);
		return *this;
	}

	/**
	 * @brief Assignment operator for Path objects
	 *
	 * @param path The Path object to copy from
	 * @return Reference to this Path object after assignment
	 */
	Path &operator=(const Path &path) {
		this->_currentPath = path._currentPath;
		this->_elements = path._elements;
		return *this;
	}

	/**
	 * @brief Equality comparison operator
	 *
	 * Compares the current path string with another Path object's path string.
	 *
	 * @param other The Path object to compare with
	 * @return true if the paths are equal, false otherwise
	 */
	bool operator==(const Path &other) const {
		return this->_currentPath == other._currentPath;
	}

	/**
	 * @brief Inequality comparison operator
	 *
	 * @param other The Path object to compare with
	 * @return true if the paths are not equal, false otherwise
	 */
	bool operator!=(const Path &other) const {
		return this->_currentPath != other._currentPath;
	}

	/**
	 * @brief Less than comparison operator
	 *
	 * Compares the current path string with another Path object's path string.
	 *
	 * @param other The Path object to compare with
	 * @return true if this path is lexicographically less than the other path
	 */
	bool operator<(const Path &other) const {
		return this->_currentPath < other._currentPath;
	}

	/**
	 * @brief Greater than comparison operator
	 *
	 * @param other The Path object to compare with
	 * @return true if this path is lexicographically greater than the other
	 * path
	 */
	bool operator>(const Path &other) const {
		return this->_currentPath > other._currentPath;
	}

	/**
	 * @brief Stream insertion operator
	 *
	 * Allows writing a Path object directly to an output stream.
	 *
	 * @param st The output stream
	 * @param path The Path object to output
	 * @return Reference to the output stream
	 */
	friend std::ostream &operator<<(std::ostream &st, const Path &path) {
		return st << path.str();
	}

	/**
	 * @brief Appends an element to the path
	 *
	 * @param val The path element to append
	 * @return The new path string after appending
	 */
	std::string append(const std::string &val) {
		if (containsAnySubstring(val, Path::_delimiters)) {
			this->parse(val, false);
		} else {
			this->_elements.push_back(val);
		}

		return this->buildPath();
	}

	/**
	 * @brief Accesses a path element at the specified index
	 *
	 * @param index The index of the element to access
	 * @return The path element at the specified index
	 * @throws std::out_of_range if the index is invalid
	 */
	std::string at(size_t index) const {
		if (index >= this->_elements.size()) {
			throw std::out_of_range(
				"Invalid path element position index requested");
		}

		return this->_elements[index];
	}

	/**
	 * @brief Clears the path
	 *
	 * Removes all elements from the path and resets it to an empty state.
	 */
	void clear() {
		this->_currentPath = "";
		this->_elements.clear();
	}

	/**
	 * @brief checks if the current path is empty
	 * @returns true if the path is empty
	 * @returns false if the path has a value
	 */
	inline bool empty() const {
		return this->_currentPath == "";
	}

	/**
	 * @brief Creates a new path from the provided components
	 *
	 * Clears any existing path elements and creates a new path from
	 * the specified components.  This method will only accept const char *
	 * or std::string elements in args.
	 *
	 * @tparam Args Variadic template parameter for different argument types
	 * @param args Variable number of arguments representing path components
	 * @return The new path string
	 */
	template<typename... Args>
	std::string newPath(Args... args) {
		static_assert(std::conjunction_v<
						  std::is_same<std::decay_t<Args>, const char *>...> ||
						  std::conjunction_v<
							  std::is_same<std::decay_t<Args>, std::string>...>,
					  "All arguments to newPath() must be std::string.");

		this->_elements.clear();
		for (const auto &val: {args...}) {
			this->append(val);
		}

		return this->buildPath();
	}

	/**
	 * @brief Parses a path string into individual elements
	 *
	 * Splits the provided path string on any of the delimiters defined in
	 * the delimiters vector, and stores the resulting elements.
	 *
	 * @param path (`std::string`) The path string to parse
	 * @param build (`bool`) a flag to suppress rebuilding the path when needed
	 * @return The parsed and rebuilt path string
	 */
	std::string parse(const std::string &path, bool build = true) {
		this->_elements = splitStringOnDelimiters(path, Path::_delimiters);
		if (build) {
			return buildPath();
		}
		return this->_currentPath;
	}

	/**
	 * @returns Returns the current value of the path inside of this object.
	 */
	std::string path() const {
		return this->_currentPath;
	}

	/**
	 * @brief Removes a path element at the specified index
	 *
	 * @param index The index of the element to remove
	 * @throws std::out_of_range if the index is invalid
	 */
	void removeAt(size_t index) {
		if (index >= this->_elements.size()) {
			throw std::out_of_range(
				"Invalid path element position index requested");
		}

		this->_elements.erase(this->_elements.begin() + index);
		this->buildPath();
	}

	/**
	 * @brief Removes an element from the path based on its name value.
	 * @param str (`std::string &`) the value that should be removed from
	 * the path list.
	 */
	void removeValue(const std::string &str) {
		removeFirstOccurrence(this->_elements, str);
		this->buildPath();
	}

	/**
	 * @returns the number of elements currently stored in this path
	 */
	size_t size() const {
		return this->_elements.size();
	}

	/**
	 * @brief Returns the string representation of the path
	 *
	 * @return The current path string
	 */
	std::string str() const {
		return this->_currentPath;
	}
};

}  // namespace ds
