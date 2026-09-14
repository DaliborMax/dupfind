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

        bool operator== (const ScanResult& s) const {
            return files.data() == s.files.data() && errors.data() == s.errors.data();
        }
    };

    

    ScanResult scan_directory(const std::filesystem::path& root);

}