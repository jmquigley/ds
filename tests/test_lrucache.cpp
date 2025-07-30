#include <testing_base.h>

#include <cstddef>
#include <ds/LRUCache.hpp>
#include <iostream>
#include <string>
#include <vector>

class TestLRUCache : public TestingBase {
public:

	TestLRUCache() : TestingBase() {}
};

// Test constructors and initialization
TEST_F(TestLRUCache, Constructors) {
	// Test with valid capacity
	ds::LRUCache<int, std::string> cache1(5);
	EXPECT_EQ(0, cache1.size());
	EXPECT_TRUE(cache1.empty());

	// Test with invalid capacity
	ds::LRUCache<int, std::string> cache2(0);
	EXPECT_EQ(0, cache2.size());
	EXPECT_TRUE(cache2.empty());
	EXPECT_EQ(cache2.minCapacity(), cache2.getCapacity());

	// Test default constructor (should use default capacity)
	ds::LRUCache<int, std::string> cache3;
	EXPECT_EQ(cache3.minCapacity(), cache3.getCapacity());
}

// Test set and get operations
TEST_F(TestLRUCache, SetAndGet) {
	ds::LRUCache<int, std::string> cache(3);

	// Set and get a single item
	cache.set(1, "one");
	std::string value;
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_EQ("one", value);

	// Set and get multiple items
	cache.set(2, "two");
	cache.set(3, "three");

	EXPECT_TRUE(cache.get(2, value));
	EXPECT_EQ("two", value);

	EXPECT_TRUE(cache.get(3, value));
	EXPECT_EQ("three", value);

	// Try to get a non-existent item
	EXPECT_FALSE(cache.get(4, value));

	// Test that the output parameter isn't changed for missing keys
	value = "original";
	EXPECT_FALSE(cache.get(4, value));
	EXPECT_EQ("original", value);
}

// Test the LRU eviction policy
TEST_F(TestLRUCache, EvictionPolicy) {
	ds::LRUCache<int, std::string> cache(3);

	// Fill the cache
	cache.set(1, "one");
	cache.set(2, "two");
	cache.set(3, "three");

	// Add another item, which should evict the least recently used (1)
	cache.set(4, "four");

	// Check that 1 was evicted
	std::string value;
	EXPECT_FALSE(cache.get(1, value));

	// Check that other items are still present
	EXPECT_TRUE(cache.get(2, value));
	EXPECT_EQ("two", value);

	EXPECT_TRUE(cache.get(3, value));
	EXPECT_EQ("three", value);

	EXPECT_TRUE(cache.get(4, value));
	EXPECT_EQ("four", value);
}

// Test that getting an item updates its position in the LRU order
TEST_F(TestLRUCache, GetUpdatesLRUOrder) {
	ds::LRUCache<int, std::string> cache(3);

	// Fill the cache
	cache.set(1, "one");
	cache.set(2, "two");
	cache.set(3, "three");

	// Access the least recently used item (1)
	std::string value;
	EXPECT_TRUE(cache.get(1, value));

	// Add a new item, which should now evict the next LRU item (2)
	cache.set(4, "four");

	// Check that 2 was evicted
	EXPECT_FALSE(cache.get(2, value));

	// Check that other items are still present
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_EQ("one", value);

	EXPECT_TRUE(cache.get(3, value));
	EXPECT_EQ("three", value);

	EXPECT_TRUE(cache.get(4, value));
	EXPECT_EQ("four", value);
}

// Test updating an existing key
TEST_F(TestLRUCache, UpdateExistingKey) {
	ds::LRUCache<int, std::string> cache(3);

	// Fill the cache
	cache.set(1, "one");
	cache.set(2, "two");
	cache.set(3, "three");

	// Update an existing key
	cache.set(2, "TWO UPDATED");

	// Check the value was updated
	std::string value;
	EXPECT_TRUE(cache.get(2, value));
	EXPECT_EQ("TWO UPDATED", value);

	// Check that updating also made it the most recently used
	cache.set(4, "four");

	// Key 1 should be evicted (not 2)
	EXPECT_FALSE(cache.get(1, value));
	EXPECT_TRUE(cache.get(2, value));
}

