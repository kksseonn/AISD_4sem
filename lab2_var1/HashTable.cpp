#include <iostream>
#include <stdexcept>
#include "HashTable.h"

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size) {
	if (size == 0) 
		throw std::invalid_argument("");
	_data.resize(size);
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size, const std::vector<std::pair<Key, Value>>& values) : _data(size) {
	for (const auto& pair : values) {
		insert(pair.first, pair.second);
	}
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable& other) : _data(other._data) {}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable() {}

template<typename Key, typename Value>
HashTable<Key, Value>& HashTable<Key, Value>::operator=(const HashTable& other) {
	if (this != &other) {
		_data = other._data;
	}
	return *this;
}

template<typename Key, typename Value>
void HashTable<Key, Value>::print() {
	for (const auto& pair : _data) {
		if (pair.filled) {
			std::cout << pair.key << ": " << pair.value << std::endl;
		}
	}
}

template<typename Key, typename Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value) {
	size_t index = hash(key) % _data.size();
	if (_data[index].filled) {
		throw std::runtime_error("Table is full");
	}
	_data[index].key = key;
	_data[index].value = value;
	_data[index].filled = true;
}

template<typename Key, typename Value>
void HashTable<Key, Value>::insert_or_assign(const Key& key, const Value& value) {
	Pair* pair = search(key);
	if (pair != nullptr) {
		pair->value = value;
		pair->filled = true;
	}
	else {
		size_t i = 0;
		size_t index;
		do {
			index = (hash(key) + i) % _data.size();
			++i;
		} while (_data[index].filled);
		_data[index].key = key;
		_data[index].value = value;
		_data[index].filled = true;
	}
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::contains(const Key& key) {
	return search(key) != nullptr;
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::erase(const Key& key) {
	Pair* pair = search(key);
	if (!pair) return false;
	pair->filled = false;
	return true;
}

template<typename Key, typename Value>
int HashTable<Key, Value>::count(const Key& key) {
	Pair* pair = search(key);
	return (pair != nullptr && pair->filled) ? 1 : 0;
}

template<typename Key, typename Value>
typename HashTable<Key, Value>::Pair* HashTable<Key, Value>::search(const Key& key) {
	for (size_t i = 0; i < _data.size(); ++i) {
		size_t index = (hash(key) + i) % _data.size();
		if (_data[index].filled && _data[index].key == key) {
			return &_data[index];
		}
	}
	return nullptr;
}
