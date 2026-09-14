#include <gtest/gtest.h>
#include <fstream>
#include <algorithm>

#include "dupfind/types.hpp"
#include "dupfind/grouper.hpp"
#include "dupfind/scanner.hpp"



using namespace dupfind;

TEST(Scanner, ScanTheDirectory) {
    FileEntry f1 = {"../../tests/testDir/b.txt", 0};
    FileEntry f2 = {"../../tests/testDir/a.txt", 0};

    ScanResult expected = {{f1, f2}, {}};

    auto actual = scan_directory("../../tests/testDir/");

    auto sort_files = [](auto& files) {
        std::sort(files.begin(), files.end(),
                  [](const FileEntry& a, const FileEntry& b) {
                      return a.path < b.path;
                  });
    };

    sort_files(expected.files);
    sort_files(actual.files);

    EXPECT_EQ(expected.files, actual.files);
    EXPECT_EQ(expected.errors, actual.errors);
}