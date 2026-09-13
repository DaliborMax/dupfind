#include "include/dupfind/grouper.hpp"

#include <iostream>
#include <unordered_map>
#include <optional>

#include "include/dupfind/size.hpp"
#include "include/dupfind/hasher.hpp"

using namespace dupfind;
namespace fs = std::filesystem;


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

std::uintmax_t wasted_bytes(const std::vector<DuplicateGroup>& groups) {

    std::uintmax_t wasted_total = 0;
    for (const auto& group : groups) {

        wasted_total += group.size * (group.paths.size() - 1);
    }

    return wasted_total;
}


std::vector<DuplicateGroup> find_duplicates(const std::vector<FileEntry>& files) {

    std::unordered_map<std::uintmax_t, std::vector<FileEntry>> files_by_size;

    std::vector<fs::path> file_paths;
    for (const auto& file : files) {
        file_paths.push_back(file.path);
    }
    for (const auto& entry : file_paths) {


        if (fs::is_regular_file(entry)) {
            FileEntry file;
            file.path = entry;
            
            std::uintmax_t size = fs::file_size(entry);
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

    std::vector<DuplicateGroup> groups;
    for (const auto& [hash, duplicates] : files_by_hash) {
        if (duplicates.size() > 1) {
            
            DuplicateGroup group;

            for (const auto& f : duplicates) {
                std::cout << " - " << f.path.string() << "\n";
                group.paths.push_back(f.path);
                group.hash = hash.value();
                group.size = get_file_size(f.path);
            }
            groups.push_back(group);
        }
    }
}
