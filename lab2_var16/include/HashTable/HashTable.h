#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>


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

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % capacity;
    }

    Pair* search(const Key& key) {
        size_t index = hash(key);
        Pair* current = _data[index];
        while (current) {
            if (current->key == key)
                return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    HashTable(size_t size) : capacity(size) {
        if (size == 0)
            throw std::invalid_argument("Size must be greater than 0");
        _data.resize(size);
    }

    HashTable(size_t size, const std::vector<std::pair<Key, Value>>& values) : HashTable(size) {
        for (const auto& pair : values) {
            insert(pair.first, pair.second);
        }
    }

    HashTable(const HashTable& other) : capacity(other.capacity), _data(other._data.size()) {
        for (size_t i = 0; i < other._data.size(); ++i) {
            Pair* current = other._data[i];
            while (current) {
                insert(current->key, current->value);
                current = current->next;
            }
        }
    }

    ~HashTable() {
        for (size_t i = 0; i < _data.size(); ++i) {
            Pair* current = _data[i];
            while (current) {
                Pair* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    HashTable& operator=(const HashTable& other) {
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

    void print() {
        for (size_t i = 0; i < _data.size(); ++i) {
            Pair* current = _data[i];
            while (current) {
                std::cout << current->key << ": " << current->value << std::endl;
                current = current->next;
            }
        }
    }

    void insert(const Key& key, const Value& value) {
        size_t index = hash(key);
        Pair* newNode = new Pair(key, value);
        newNode->next = _data[index];
        _data[index] = newNode;
    }

    void insert_or_assign(const Key& key, const Value& value) {
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

    bool contains(const Key& key) {
        return search(key) != nullptr;
    }

    bool erase(const Key& key) {
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

    int count(const Key& key) {
        Pair* current = search(key);
        return current ? 1 : 0;
    }

    size_t countCollisions() const {
        size_t collisionCount = 0;
        for (const auto& bucket : _data) {
            if (bucket) {
                size_t bucketSize = 0;
                Pair* current = bucket;
                while (current->next) {
                    ++bucketSize;
                    current = current->next;
                }
                if (bucketSize > 0)
                    ++collisionCount;
            }
        }
        return collisionCount;
    }
};

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

void statistics(const size_t table_size, const size_t count_nodes, const size_t numExperiments) {
    size_t sum = 0;
    for (size_t i = 0; i < numExperiments; ++i) {
        HashTable<int, int> hash_table(table_size);
        for (size_t j = 0; j < count_nodes; ++j) {
            hash_table.insert(lcg(), lcg());
        }
        sum += hash_table.countCollisions();
    }
    std::cout << "size=" << table_size << "    average count of collisions=" << sum / numExperiments << "\n";
}