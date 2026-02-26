#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

template <typename K, typename V>
class MyHashTable {
private:
  struct HashNode {
    K key;
    V value;
    HashNode(K k, V v) : key(k), value(v) {}
  };
  HashNode next;

  public:
    V get(K key);
};

#endif