#include <cstdint>
#include <filesystem>
#include <iostream>
#include <vector>

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

    return 0;
}