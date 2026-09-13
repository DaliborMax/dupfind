#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

#include "scanner.hpp"

namespace dupfind {

struct DuplicateGroup {
    std::uintmax_t size;
    std::uint64_t hash;
    std::vector<std::filesystem::path> paths;
};

std::vector<std::vector<FileEntry>> group_by_size(const std::vector<FileEntry>& files);

std::vector<DuplicateGroup> find_duplicates(const std::vector<FileEntry>& files);

std::uintmax_t wasted_bytes(const std::vector<DuplicateGroup>& groups);

}