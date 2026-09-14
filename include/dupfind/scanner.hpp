#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "grouper.hpp"

namespace dupfind
{
    
    struct ScanResult {
        std::vector<FileEntry> files;
        std::vector<std::string> errors;
        std::vector<DuplicateGroup> duplicates;
    };

    

    ScanResult scan_directory(const std::filesystem::path& root);

}