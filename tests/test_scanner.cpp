#include <gtest/gtest.h>
#include <fstream>

#include "dupfind/types.hpp"
#include "dupfind/grouper.hpp"
#include "dupfind/scanner.hpp"



using namespace dupfind;



TEST(Scanner, ScanTheDirectory) {
    FileEntry f1 = {"testDir/a.txt", 0};
    FileEntry f2 = {"testDir/b.txt", 0};

    ScanResult scan = {{f1, f2}, {""}};

    auto groups = scan_directory("testDir/");
    EXPECT_EQ(scan, groups);
}