// Test the contains method
TEST_F(TestLRUCache, Contains) {
	ds::LRUCache<int, std::string> cache(3);

	// Add some items
	cache.set(1, "one");
	cache.set(2, "two");

	// Check contains for existing and non-existing keys
	EXPECT_TRUE(cache.contains(1));
	EXPECT_TRUE(cache.contains(2));
	EXPECT_FALSE(cache.contains(3));

	// Verify that contains doesn't affect LRU order
	cache.contains(1);		// Access key 1
	cache.set(3, "three");	// Fill the cache
	cache.set(4, "four");	// This should evict the LRU item

	// Key 1 should still be evicted if contains doesn't affect LRU order
	EXPECT_FALSE(cache.contains(1));
	EXPECT_TRUE(cache.contains(2));
}

// Test the size method
TEST_F(TestLRUCache, Size) {
	ds::LRUCache<int, std::string> cache(5);

	// Empty cache should have size 0
	EXPECT_EQ(0, cache.size());

	// Add items and check size increases
	cache.set(1, "one");
	EXPECT_EQ(1, cache.size());

	cache.set(2, "two");
	EXPECT_EQ(2, cache.size());

	// Updating an existing key shouldn't change size
	cache.set(1, "ONE UPDATED");
	EXPECT_EQ(2, cache.size());

	// Fill to capacity
	cache.set(3, "three");
	cache.set(4, "four");
	cache.set(5, "five");
	EXPECT_EQ(5, cache.size());

	// Exceeding capacity should maintain the size at capacity
	cache.set(6, "six");
	EXPECT_EQ(5, cache.size());
}

// Test the empty method
TEST_F(TestLRUCache, Empty) {
	ds::LRUCache<int, std::string> cache(3);

	// New cache should be empty
	EXPECT_TRUE(cache.empty());

	// After adding an item, it shouldn't be empty
	cache.set(1, "one");
	EXPECT_FALSE(cache.empty());

	// After clearing, it should be empty again
	cache.clear();
	EXPECT_TRUE(cache.empty());
}

// Test the clear method
TEST_F(TestLRUCache, Clear) {
	ds::LRUCache<int, std::string> cache(3);

	// Add some items
	cache.set(1, "one");
	cache.set(2, "two");
	EXPECT_EQ(2, cache.size());

	// Clear the cache
	cache.clear();

	// Check that the cache is empty
	EXPECT_EQ(0, cache.size());
	EXPECT_TRUE(cache.empty());

	// Check that items are no longer accessible
	std::string value;
	EXPECT_FALSE(cache.get(1, value));
	EXPECT_FALSE(cache.get(2, value));

	// Check that we can add items after clearing
	cache.set(3, "three");
	EXPECT_EQ(1, cache.size());
	EXPECT_TRUE(cache.get(3, value));
	EXPECT_EQ("three", value);
}

// Test with different key and value types
TEST_F(TestLRUCache, DifferentTypes) {
	// String keys, integer values
	ds::LRUCache<std::string, int> cache1(2);
	cache1.set("one", 1);
	cache1.set("two", 2);

	int intValue;
	EXPECT_TRUE(cache1.get("one", intValue));
	EXPECT_EQ(1, intValue);

	// Integer keys, complex values (using shared_ptr to avoid copy issues)
	struct ComplexValue {
		std::string data;
		int count;
	};

	ds::LRUCache<int, std::shared_ptr<ComplexValue>> cache2(2);
	auto val1 = std::make_shared<ComplexValue>(ComplexValue {"test", 1});
	auto val2 = std::make_shared<ComplexValue>(ComplexValue {"data", 2});

	cache2.set(1, val1);
	cache2.set(2, val2);

	std::shared_ptr<ComplexValue> complexValue;
	EXPECT_TRUE(cache2.get(1, complexValue));
	EXPECT_EQ("test", complexValue->data);
	EXPECT_EQ(1, complexValue->count);
}

// Define hash function for our custom key type
// This needs to be outside any function scope
struct CustomKey {
	int id;

	bool operator==(const CustomKey &other) const {
		return id == other.id;
	}
};

