#include <cstdint>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

#include "dupfind/grouper.hpp"
#include "dupfind/hasher.hpp"
#include "dupfind/scanner.hpp"

namespace fs = std::filesystem;
using namespace dupfind;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_folder>\n";
        return 1;
    }

    fs::path target_path = argv[1];

    if (!fs::exists(target_path) || !fs::is_directory(target_path)) {
        std::cerr << "Error: Path does not exist or is not a directory!\n";
        return 1;
    }

    std::cout << "Scanning the directory...\n";

    ScanResult files = scan_directory(target_path);

    if (!files.errors.empty()) {
        std::cerr << "Encountered " << files.errors.size()
                  << " error(s) while scanning.\n";
    }

    std::vector<DuplicateGroup> duplicates = find_duplicates(files.files);

    std::uintmax_t total_wasted = wasted_bytes(duplicates);

    std::cout << "\nDuplicates found:\n";
    for (const auto& group : duplicates) {
        std::cout << "File size: " << group.size
                  << " bytes (Hash: " << group.hash << ")\n";
        for (const auto& p : group.paths) {
            std::cout << "  - " << p.string() << "\n";
        }
    }

    std::cout << "Total wasted space due to duplicates: "
              << total_wasted << " bytes.\n";

    /* std::ofstream("a.txt") << "1234567890";
    std::ofstream("b.txt") << "1234567890";
    
    std::vector<dupfind::FileEntry> _files {
        {"a.txt", 10},
        {"b.txt", 10},
    };

    std::vector<std::string> errors;

    ScanResult scan{_files, errors};

    std::vector<DuplicateGroup> scan_result = find_duplicates(_files);

    for (size_t i = 0; i < scan_result.size(); ++i) {
        for (size_t j = 0; j < scan_result[i].paths.size(); ++j) {

            std::cout << scan_result[i].paths[j] << std::endl;
        }
    } */

    FileEntry f1 = {"testDir/a.txt", 0};
    FileEntry f2 = {"testDir/b.txt", 0};

    ScanResult scan = {{f1, f2}, {""}};

    for (size_t i = 0; i < scan.files.size(); ++i) {
        std::cout << scan.files[i].path << std::endl;
    }

    auto groups = scan_directory("testDir/");
    std::cout << "Should work on test" << std::endl;
    for (size_t i = 0; i < groups.files.size(); ++i) {
        std::cout << groups.files[i].path << std::endl;
        std::cout << groups.files[i].size << std::endl;
        
    }
    for (int i = 0; i < groups.errors.size(); i++) {
        std::cout << "here";
        std::cout << groups.errors[i] << std::endl;
    }
    
    return 0;
}