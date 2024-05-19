#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <list>
#include <random>

std::mt19937& getRng() {
    static std::mt19937 rng{ std::random_device{}() };
    return rng;
}

int randomInt() {
    static std::uniform_int_distribution<int> dist(0, 116639);
    return dist(getRng());
}

template<typename Key, typename Value, template<typename...> class Container = std::list>
class HashTable {
    struct Pair {
        Key key;
        Value value;
        Pair(const Key& k, const Value& v) : key(k), value(v) {}
    };

    std::vector<Container<Pair>> _data;
    size_t _size;

    size_t hash(const Key& key) const {
        return key % _data.size();
    }

    void grow() {
        std::vector<Container<Pair>> new_data(_data.size() * 2);
        for (const auto& bucket : _data) {
            for (const auto& pair : bucket) {
                size_t new_index = pair.key % new_data.size();
                new_data[new_index].emplace_back(pair.key, pair.value);
            }
        }
        _data.swap(new_data);
    }

public:
    HashTable(size_t size) : _size(0) {
        if (size == 0)
            throw std::invalid_argument("Size must be greater than 0");
        _data.resize(size);
    }

    HashTable(size_t size, size_t count) : HashTable(size) {
        for (size_t i = 0; i < count; ++i) {
            insert(randomInt(), randomInt());
        }
    }

    HashTable(const HashTable& other) : _size(other._size), _data(other._data.size()) {
        for (const auto& bucket : other._data) {
            for (const auto& pair : bucket) {
                insert(pair.key, pair.value);
            }
        }
    }

    ~HashTable() = default;

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            _data.clear();
            _size = other._size;
            _data.resize(other._data.size());
            for (const auto& bucket : other._data) {
                for (const auto& pair : bucket) {
                    insert(pair.key, pair.value);
                }
            }
        }
        return *this;
    }

    void print() const {
        for (size_t i = 0; i < _data.size(); ++i) {
            if (_data[i].empty()) {
                std::cout << "Bucket " << i << " is empty" << std::endl;
            }
            else {
                for (const auto& pair : _data[i]) {
                    std::cout << "Bucket " << i << ": " << pair.key << ": " << pair.value << std::endl;
                }
            }
        }
    }

    void insert(const Key& key, const Value& value) {
        if (static_cast<double>(_size) / _data.size() > 0.6) {
            grow();
        }
        size_t index = hash(key);
        _data[index].emplace_back(key, value);
        ++_size;
    }

    void insert_or_assign(const Key& key, const Value& value) {
        size_t index = hash(key);
        for (auto& pair : _data[index]) {
            if (pair.key == key) {
                pair.value = value;
                return;
            }
        }
        insert(key, value);
    }

    bool contains(const Key& key) const {
        return search(key) != nullptr;
    }

    Value* search(const Key& key) const {
        size_t index = hash(key);
        for (const auto& pair : _data[index]) {
            if (pair.key == key) {
                return const_cast<Value*>(&pair.value); // const_cast чтобы вернуть неконстантный указатель
            }
        }
        return nullptr;
    }

    bool erase(const Key& key) {
        size_t index = hash(key);
        auto& bucket = _data[index];
        auto it = std::remove_if(bucket.begin(), bucket.end(), [&key](const Pair& pair) {
            return pair.key == key;
            });
        if (it != bucket.end()) {
            bucket.erase(it, bucket.end());
            --_size;
            return true;
        }
        return false;
    }

    int count(const Key& key) const {
        return search(key) ? 1 : 0;
    }

    size_t countCollisions() const {
        size_t collisionCount = 0;
        for (const auto& bucket : _data) {
            if (bucket.size() > 1) {
                collisionCount += bucket.size() - 1;
            }
        }
        return collisionCount;
    }
};
void statistics(const size_t table_size, const size_t count_nodes, const size_t numExperiments) {
    size_t totalCollisions = 0;
    size_t experimentsWithCollisions = 0;
    for (size_t i = 0; i < numExperiments; ++i) {
        HashTable<int, int> hash_table(table_size);
        for (size_t j = 0; j < count_nodes; ++j) {
            hash_table.insert(randomInt(), randomInt());
        }
        size_t collisions = hash_table.countCollisions();
        totalCollisions += collisions;
        if (collisions > 0) {
            ++experimentsWithCollisions;
        }
    }
    std::cout << "size=" << table_size << " experiments with collisions=" << experimentsWithCollisions << "\n";
}
