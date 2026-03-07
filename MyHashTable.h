#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include <algorithm>
#include <functional>
#include <list>
#include <stdexcept>
#include <vector>

/*
Generic hash table implementation.

This template class stores key-value pairs using a vector
of linked lists. Supports basic operations:
- insert
- get
- contains
- remove
- values

Used throughout the movie store system for efficient lookups.
*/
template <typename K, typename V> class MyHashTable {
private:
  /**
   * Internal structure to represent a key-value pair in the hash table.
   */
  struct HashNode {
    K key;
    V value;
    HashNode(K k, V v) : key(k), value(v) {}
  };
  // Vector of buckets, each bucket is a linked list
  std::vector<std::list<HashNode>> buckets;

public:
  /**
   * Constructor initializes the hash table with a default number of buckets
   * (101).
   */
  MyHashTable() : buckets(101) {};

  // Returns the value associated with the key
  V get(const K &key) const;

  // Returns a reference to the value associated with the key, allowing
  // modification
  V &get(const K &key);

  // Inserts a key-value pair into the hash table. Returns false if the key
  // already exists.
  bool insert(const K &key, V v);

  // Checks if the key exists in the hash table.
  bool contains(const K &key) const;

  // Removes the key-value pair associated with the key. Returns true if
  // removed, false if not found.
  bool remove(const K &key, V v);

  // Returns a vector of all values stored in the hash table.
  std::vector<V> values() const;
};

// Implementation of MyHashTable methods

/**
 * Retrieves the value associated with the given key
 */
template <typename K, typename V> V MyHashTable<K, V>::get(const K &key) const {
  const std::list<HashNode> &bucket =
      buckets[std::hash<K>{}(key) % buckets.size()];
  for (const auto &node : bucket) {
    if (node.key == key) {
      return node.value;
    }
  }
  throw std::runtime_error("Key not found");
}

// Retrieves a reference to the value associated with the given key, allowing
// modifications
template <typename K, typename V> V &MyHashTable<K, V>::get(const K &key) {
  std::list<HashNode> &bucket = buckets[std::hash<K>{}(key) % buckets.size()];
  for (auto &node : bucket) {
    if (node.key == key) {
      return node.value;
    }
  }
  throw std::runtime_error("Key not found");
}

// Inserts a key-value pair into the hash table. Returns false if the key
// already exists.
template <typename K, typename V>
bool MyHashTable<K, V>::insert(const K &key, V v) {
  std::list<HashNode> &bucket = buckets[std::hash<K>{}(key) % buckets.size()];
  if (std::any_of(bucket.begin(), bucket.end(),
                  [&](const HashNode &node) { return node.key == key; })) {
    return false;
  }
  bucket.emplace_back(key, v);
  return true;
}

// Checks if the key exists in the hash table.
template <typename K, typename V>
bool MyHashTable<K, V>::contains(const K &key) const {
  const std::list<HashNode> &bucket =
      buckets[std::hash<K>{}(key) % buckets.size()];
  return std::any_of(bucket.begin(), bucket.end(),
                     [&](const HashNode &node) { return node.key == key; });
}

// Removes the key-value pair associated with the key. Returns true if removed,
// false if not found.
template <typename K, typename V>
bool MyHashTable<K, V>::remove(const K &key, V v) {
  std::list<HashNode> &bucket = buckets[std::hash<K>{}(key) % buckets.size()];
  for (auto it = bucket.begin(); it != bucket.end(); ++it) {
    if (it->key == key) {
      bucket.erase(it);
      return true;
    }
  }
  return false;
}

// Returns a vector of all values stored in the hash table.
template <typename K, typename V>
std::vector<V> MyHashTable<K, V>::values() const {
  std::vector<V> result;
  for (const auto &bucket : buckets) {
    for (const auto &node : bucket) {
      result.push_back(node.value);
    }
  }
  return result;
}

#endif