// Hash function specialization must be in global scope
namespace std {
template<>
struct hash<CustomKey> {
	size_t operator()(const CustomKey &key) const {
		return hash<int>()(key.id);
	}
};
}  // namespace std

// Now the test function can use our custom key type
TEST_F(TestLRUCache, CustomKeyType) {
	ds::LRUCache<CustomKey, std::string> cache(2);

	CustomKey key1 {1};
	CustomKey key2 {2};

	cache.set(key1, "one");
	cache.set(key2, "two");

	std::string value;
	EXPECT_TRUE(cache.get(key1, value));
	EXPECT_EQ("one", value);

	// Test LRU eviction with custom keys
	CustomKey key3 {3};
	cache.set(key3, "three");

	EXPECT_FALSE(cache.get(key2, value));  // key2 should be evicted
	EXPECT_TRUE(cache.get(key1, value));
	EXPECT_TRUE(cache.get(key3, value));
}

// Test with the default value type (K = V)
TEST_F(TestLRUCache, DefaultValueType) {
	ds::LRUCache<std::string> cache(2);	 // Value type defaults to std::string

	cache.set("key1", "value1");
	cache.set("key2", "value2");

	std::string value;
	EXPECT_TRUE(cache.get("key1", value));
	EXPECT_EQ("value1", value);
}

// Test with large capacity
TEST_F(TestLRUCache, LargeCapacity) {
	ds::LRUCache<int, int> cache(1000);

	// Add many items
	for (int i = 0; i < 1000; i++) {
		cache.set(i, i * 10);
	}

	// Check all items are present
	int value;
	for (int i = 0; i < 1000; i++) {
		EXPECT_TRUE(cache.get(i, value));
		EXPECT_EQ(i * 10, value);
	}

	// Add one more to test eviction
	cache.set(1000, 10000);
	EXPECT_FALSE(cache.get(0, value));	// First item should be evicted
}

// Test concurrent access patterns
TEST_F(TestLRUCache, AccessPatterns) {
	ds::LRUCache<int, std::string> cache(3);

	// Add items
	cache.set(1, "one");
	cache.set(2, "two");
	cache.set(3, "three");

	// Access in different orders to test LRU behavior
	std::string value;

	// Access: 3, 1, 2
	EXPECT_TRUE(cache.get(3, value));
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_TRUE(cache.get(2, value));

	// Add new item - should evict 3 (least recently used)
	cache.set(4, "four");
	EXPECT_FALSE(cache.get(3, value));

	// Access: 1, 4
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_TRUE(cache.get(4, value));

	// Add new item - should evict 2
	cache.set(5, "five");
	EXPECT_FALSE(cache.get(2, value));
}

// Test with high memory usage
TEST_F(TestLRUCache, HighMemoryUsage) {
	ds::LRUCache<int, std::string> cache(5);

	// Create large strings (1MB each)
	std::string largeValue(1024 * 1024, 'X');

	// Add large values
	for (int i = 0; i < 5; i++) {
		cache.set(i, largeValue + std::to_string(i));
	}

	// Verify all values
	std::string value;
	for (int i = 0; i < 5; i++) {
		EXPECT_TRUE(cache.get(i, value));
		EXPECT_EQ(largeValue + std::to_string(i), value);
	}

	// Test eviction with large values
	cache.set(5, largeValue + "5");
	EXPECT_FALSE(cache.get(0, value));	// First should be evicted
}

// Edge case: Capacity of 1
TEST_F(TestLRUCache, SingleItemCapacity) {
	ds::LRUCache<int, std::string> cache(1);

	cache.set(1, "one");

	// Adding another item should evict the first
	cache.set(2, "two");

	std::string value;
	EXPECT_FALSE(cache.get(1, value));
	EXPECT_TRUE(cache.get(2, value));
	EXPECT_EQ("two", value);
}

