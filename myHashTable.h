#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include <vector>

template <typename K, typename V>
class MyHashTable {
private:
  struct HashNode {
    K key;
    V value;
    HashNode(K k, V v) : key(k), value(v) {}
  };
  std::vector<HashNode> hashMap;

  public:
    V get(K key) const;
    bool insert(K key, V v);
    bool remove(K key, V v);
    bool contains(K key);
};

#endif