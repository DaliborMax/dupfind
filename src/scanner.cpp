#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "include/dupfind/scanner.hpp"
#include "include/dupfind/hasher.hpp"

using namespace dupfind;
namespace fs = std::filesystem;

dupfind::ScanResult scan_directory(const std::filesystem::path& root, const ScanOptions& options) {
    dupfind::ScanResult result;

    if (!fs::exists(root) || !fs::is_directory(root)) {
        std::cerr << "Directory does not exist or is not a directory.\n";
        return result; 
    }

    std::unordered_map<std::uintmax_t, std::vector<FileEntry>> files_by_size;

    for (const auto& entry : fs::recursive_directory_iterator(root)) {

        if (fs::is_regular_file(entry.path())) {
            FileEntry file;
            file.path = entry.path();
            
            std::uintmax_t size = fs::file_size(entry.path());
            files_by_size[size].push_back(file);
        }
    }

    std::unordered_map<std::optional<std::uint64_t>, std::vector<FileEntry>> files_by_hash;

    size_t max_bytes = 1 << 31;

    for (const auto& [size, file_list] : files_by_size) {

        if (file_list.size() < 2) {
            continue;
        }
        for (const auto& file : file_list) {
            std::optional<std::uint64_t> file_hash = hash_file(file.path, max_bytes); 
            files_by_hash[file_hash].push_back(file);
        }
    }

    for (const auto& [hash, duplicates] : files_by_hash) {
        if (duplicates.size() > 1) {
            std::cout << "Pronadjeni duplikati za hes: " << hash.value() << "\n";
            for (const auto& f : duplicates) {
                std::cout << "  - " << f.path.string() << "\n";
            }
        }
    }

    return result;
}