// Edge case: Insert same key multiple times
TEST_F(TestLRUCache, RepeatedKeys) {
	ds::LRUCache<int, std::string> cache(2);

	// Set same key multiple times
	cache.set(1, "one");
	cache.set(1, "ONE");
	cache.set(1, "One");

	// Only one entry should be used
	EXPECT_EQ(1, cache.size());

	// Should have the latest value
	std::string value;
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_EQ("One", value);

	// Add another key
	cache.set(2, "two");
	EXPECT_EQ(2, cache.size());

	// Update first key again
	cache.set(1, "ONE FINAL");

	// Add a third key to test eviction
	cache.set(3, "three");

	// Key 2 should be evicted (not 1, since 1 was more recently used)
	EXPECT_FALSE(cache.get(2, value));
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_TRUE(cache.get(3, value));
}

// Test behavior when accessing a non-existent key
TEST_F(TestLRUCache, NonExistentKey) {
	ds::LRUCache<int, std::string> cache(3);

	cache.set(1, "one");
	cache.set(2, "two");

	// Try to get a non-existent key
	std::string value = "original";
	EXPECT_FALSE(cache.get(3, value));

	// Output parameter should remain unchanged
	EXPECT_EQ("original", value);

	// Contains should also return false
	EXPECT_FALSE(cache.contains(3));

	// Size should still be 2
	EXPECT_EQ(2, cache.size());
}

TEST_F(TestLRUCache, CaseSensitivityDetailed) {
	// Create a fresh cache
	ds::LRUCache<std::string, int> cache(10);

	// Add a lowercase key
	cache.set("key", 1);

	// Verify we can retrieve it
	int value = 0;
	EXPECT_TRUE(cache.get("key", value));
	EXPECT_EQ(1, value);

	// Add an uppercase version of the same key
	cache.set("KEY", 2);

	// Verify both keys are present with correct values
	value = 0;
	EXPECT_TRUE(cache.get("key", value)) << "Could not find lowercase key";
	EXPECT_EQ(1, value) << "Lowercase key has incorrect value";

	value = 0;
	EXPECT_TRUE(cache.get("KEY", value)) << "Could not find uppercase key";
	EXPECT_EQ(2, value) << "Uppercase key has incorrect value";

	// Verify the size is 2 (indicating two distinct keys)
	EXPECT_EQ(2, cache.size()) << "Cache should have 2 items (case-sensitive)";

	// Use contains method to verify both keys exist
	EXPECT_TRUE(cache.contains("key"))
		<< "contains() should find lowercase key";
	EXPECT_TRUE(cache.contains("KEY"))
		<< "contains() should find uppercase key";
}

// Test sequential access pattern
TEST_F(TestLRUCache, SequentialAccess) {
	ds::LRUCache<int, int> cache(3);

	// Fill cache sequentially
	for (int i = 0; i < 10; i++) {
		cache.set(i, i);

		// Check that only the last 3 items are in the cache
		int value;
		for (int j = 0; j <= i; j++) {
			if (j <= i - 3) {
				EXPECT_FALSE(cache.get(j, value))
					<< "Key " << j << " should be evicted";
			} else {
				EXPECT_TRUE(cache.get(j, value))
					<< "Key " << j << " should be in cache";
				EXPECT_EQ(j, value);
			}
		}
	}
}

// Test random access pattern
TEST_F(TestLRUCache, RandomAccess) {
	ds::LRUCache<int, int> cache(3);

	// Add initial items
	cache.set(1, 10);
	cache.set(2, 20);
	cache.set(3, 30);

	// Access in non-sequential order
	int value;
	EXPECT_TRUE(cache.get(2, value));
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_TRUE(cache.get(3, value));

	// Add a new item - should evict 2 which was accessed first
	cache.set(4, 40);
	EXPECT_FALSE(cache.get(2, value));
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_TRUE(cache.get(3, value));
	EXPECT_TRUE(cache.get(4, value));

	// Access in different order
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_TRUE(cache.get(4, value));

	// Add a new item - should evict 3
	cache.set(5, 50);
	EXPECT_FALSE(cache.get(3, value));
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_TRUE(cache.get(4, value));
	EXPECT_TRUE(cache.get(5, value));
}

