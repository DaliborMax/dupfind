#include <gtest/gtest.h>
#include <fstream>

#include "dupfind/types.hpp"
#include "dupfind/grouper.hpp"
#include "dupfind/size.hpp"


using namespace dupfind;

TEST(Grouper, GroupBySizeSeparatesDifferentSizes) {
    const std::vector<FileEntry> files {
        {"a1.txt", 10},
        {"a2.txt", 10},
        {"b1.txt", 20},
    };
    auto groups = group_by_size(files);
    EXPECT_EQ(groups.size(), 2u);
}

TEST(Grouper, FindDuplicatesIdentifiesSameSizeAndHash) {
    std::ofstream("a.txt") << "1234567890";
    std::ofstream("b.txt") << "1234567890";

    const std::vector<FileEntry> files{
        {"a.txt", 10},
        {"b.txt", 10},
    };

    auto duplicates = find_duplicates(files);

    ASSERT_EQ(duplicates.size(), 1u);
    EXPECT_EQ(duplicates[0].paths.size(), 2u);

    std::filesystem::remove("a.txt");
    std::filesystem::remove("b.txt");
}

TEST(Grouper, WastedBytesCalculatesCorrectly) {
    const std::vector<DuplicateGroup> groups{
        {100, 12345, {"path/a1.txt", "path/a2.txt"}},
        {50,  67890, {"path/b1.txt", "path/b2.txt", "path/b3.txt"}},
    };
    EXPECT_EQ(wasted_bytes(groups), 200u);
}