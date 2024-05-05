#pragma once
#include <vector>
#include <iostream>

template<typename Key, typename Value>
class HashTable {
    struct Pair {
        Key key;
        Value value;
        Pair* next;
        Pair() : next(nullptr) {}
        Pair(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };
    std::vector<Pair*> _data;
    size_t capacity;
    size_t hash(const Key& key) const;
    Pair* search(const Key& key);
public:
    HashTable(size_t size);
    HashTable(size_t size, const std::vector<std::pair<Key, Value>>& values);
    HashTable(const HashTable& other);
    ~HashTable();
    HashTable& operator=(const HashTable& other);
    void print();
    void insert(const Key& key, const Value& value);
    void insert_or_assign(const Key& key, const Value& value);
    bool contains(const Key& key);
    bool erase(const Key& key);
    int count(const Key& key);
};