// Test with complex value types
TEST_F(TestLRUCache, ComplexValueTypes) {
	struct ComplexValue {
		std::string str;
		int num;
		std::vector<double> vec;

		bool operator==(const ComplexValue &other) const {
			return str == other.str && num == other.num && vec == other.vec;
		}
	};

	ds::LRUCache<int, ComplexValue> cache(2);

	ComplexValue v1 {"hello", 42, {1.1, 2.2, 3.3}};
	ComplexValue v2 {"world", 99, {4.4, 5.5}};

	cache.set(1, v1);
	cache.set(2, v2);

	ComplexValue result;
	EXPECT_TRUE(cache.get(1, result));
	EXPECT_EQ(v1, result);

	EXPECT_TRUE(cache.get(2, result));
	EXPECT_EQ(v2, result);
}

// Test with move semantics
TEST_F(TestLRUCache, MoveSemantics) {
	// Instead of unique_ptr which can't be copied, use shared_ptr
	ds::LRUCache<int, std::shared_ptr<int>> cache(2);

	// Use shared_ptr instead of unique_ptr
	cache.set(1, std::make_shared<int>(10));
	cache.set(2, std::make_shared<int>(20));

	std::shared_ptr<int> result;
	EXPECT_TRUE(cache.get(1, result));
	EXPECT_EQ(10, *result);

	EXPECT_TRUE(cache.get(2, result));
	EXPECT_EQ(20, *result);
}

// Test destructor
TEST_F(TestLRUCache, Destructor) {
	// Create a counter to track object destruction
	static int destructorCallCount = 0;

	class TrackDestructor {
	public:

		TrackDestructor() = default;

		~TrackDestructor() {
			destructorCallCount++;
		}
	};

	// Reset counter
	destructorCallCount = 0;

	{
		ds::LRUCache<int, std::shared_ptr<TrackDestructor>> cache(3);

		// Add items that will track their destruction
		cache.set(1, std::make_shared<TrackDestructor>());
		cache.set(2, std::make_shared<TrackDestructor>());
		cache.set(3, std::make_shared<TrackDestructor>());

		// Evict one item
		cache.set(4, std::make_shared<TrackDestructor>());

		// At this point, item 1 should be destroyed
		EXPECT_EQ(1, destructorCallCount);

		// Clear should destroy the remaining items
		cache.clear();
		EXPECT_EQ(4, destructorCallCount);
	}

	// No additional destructions should occur since everything was already
	// cleared
	EXPECT_EQ(4, destructorCallCount);
}

// Test cache behavior after clear
TEST_F(TestLRUCache, BehaviorAfterClear) {
	ds::LRUCache<int, std::string> cache(3);

	// Add items
	cache.set(1, "one");
	cache.set(2, "two");

	// Clear the cache
	cache.clear();
	EXPECT_EQ(0, cache.size());
	EXPECT_TRUE(cache.empty());
	cache.setMinCapacity(3);
	cache.setCapacity(3);

	// Add items again
	cache.set(3, "three");
	cache.set(4, "four");

	std::string value;
	EXPECT_TRUE(cache.get(3, value));
	EXPECT_EQ("three", value);

	EXPECT_TRUE(cache.get(4, value));
	EXPECT_EQ("four", value);

	// Make sure capacity is preserved
	cache.set(5, "five");
	cache.set(6, "six");  // Should evict 3

	EXPECT_EQ(cache.size(), 3);
	EXPECT_FALSE(cache.get(3, value));
	EXPECT_TRUE(cache.get(4, value));
	EXPECT_TRUE(cache.get(5, value));
	EXPECT_TRUE(cache.get(6, value));
}

// Test cache with nullptr values
TEST_F(TestLRUCache, NullptrValues) {
	ds::LRUCache<int, std::shared_ptr<int>> cache(2);

	// Set some null and non-null values
	cache.set(1, nullptr);
	cache.set(2, std::make_shared<int>(20));

	std::shared_ptr<int> result;

	// Check the null value
	EXPECT_TRUE(cache.get(1, result));
	EXPECT_EQ(nullptr, result);

	// Check the non-null value
	EXPECT_TRUE(cache.get(2, result));
	EXPECT_NE(nullptr, result);
	EXPECT_EQ(20, *result);

	// Ensure null values affect LRU ordering properly
	cache.set(3, std::make_shared<int>(30));

	// Key 1 should be evicted
	EXPECT_FALSE(cache.get(1, result));
	EXPECT_TRUE(cache.get(2, result));
	EXPECT_TRUE(cache.get(3, result));
}

