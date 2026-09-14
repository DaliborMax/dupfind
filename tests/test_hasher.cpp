#include <gtest/gtest.h>

#include "dupfind/types.hpp"
#include "dupfind/size.hpp"
#include "dupfind/hasher.hpp"
#include "dupfind/grouper.hpp"

using namespace dupfind;

TEST(Hasher, SameBytesProduceSameHash) {
    const std::string a = "matf";
    const std::string b = "matf";
    EXPECT_EQ(hash_bytes(a.data(), a.size()),
              hash_bytes(b.data(), b.size()));
}

TEST(Hasher, DifferentBytesProduceDifferentHash) {
    const std::string a = "matf";
    const std::string b = "mafl";
    EXPECT_NE(hash_bytes(a.data(), a.size()),
              hash_bytes(b.data(), b.size()));
}

TEST(Hasher, MissingFileReturnsNullopt) {
    EXPECT_FALSE(hash_file("/not-exists/path/file.bin").has_value());
}

TEST(Grouper, UniqueSizesProduceNoDuplicates) {
    const std::vector<FileEntry> files{
        {"a.txt", 10},
        {"b.txt", 20},
        {"c.txt", 30},
    };
    EXPECT_TRUE(find_duplicates(files).empty());
}