#pragma once

#include <cstddef>
#include <ds/property.hpp>
#include <list>
#include <unordered_map>

namespace ds {

/**
 * @class LRUCache
 * @brief Implements a Least Recently Used (LRU) cache with fixed capacity
 *
 * This cache maintains items in order of use, evicting the least recently used
 * items when the capacity is exceeded. Each get or set operation moves the
 * accessed item to the front of the cache (marking it as most recently used).
 *
 * @tparam K The key type used to identify cached items
 * @tparam V The value type to be stored (defaults to the same as key type)
 *
 * @note This implementation provides O(1) complexity for both get and set
 * operations
 *
 * @par Basic Usage Example:
 * @code{.cpp}
 * // Create a cache with integers as keys and strings as values, capacity of 3
 * ds::LRUCache<int, std::string> cache(3);
 *
 * // Add some items to the cache
 * cache.set(1, "one");
 * cache.set(2, "two");
 * cache.set(3, "three");
 *
 * // Retrieve values
 * std::string value;
 * if (cache.get(2, value)) {
 *     std::cout << "Found value: " << value << std::endl; // Outputs: Found
 * value: two
 * }
 *
 * // Adding a fourth item will evict the least recently used item (key 1)
 * cache.set(4, "four");
 *
 * // Key 1 is no longer in the cache
 * if (!cache.contains(1)) {
 *     std::cout << "Key 1 was evicted" << std::endl;
 * }
 * @endcode
 *
 * @par Using Custom Types as Keys:
 * @code{.cpp}
 * struct CustomKey {
 *     int id;
 *     std::string name;
 *
 *     // Must provide equality operator for unordered_map
 *     bool operator==(const CustomKey& other) const {
 *         return id == other.id && name == other.name;
 *     }
 * };
 *
 * // Must provide hash function for custom key
 * namespace std {
 *     template<>
 *     struct hash<CustomKey> {
 *         size_t operator()(const CustomKey& key) const {
 *             return hash<int>()(key.id) ^ hash<string>()(key.name);
 *         }
 *     };
 * }
 *
 * // Now we can use CustomKey as the key type
 * ds::LRUCache<CustomKey, int> customCache(10);
 * customCache.set({1, "test"}, 42);
 * @endcode
 *
 * @par Complex Value Types:
 * @code{.cpp}
 * struct User {
 *     int id;
 *     std::string name;
 *     std::vector<std::string> permissions;
 * };
 *
 * // Cache using string keys and User values
 * ds::LRUCache<std::string, User> userCache(100);
 *
 * // Store a user
 * User admin = {1, "Admin", {"read", "write", "delete"}};
 * userCache.set("admin", admin);
 *
 * // Retrieve the user
 * User retrievedUser;
 * if (userCache.get("admin", retrievedUser)) {
 *     // Use the retrieved user
 *     std::cout << "Found user: " << retrievedUser.name << std::endl;
 * }
 * @endcode
 *
 * @par Cache Management:
 * @code{.cpp}
 * ds::LRUCache<std::string, int> cache(5);
 *
 * // Add some items
 * cache.set("a", 1);
 * cache.set("b", 2);
 *
 * // Check size and if empty
 * std::cout << "Cache size: " << cache.size() << std::endl;  // Outputs: 2
 * std::cout << "Is empty: " << (cache.empty() ? "yes" : "no") << std::endl;  //
 * Outputs: no
 *
 * // Check if a key exists without affecting LRU order
 * if (cache.contains("a")) {
 *     std::cout << "Cache contains key 'a'" << std::endl;
 * }
 *
 * // Clear the cache
 * cache.clear();
 * std::cout << "After clear, size: " << cache.size() << std::endl;  // Outputs:
 * 0
 * @endcode
 */
template<typename K, typename V = K>
class LRUCache final {
	/// @brief The maximum number of items the cache can hold
	PROPERTY(capacity, Capacity, size_t);

	/// @brief List maintaining the order of keys from most to least recently
	/// used
	PROPERTY(items, Items, std::list<K>);

private:

	/** Map from keys to their values and positions in the items list */
	std::unordered_map<K, std::pair<V, typename std::list<K>::iterator>> kvm;

public:

	/** If the capacity given is 0, then set it to this value to ensure that
	the cache has space to store values */
	inline static size_t MIN_CAPACITY {100};

	LRUCache() : _capacity(LRUCache::MIN_CAPACITY) {}

	/**
	 * @brief Constructs an LRUCache with the specified capacity
	 *
	 * @param capacity Maximum number of items the cache can hold
	 * @note If capacity is less than 1, it will default to 10
	 */
	explicit LRUCache(size_t capacity) : _capacity(capacity) {
		if (this->_capacity == 0) {
			this->_capacity = LRUCache::MIN_CAPACITY;
		}
	}

	~LRUCache() {
		this->clear();
	}

	/**
	 * @brief Removes all items from the cache
	 */
	void clear() {
		_items.clear();
		kvm.clear();
	}

	/**
	 * @brief Checks if a key exists in the cache without affecting its position
	 *
	 * Unlike get(), this method doesn't change the order of items.
	 *
	 * @param key The key to check
	 * @return true if the key exists in the cache, false otherwise
	 */
	inline bool contains(const K &key) const {
		return kvm.find(key) != kvm.end();
	}

	/**
	 * @brief Retrieves a value from the cache
	 *
	 * If the key exists, retrieves its value and moves the key to the front
	 * of the cache (marking it as most recently used).
	 *
	 * @param key The key to look up
	 * @param value Reference where the found value will be stored
	 * @return true if the key was found, false otherwise
	 */
	bool get(const K &key, V &value) {
		auto pos = kvm.find(key);
		if (pos == kvm.end()) {
			return false;
		}

		// Move to front (mark as most recently used)
		_items.erase(pos->second.second);
		_items.push_front(key);
		kvm[key] = {pos->second.first, _items.begin()};

		// Set the output value
		value = pos->second.first;
		return true;
	}

	/**
	 * @brief Checks if the cache is empty
	 *
	 * @return true if the cache contains no items, false otherwise
	 */
	inline bool empty() const {
		return kvm.empty();
	}

	/**
	 * @brief gets the minimum capacity value for the LRU cache
	 * @returns a size_t value that represents the minimum size of a cache
	 */
	inline size_t minCapacity() const {
		return LRUCache::MIN_CAPACITY;
	}

	/**
	 * @brief Sets a key-value pair in the cache
	 *
	 * If the key already exists, its value is updated and the key is moved
	 * to the front of the cache. If the key is new and the cache is at
	 * capacity, the least recently used item is evicted.
	 *
	 * @param key The key to set
	 * @param value The value to associate with the key
	 */
	void set(const K &key, const V &value) {
		auto pos = kvm.find(key);
		if (pos == kvm.end()) {
			// Key doesn't exist - add new item
			_items.push_front(key);
			kvm[key] = {value, _items.begin()};

			// Evict least recently used item if over capacity
			if (size() > _capacity) {
				kvm.erase(_items.back());
				_items.pop_back();
			}
		} else {
			// Key exists - update and move to front
			_items.erase(pos->second.second);
			_items.push_front(key);
			kvm[key] = {value, _items.begin()};
		}
	}

	/**
	 * @brief Returns the current number of items in the cache
	 *
	 * @return The number of items currently stored
	 */
	inline size_t size() const {
		return kvm.size();
	}
};

}  // namespace ds
