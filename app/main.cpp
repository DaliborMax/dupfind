#include <iostream>
#include <filesystem>
#include <vector>

#include "include/dupfind/grouper.hpp"
#include "include/dupfind/scanner.hpp"
#include "include/dupfind/hasher.hpp"

namespace fs = std::filesystem;
using namespace dupfind;


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << "<path_to_folder>\n";
        return 1;
    }

    fs::path target_path = argv[1];

    if (!fs::exists(target_path) || !fs::is_directory(target_path)) {
        std::cerr << "Error: Path does not exists or it is not directory!\n";
    }

    std::cout << "Scanning the directory..." << std::endl;

    dupfind::ScanResult files = dupfind::scan_directory(target_path);

    std::vector<dupfind::DuplicateGroup> duplicates = dupfind::find_duplicates(files.files);

    std::uintmax_t total_wasted = dupfind::wasted_bytes(duplicates);

    std::cout << "\nDuplicates found:\n";
    for (const auto& group : duplicates) {
        std::cout << "File size: " << group.size << " bytes (Hash: " << group.hash << ")\n";
        for (const auto& p : group.paths) {
            std::cout << "  - " << p << "\n";
        }
        std::cout << "----------------------------------------\n";
    }

    std::cout << "Total wasted space due to duplicates: " << total_wasted << " bajtova.\n";


    return 0;
}