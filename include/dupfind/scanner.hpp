#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "grouper.hpp"

namespace dupfind
{

    struct ScanResult {
        std::vector<dupfind::FileEntry> files;
        std::vector<std::string> errors;
        std::vector<dupfind::DuplicateGroup> duplicates;
    };

    struct FileEntry {
        std::filesystem::path path;
        std::uintmax_t size;
    };

    ScanResult scan_directory(const std::filesystem::path& root);

}