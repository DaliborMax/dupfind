#include "dupfind/scanner.hpp"

#include <filesystem>
#include <iostream>

namespace dupfind {

ScanResult scan_directory(const std::filesystem::path& root) {
    ScanResult result;

    std::error_code ec;
    if (!std::filesystem::exists(root, ec) || ec ||
        !std::filesystem::is_directory(root, ec) || ec) {
        std::cerr << "Directory does not exist or is not a directory.\n";
        return result;
    }

    for (auto it = std::filesystem::recursive_directory_iterator(
             root, std::filesystem::directory_options::skip_permission_denied, ec);
         it != std::filesystem::recursive_directory_iterator();
         it.increment(ec)) {

        if (ec) {
            result.errors.push_back(ec.message());
            ec.clear();
            continue;
        }

        const auto& entry = *it;

        std::error_code entry_ec;
        if (!entry.is_regular_file(entry_ec) || entry_ec) {
            continue;
        }

        FileEntry file;
        file.path = entry.path();
        file.size = entry.file_size(entry_ec);
        if (entry_ec) {
            result.errors.push_back(entry_ec.message());
            continue;
        }

        result.files.push_back(std::move(file));
    }
    
    for (size_t i = 0; i < result.files.size(); ++i) {
        std::cout << "Path: " << result.files[i].path << "\n";
        std::cout << "Size: " << result.files[i].size << "\n";
    }

    return result;
}

} // namespace dupfind