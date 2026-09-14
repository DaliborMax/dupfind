#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace dupfind {

struct FileEntry {
    std::filesystem::path path;
    std::uintmax_t size = 0;
};

struct DuplicateGroup {
    std::uintmax_t size = 0;
    std::uint64_t hash = 0;
    std::vector<std::filesystem::path> paths;
};

}