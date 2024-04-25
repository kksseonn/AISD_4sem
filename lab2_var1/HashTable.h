#pragma once
#include <vector>
#include <iostream>

template<typename Key, typename Value>
class HashTable {
	struct Pair {
		Key key;
		Value value;
		bool filled;
		Pair() : filled(false) {}
	};
	std::vector<Pair> _data;
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
private:
	Pair* search(const Key& key);
};