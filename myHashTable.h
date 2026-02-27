#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include <list>
#include <vector>

template <typename K, typename V> class MyHashTable {
private:
  struct HashNode {
    K key;
    V value;
    HashNode(K k, V v) : key(k), value(v) {}
  };
  std::vector<std::list<HashNode>> buckets;

public:
  MyHashTable() : buckets(101) {};

  V get(K key) const;
  bool insert(K key, V v);
  bool contains(K key);
  bool remove(K key, V v);
};

// Implementation for MyHashTable class

template <typename K, typename V> V MyHashTable<K, V>::get(K key) const {
  const std::list<HashNode> &bucket =
      buckets[std::hash<K>{}(key) % buckets.size()];
  for (const auto &node : bucket) {
    if (node.key == key) {
      return node.value;
    }
  }
  throw std::runtime_error("Key not found");
}

template <typename K, typename V> bool MyHashTable<K, V>::insert(K key, V v) {
  std::list<HashNode> &bucket = buckets[std::hash<K>{}(key) % buckets.size()];
  for (const auto &node : bucket) {
    if (node.key == key) {
      return false;
    }
  }
  bucket.emplace_back(key, v);
  return true;
}

template <typename K, typename V> bool MyHashTable<K, V>::contains(K key) {
  const std::list<HashNode> &bucket =
      buckets[std::hash<K>{}(key) % buckets.size()];
  for (const auto &node : bucket) {
    if (node.key == key) {
      return true;
    }
  }
  return false;
}

template <typename K, typename V> bool MyHashTable<K, V>::remove(K key, V v) {
  std::list<HashNode> &bucket = buckets[std::hash<K>{}(key) % buckets.size()];
  for (auto it = bucket.begin(); it != bucket.end(); ++it) {
    if (it->key == key && it->value == v) {
      bucket.erase(it);
      return true;
    }
  }
  return false;
}

#endif