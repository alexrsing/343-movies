// Implementation file for MyHashTable class

#include "myHashTable.h"

template <typename K, typename V> V MyHashTable<K, V>::get(K key) const {
  for (const auto &node : hashMap) {
    if (node.key == key) {
      return node.value;
    }
  }
  throw std::runtime_error("Key not found");
}

template <typename K, typename V> bool MyHashTable<K, V>::insert(K key, V v) {
  for (const auto &node : hashMap) {
    if (node.key == key) {
      return false; // Key already exists
    }
  }
  hashMap.emplace_back(key, v);
  return true;
}

template <typename K, typename V> bool MyHashTable<K, V>::remove(K key, V v) {
  for (auto it = hashMap.begin(); it != hashMap.end(); ++it) {
    if (it->key == key && it->value == v) {
      hashMap.erase(it);
      return true;
    }
  }
  return false; // Key-value pair not found
}

template <typename K, typename V> bool MyHashTable<K, V>::contains(K key) {
  for (const auto &node : hashMap) {
    if (node.key == key) {
      return true;
    }
  }
  return false; // Key not found
}
