#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace dupfind
{

struct FileEntry {
    std::filesystem::path path;
    std::uintmax_t size;
};

struct ScanOptions {
    bool follow_symlinks = false;
    std::uintmax_t min_size = 1;
};

struct ScanResult {
    std::vector<FileEntry> files;
    std::vector<std::string> errors;
};

ScanResult scan_directory(const std::filesystem::path& root, const ScanOptions& options);

}