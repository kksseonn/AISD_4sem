#include <iostream>
#include <stdexcept>
#include "HashTable.h"


template<typename Key, typename Value>
size_t HashTable<Key, Value>::hash(const Key& key) const {
	return std::hash<Key>{}(key) % capacity;
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size) : capacity(size) {
	if (size == 0)
		throw std::invalid_argument("Size must be greater than 0");
	_data.resize(size, nullptr);
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size, const std::vector<std::pair<Key, Value>>& values) : HashTable(size) {
	for (const auto& pair : values) {
		insert(pair.first, pair.second);
	}
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable& other) : capacity(other.capacity), _data(other._data.size()) {
	for (size_t i = 0; i < other._data.size(); ++i) {
		Pair* current = other._data[i];
		while (current) {
			insert(current->key, current->value);
			current = current->next;
		}
	}
}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable() {
	for (size_t i = 0; i < _data.size(); ++i) {
		Pair* current = _data[i];
		while (current) {
			Pair* temp = current;
			current = current->next;
			delete temp;
		}
	}
}

template<typename Key, typename Value>
HashTable<Key, Value>& HashTable<Key, Value>::operator=(const HashTable& other) {
	if (this != &other) {
		capacity = other.capacity;
		_data.clear();
		_data.resize(other._data.size());
		for (size_t i = 0; i < other._data.size(); ++i) {
			Pair* current = other._data[i];
			while (current) {
				insert(current->key, current->value);
				current = current->next;
			}
		}
	}
	return *this;
}

template<typename Key, typename Value>
void HashTable<Key, Value>::print() {
	for (size_t i = 0; i < _data.size(); ++i) {
		Pair* current = _data[i];
		while (current) {
			std::cout << current->key << ": " << current->value << std::endl;
			current = current->next;
		}
	}
}

template<typename Key, typename Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value) {
	size_t index = hash(key);
	Pair* newNode = new Pair(key, value);
	newNode->next = _data[index];
	_data[index] = newNode;
}

template<typename Key, typename Value>
void HashTable<Key, Value>::insert_or_assign(const Key& key, const Value& value) {
	size_t index = hash(key);
	Pair* current = _data[index];
	while (current) {
		if (current->key == key) {
			current->value = value;
			return;
		}
		current = current->next;
	}
	insert(key, value);
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::contains(const Key& key) {
	return search(key) != nullptr;
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::erase(const Key& key) {
	size_t index = hash(key);
	Pair* current = _data[index];
	Pair* prev = nullptr;
	while (current) {
		if (current->key == key) {
			if (prev)
				prev->next = current->next;
			else
				_data[index] = current->next;
			delete current;
			return true;
		}
		prev = current;
		current = current->next;
	}
	return false;
}

template<typename Key, typename Value>
int HashTable<Key, Value>::count(const Key& key) {
	Pair* current = search(key);
	return current ? 1 : 0;
}

template<typename Key, typename Value>
typename HashTable<Key, Value>::Pair* HashTable<Key, Value>::search(const Key& key) {
	size_t index = hash(key);
	Pair* current = _data[index];
	while (current) {
		if (current->key == key)
			return current;
		current = current->next;
	}
	return nullptr;
}
