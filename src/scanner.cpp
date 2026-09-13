#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "include/dupfind/scanner.hpp"
#include "include/dupfind/hasher.hpp"
#include "include/dupfind/grouper.hpp"
#include "include/dupfind/size.hpp"

using namespace dupfind;
namespace fs = std::filesystem;

dupfind::ScanResult scan_directory(const std::filesystem::path& root) {
    dupfind::ScanResult result;

    if (!fs::exists(root) || !fs::is_directory(root)) {
        std::cerr << "Directory does not exist or is not a directory.\n";
        return result; 
    }

    

    

    

    return result;
}