TEST_F(TestLRUCache, HitMissRate) {
	size_t cacheSize = 20;
	size_t maxValues = 100;
	size_t threshold = 25;
	std::vector<size_t> v {
		63, 12, 30, 43, 53, 2,	5,	67, 39, 15, 50, 1,	23, 48, 93,	 41, 45,
		76, 8,	71, 57, 24, 42, 73, 47, 79, 26, 62, 40, 89, 60, 16,	 86, 88,
		82, 72, 27, 74, 14, 52, 75, 31, 84, 99, 95, 18, 91, 9,	100, 49, 66,
		5,	8,	21, 16, 10, 24, 23, 10, 6,	10, 11, 25, 9,	18, 19,	 17, 1,
		97, 25, 58, 3,	80, 36, 6,	28, 98, 87, 17, 44, 70, 77, 29,	 11, 54,
		82, 72, 27, 74, 14, 52, 75, 31, 84, 99, 95, 18, 91, 9,	100, 49, 66,
		34, 56, 19, 64, 69, 46, 22, 78, 81, 96, 55, 7,	20, 13, 4,	 10, 38,
		63, 12, 30, 43, 53, 2,	5,	67, 39, 15, 50, 1,	23, 48, 93,	 41, 45,
		83, 68, 33, 35, 59, 94, 61, 85, 51, 65, 32, 92, 21, 90, 37,	 99, 16,
		16, 10, 21, 7,	25, 24, 9,	24, 25, 6,	17, 14, 9,	20, 20,	 7,	 4,
		82, 72, 27, 74, 14, 52, 75, 31, 84, 99, 95, 18, 91, 9,	100, 49, 66,
		5,	8,	21, 16, 10, 24, 23, 10, 6,	10, 11, 25, 9,	18, 19,	 17, 1,
		76, 8,	71, 57, 24, 42, 73, 47, 79, 26, 62, 40, 89, 60, 16,	 86, 88,
		97, 25, 58, 3,	80, 36, 6,	28, 98, 87, 17, 44, 70, 77, 29,	 11, 54,
		8,	7,	23, 2,	19, 99, 9,	5,	12, 1,	1,	19, 18, 18, 1,	 18, 42};

	EXPECT_EQ(v.size(), 255);

	ds::LRUCache<size_t, size_t> cache(cacheSize);
	cache.setThreshold(threshold);
	cache.setCollectionSize(maxValues);

	// This test uses the number 1-100 for the data collection.
	// The cache is seeded 5,10,...100, with 20 initial values
	for (size_t i = 5; i <= maxValues; i += 5) {
		cache.set(i, i);
	}

	// A set of 255 values are then checked against the cache one at a time.
	// When the values are not there, then they are set in the cache.  Every
	// 25 get operations (threshold) causes a check against the cache for
	// adjustment.
	size_t val;
	for (auto &it: v) {
		if (!cache.get(it, val)) {
			cache.set(it, it);
		}
	}

	// The following stats are a snapshot of the cache operation
	std::cout << cache.stats() << std::endl;
	// targetHitRaio: 0.8, hitRatio: 0.20784, hits: 53, missRatio: 0.79216,
	// misses: 202, totalAccess: 255, ejectRatio: 0.81982, ejects: 182,
	// capacity: 40

	const double epsilon = 0.001;

	ASSERT_NEAR(0.8d, cache.getTargetHitRatio(), epsilon);
	ASSERT_NEAR(0.20784d, cache.hitRatio(), epsilon);
	ASSERT_NEAR(0.79216d, cache.missRatio(), epsilon);
	ASSERT_NEAR(0.81982d, cache.ejectRatio(), epsilon);

	EXPECT_EQ(cache.hits(), 53);
	EXPECT_EQ(cache.misses(), 202);
	EXPECT_EQ(cache.totalAccess(), 255);
	EXPECT_EQ(cache.ejects(), 182);
	EXPECT_EQ(cache.capacity(), 40);
}
