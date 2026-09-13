#include <gtest/gtest.h>

#include "dupfind/hasher.hpp"
#include "dupfind/grouper.hpp"

using namespace dupfind;

TEST(Hasher, SameBytesProduceSameHash) {
    const std::string a = "matf";
    const std::string b = "matf";
    EXPECT_EQ(dupfind::hash_bytes(a.data(), a.size()),
              dupfind::hash_bytes(b.data(), b.size()));
}

TEST(Hasher, DifferentBytesProduceDifferentHash) {
    const std::string a = "matf";
    const std::string b = "mafl";
    EXPECT_NE(dupfind::hash_bytes(a.data(), a.size()),
              dupfind::hash_bytes(b.data(), b.size()));
}

TEST(Hasher, MissingFileReturnsNullopt) {
    EXPECT_FALSE(dupfind::hash_file("/nepostojeci/put/fajl.bin").has_value());
}

TEST(Grouper, UniqueSizesProduceNoDuplicates) {
    const std::vector<dupfind::FileEntry> files{
        {"a.txt", 10},
        {"b.txt", 20},
        {"c.txt", 30},
    };
    EXPECT_TRUE(dupfind::find_duplicates(files).empty());
}