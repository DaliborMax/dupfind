#include "dupfind/grouper.hpp"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <optional>
#include <unordered_map>
#include <vector>

#include "dupfind/hasher.hpp"
#include "dupfind/size.hpp"

namespace dupfind {

std::vector<std::vector<FileEntry>>
group_by_size(const std::vector<FileEntry>& files) {
    std::vector<std::vector<FileEntry>> groups;

    for (const auto& file : files) {
        bool found = false;

        for (auto& g : groups) {
            if (!g.empty() && g.front().size == file.size) {
                g.push_back(file);
                found = true;
                break;
            }
        }

        if (!found) {
            groups.push_back({file});
        }
    }

    return groups;
}

std::uintmax_t wasted_bytes(const std::vector<DuplicateGroup>& groups) {
    std::uintmax_t wasted_total = 0;

    for (const auto& group : groups) {
        if (group.paths.size() > 1) {
            wasted_total += group.size * (group.paths.size() - 1);
        }
    }

    return wasted_total;
}
std::vector<DuplicateGroup> find_duplicates(
    const std::vector<FileEntry>& files) {

    std::unordered_map<std::uintmax_t, std::vector<FileEntry>> files_by_size;

    for (const auto& file : files) {
        std::error_code ec;

        if (!std::filesystem::is_regular_file(file.path, ec) || ec) {
            continue;
        }

        std::uintmax_t size = file.size;

        if (size == 0) {
            size = get_file_size(file.path);
        }

        FileEntry entry = file;
        entry.size = size;

        files_by_size[size].push_back(std::move(entry));
    }

    constexpr std::size_t max_bytes = 1 << 31;

    std::vector<DuplicateGroup> groups;

    for (const auto& [size, file_list] : files_by_size) {

        // Nema smisla hashirati ako postoji samo jedan fajl te veličine
        if (file_list.size() < 2) {
            continue;
        }

        std::unordered_map<std::uint64_t, std::vector<FileEntry>>
            files_by_hash;

        for (const auto& file : file_list) {
            auto file_hash = hash_file(file.path, max_bytes);

            if (!file_hash) {
                continue;
            }

            files_by_hash[*file_hash].push_back(file);
        }

        for (const auto& [hash, duplicates] : files_by_hash) {
            if (duplicates.size() < 2) {
                continue;
            }

            DuplicateGroup group;
            group.hash = hash;
            group.size = size;

            for (const auto& file : duplicates) {
                group.paths.push_back(file.path);
            }

            groups.push_back(std::move(group));
        }
    }

    return groups;
}

}

