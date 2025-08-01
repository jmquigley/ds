#pragma once

#include <algorithm>
#include <cstddef>
#include <ds/property.hpp>
#include <iomanip>
#include <limits>
#include <list>
#include <sstream>
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
 *
 *
 * NOTE: if a custom object is used as the key, then a special hash object must
 * be created to handle hashing the values so they can be compared.  e.g.
 *
 * @code{.cpp}
 * template<>
 * struct hash<ds::Path> {
 * 	size_t operator()(const ds::Path &path) const {
 * 		return hash<std::string>()(path.path());
 * 	}
 * };
 * }
 * @endcode
 *
 * TODO: Add callback mechanisms for significant operations (evictions, capacity
 * changes)
 */
template<typename K, typename V = K>
class LRUCache final {
	/// @brief The maximum number of items the cache can currently hold
	PROPERTY_WITH_DEFAULT(capacity, Capacity, size_t, {LRUCache::MIN_CAPACITY});

	/// @brief The size of the collection that the LRUCache is using, updated
	/// by the object.
	PROPERTY_WITH_DEFAULT(collectionSize, CollectionSize, size_t, {});

	/// @brief The rate to decrease capacity when the hit rate is too high
	PROPERTY_WITH_DEFAULT(decreaseFactor, DecreaseFactor, double, {0.9});

	/// @brief The number of keys that are ejected from the cache
	PROPERTY_WITH_DEFAULT(ejects, Ejects, size_t, {});

	/// @brief The number of cache access requests history
	PROPERTY_READONLY_WITH_DEFAULT(hits, Hits, size_t, {});

	/// @brief The rate to increase capacity when hit ratio is too low
	PROPERTY_WITH_DEFAULT(increaseFactor, IncreaseFactor, double, {1.2});

	/// @brief List maintaining the order of keys from most to least recently
	/// used
	PROPERTY(items, Items, std::list<K>);

	/// @brief The cache must have at least N values available
	PROPERTY_WITH_DEFAULT(minCapacity, MinCapacity, size_t,
						  {LRUCache::MIN_CAPACITY});

	/// @brief The lowest allowable percentage of total capacity
	PROPERTY_WITH_DEFAULT(minPercentage, MinPercentage, double, {0.05});

	/// @brief The upper limit on how large the capacity can grow
	PROPERTY_WITH_DEFAULT(maxCapacity, MaxCapacity, size_t,
						  {LRUCache::MAX_CAPACITY});

	/// @brief The higest allowable percentage of total capacity
	PROPERTY_WITH_DEFAULT(maxPercentage, MaxPercentage, double, {0.40});

	/// @brief The number of cache requests that miss
	PROPERTY_READONLY_WITH_DEFAULT(misses, Misses, size_t, {});

	/// @brief A percentage +/- of the hit ratio to facilitate movement
	PROPERTY_WITH_DEFAULT(noise, Noise, double, {0.05});

	/// @brief the percetage level for cache hits we are trying to achieve
	PROPERTY_WITH_DEFAULT(targetHitRatio, TargetHitRatio, double, {0.8});

	/// @brief The number of cache access requests before the capacity size is
	/// re-evaluated
	PROPERTY_WITH_DEFAULT(threshold, Threshold, size_t, {1000});

	/// @brief The total number of access requests
	PROPERTY_READONLY_WITH_DEFAULT(totalAccess, TotalAccess, size_t, {});

	/// @brief the total number of set operations
	PROPERTY_READONLY_WITH_DEFAULT(totalSets, TotalSets, size_t, {});

private:

	/** Map from keys to their values and positions in the items list */
	std::unordered_map<K, std::pair<V, typename std::list<K>::iterator>> kvm;

	/**
	 * @brief after N cache lookups uses cache statistics to dynamically resize
	 * the LRU cache.
	 */
	void updateCapacity() {
		if (_totalAccess % _threshold != 0) {
			return;
		}

		size_t newCapacity {};
		double currentHitRatio = this->hitRatio();

		if (currentHitRatio < _targetHitRatio - _noise) {
			newCapacity = static_cast<size_t>(_capacity * _increaseFactor);
		} else if (currentHitRatio > _targetHitRatio + _noise) {
			newCapacity = static_cast<size_t>(_capacity * _decreaseFactor);
		} else {
			return;
		}

		size_t minSize = static_cast<size_t>(_collectionSize * _minPercentage);
		size_t maxSize = static_cast<size_t>(_collectionSize * _maxPercentage);

		newCapacity = std::clamp(newCapacity, std::max(minSize, _minCapacity),
								 std::min(maxSize, _maxCapacity));

		resizeCache(newCapacity);
	}

	/**
	 * @brief Changes the size of the current map/list for the cache
	 *
	 * If the cache grows in size, then the capacity is just changed to
	 * that new size.  If the capacity shrinks, then the oldest items are
	 * ejected from the cache until it hits the new capacity size.
	 *
	 * @param newCapacity (`size_t`) the computed new size for the capacity
	 */
	void resizeCache(size_t newCapacity) {
		if (newCapacity == _capacity) {
			return;
		}

		_capacity = newCapacity;

		while (kvm.size() > _capacity) {
			auto last = _items.end();
			--last;
			this->eject(*last);
		}
	}

public:

	/// @brief If the capacity given is 0, then set it to this value to ensure
	/// that the cache has space to store values
	inline static const size_t MIN_CAPACITY {100};

	/// @brief the maximum entries that can be added to the LRU cache
	inline static const size_t MAX_CAPACITY {
		std::numeric_limits<std::size_t>::max()};

	LRUCache() {
		this->clear();
	}

