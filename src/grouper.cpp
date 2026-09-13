#include "include/dupfind/grouper.hpp"

#include <iostream>
#include <unordered_map>

using namespace dupfind;
namespace fs = std::filesystem;

std::uintmax_t get_file_size(fs::path path) {
    
    try {

        if (fs::exists(path) && fs::is_regular_file(path)) {
            std::uintmax_t size = fs::file_size(path);
            return size;
        } else {
            std::cout << "File does not exists or it is not regular file!" << std::endl;
        }

    } catch(const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}

std::vector<std::vector<FileEntry>> dupfind::group_by_size(const std::vector<FileEntry>& files) {

    std::vector<std::vector<FileEntry>> group;

    for (size_t i = 0; i < files.size(); ++i) {
        
        bool found = false;
        for (size_t j = 0; j < group.size(); j++) {

            if (get_file_size(files[i].path) == get_file_size(group[j][0].path)) {
                group[j].push_back(files[i]);
                found = true;
            }
        }
        if (!found) {
            group.push_back({files[i]});
        }
    }

    return group;
}