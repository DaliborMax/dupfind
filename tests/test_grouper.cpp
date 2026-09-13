 #include <gtest/gtest.h>


#include "dupfind/grouper.hpp" 

TEST(Grouper, GroupBySizeSeparatesDifferentSizes) {
    const std::vector<dupfind::FileEntry> files{
        {"a1.txt", 10},
        {"a2.txt", 10},
        {"b1.txt", 20},
    };
    auto groups = dupfind::group_by_size(files);
    EXPECT_EQ(groups.size(), 2u);
}

TEST(Grouper, FindDuplicatesIdentifiesSameSizeAndHash) {
    const std::vector<dupfind::FileEntry> files{
        {"a.txt", 10},
        {"b.txt", 10},
    };
    auto duplicates = dupfind::find_duplicates(files);
    ASSERT_EQ(duplicates.size(), 1u);
    EXPECT_EQ(duplicates[0].paths.size(), 2u);
}

TEST(Grouper, WastedBytesCalculatesCorrectly) {
    const std::vector<dupfind::DuplicateGroup> groups{
        {100, 12345, {"path/a1.txt", "path/a2.txt"}},
        {50,  67890, {"path/b1.txt", "path/b2.txt", "path/b3.txt"}},
    };
    EXPECT_EQ(dupfind::wasted_bytes(groups), 200u);
}