	/**
	 * @brief Constructs an LRUCache with the specified capacity
	 *
	 * @param initialCapacity Maximum number of items the cache can hold
	 * @note If capacity is less than 1, it will default to 10
	 */
	LRUCache(size_t initialCapacity) : LRUCache() {
		this->_capacity = initialCapacity;
		if (this->_capacity == 0) {
			this->_capacity = LRUCache::MIN_CAPACITY;
		}
	}

	~LRUCache() {
		this->clear();
	}

	/**
	 * @brief Removes all items from the cache and resets all of the base
	 * statistics to their built in defaults.
	 */
	void clear() {
		this->_capacity = this->_minCapacity = LRUCache::MIN_CAPACITY;
		this->_collectionSize = 0;
		this->_decreaseFactor = 0.9;
		this->_ejects = 0;
		this->_hits = 0;
		this->_increaseFactor = 1.2;
		this->_minPercentage = 0.05;
		this->_maxCapacity = LRUCache::MAX_CAPACITY;
		this->_maxPercentage = 0.40;
		this->_misses = 0;
		this->_noise = 0.05;
		this->_targetHitRatio = 0.8;
		this->_threshold = 1000;
		this->_totalAccess = 0;
		this->_totalSets = 0;

		_items.clear();
		kvm.clear();
	}

	/**
	 * @brief Checks if a key exists in the cache without affecting its
	 * position
	 *
	 * Unlike get(), this method doesn't change the order of items or impact
	 * the dynamic capacity sizing.
	 *
	 * @param key The key to check
	 * @return true if the key exists in the cache, false otherwise
	 */
	inline bool contains(const K &key) const {
		return kvm.find(key) != kvm.end();
	}

	/**
	 * @brief Removes a specific key from the cache
	 *
	 * This method allows for manual removal of an item from the cache
	 * regardless of its LRU position.
	 *
	 * @param key The key to remove from the cache
	 * @return true if the key was found and removed, false if the key wasn't in
	 * the cache
	 *
	 * @par Example:
	 * @code{.cpp}
	 * ds::LRUCache<int, std::string> cache(10);
	 * cache.set(1, "one");
	 * cache.set(2, "two");
	 *
	 * // Remove a specific key
	 * bool removed = cache.eject(1);  // Returns true
	 *
	 * // Key 1 is no longer in the cache
	 * std::string value;
	 * cache.get(1, value);  // Returns false
	 *
	 * // Try to remove a non-existent key
	 * removed = cache.eject(3);  // Returns false
	 * @endcode
	 */
	bool eject(const K &key) {
		auto pos = kvm.find(key);
		if (pos == kvm.end()) {
			// Key doesn't exist in cache
			return false;
		}

		// Remove from the LRU list and map
		_items.erase(pos->second.second);
		kvm.erase(pos);

		return true;
	}

	/**
	 * @brief computes the percentage on how often the cache entry is removed
	 * @returns a percentage that represents how often a value is removed
	 * from the cache.
	 */
	double ejectRatio() {
		if (this->_totalSets > 0) {
			return static_cast<double>(this->_ejects) /
				   static_cast<double>(this->_totalSets);
		} else {
			return 0.0;
		}
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
		this->_totalAccess++;

		auto pos = kvm.find(key);
		if (pos == kvm.end()) {
			this->_misses++;
			updateCapacity();
			return false;
		}

		// Move to front (mark as most recently used)
		_items.erase(pos->second.second);
		_items.push_front(key);
		kvm[key] = {pos->second.first, _items.begin()};

		// Set the output value
		value = pos->second.first;
		this->_hits++;
		updateCapacity();
		return true;
	}

	/**
	 * @brief computes the percentage on how often the cache is accessed
	 * @returns a percentage that represents how often a value is accessed
	 * in the cache.
	 */
	double hitRatio() const {
		if (this->_totalAccess > 0) {
			return static_cast<double>(this->_hits) /
				   static_cast<double>(this->_totalAccess);
		} else {
			return 0.0;
		}
	}

	/**
	 * @brief computes the percentage on how often the cache is missed
	 * @returns a percentage that represents how often a value is missed
	 * in the cache.
	 */
	double missRatio() const {
		if (this->_totalAccess > 0) {
			return static_cast<double>(this->_misses) /
				   static_cast<double>(this->_totalAccess);
		} else {
			return 0.0;
		}
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
			_totalSets++;
			// Key doesn't exist - add new item
			_items.push_front(key);
			kvm[key] = {value, _items.begin()};

			// Evict least recently used item if over capacity
			if (size() > _capacity) {
				kvm.erase(_items.back());
				_items.pop_back();
				_ejects++;
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

	/**
	 * @brief create a string that holds all relevant informaiton for the
	 * cache.
	 *
	 * The purpose of this function is to provide debugging information
	 * for the caller programs.  It uses a csv format.
	 *
	 * @returns a `std::string` that contains debugging information about the
	 * current state of the cache.
	 */
	std::string stats() {
		std::string sep = ", ";
		std::stringstream ss;

		ss << std::setprecision(5) << "targetHitRaio: " << _targetHitRatio
		   << sep << "hitRatio: " << hitRatio() << sep
		   << "hits: " << this->_hits << sep << "missRatio: " << missRatio()
		   << sep << "misses: " << this->_misses << sep
		   << "totalAccess: " << this->_totalAccess << sep
		   << "ejectRatio: " << this->ejectRatio() << sep
		   << "ejects: " << this->_ejects << sep
		   << "capacity: " << this->_capacity;

		return ss.str();
	}
};

}  // namespace ds
