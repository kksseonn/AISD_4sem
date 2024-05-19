#include <HashTable/HashTable.h>
#include <gtest/gtest.h>

TEST(HashTableTest, ConstructorTest) {
    HashTable<int, std::string> hash(5);
    ASSERT_FALSE(hash.contains(1));
    ASSERT_FALSE(hash.contains(2));
    ASSERT_FALSE(hash.contains(3));
}

TEST(HashTableTest, InsertAndContains) {
    HashTable<int, std::string> hash(5);
    hash.insert(1, "One");
    hash.insert(2, "Two");
    hash.insert(3, "Three");

    ASSERT_TRUE(hash.contains(1));
    ASSERT_TRUE(hash.contains(2));
    ASSERT_TRUE(hash.contains(3));
    ASSERT_FALSE(hash.contains(4));
}

TEST(HashTableTest, Erase) {
    HashTable<int, std::string> hash(5);
    hash.insert(1, "One");
    hash.insert(2, "Two");
    hash.insert(3, "Three");

    ASSERT_TRUE(hash.contains(2));
    ASSERT_TRUE(hash.erase(2));
    ASSERT_FALSE(hash.contains(2));
}

TEST(HashTableTest, InsertOrAssign) {
    HashTable<int, std::string> hash(5);
    hash.insert_or_assign(1, "One");
    hash.insert_or_assign(2, "Two");
    hash.insert_or_assign(3, "Three");

    ASSERT_EQ(hash.count(1), 1);
    ASSERT_EQ(hash.count(2), 1);
    ASSERT_EQ(hash.count(3), 1);

    hash.insert_or_assign(2, "NewTwo");
    ASSERT_EQ(hash.count(2), 1);
    ASSERT_EQ(*hash.search(2), "NewTwo");
    ASSERT_EQ(hash.count(4), 0);
}

TEST(HashTableTest, CopyConstructor) {
    HashTable<int, std::string> hash1(5);
    hash1.insert(1, "One");
    hash1.insert(2, "Two");
    hash1.insert(3, "Three");

    HashTable<int, std::string> hash2(hash1);

    ASSERT_TRUE(hash2.contains(1));
    ASSERT_TRUE(hash2.contains(2));
    ASSERT_TRUE(hash2.contains(3));
    ASSERT_EQ(*hash2.search(1), "One");
    ASSERT_EQ(*hash2.search(2), "Two");
    ASSERT_EQ(*hash2.search(3), "Three");
}

TEST(HashTableTest, AssignmentOperator) {
    HashTable<int, std::string> hash1(5);
    hash1.insert(1, "One");
    hash1.insert(2, "Two");
    hash1.insert(3, "Three");

    HashTable<int, std::string> hash2(10);
    hash2 = hash1;

    ASSERT_TRUE(hash2.contains(1));
    ASSERT_TRUE(hash2.contains(2));
    ASSERT_TRUE(hash2.contains(3));
    ASSERT_EQ(*hash2.search(1), "One");
    ASSERT_EQ(*hash2.search(2), "Two");
    ASSERT_EQ(*hash2.search(3), "Three");
}

TEST(HashTableTest, Print) {
    HashTable<int, std::string> hash(5);
    hash.insert(1, "One");
    hash.insert(2, "Two");
    hash.insert(3, "Three");

    testing::internal::CaptureStdout();
    hash.print();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_FALSE(output.empty());
}

TEST(HashTableTest, Count) {
    HashTable<int, std::string> hash(5);
    hash.insert(1, "One");
    hash.insert(2, "Two");
    hash.insert(3, "Three");

    ASSERT_EQ(hash.count(1), 1);
    ASSERT_EQ(hash.count(4), 0);
}

TEST(HashTableTest, get_stat) {
    for (size_t i = 25; i < 476; i += 50) {
        statistics(i, 26, 100);
    }
}

