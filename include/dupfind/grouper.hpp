#pragma once

#include <cstdint>
#include <vector>

#include "dupfind/types.hpp"

namespace dupfind {

std::vector<std::vector<FileEntry>>
group_by_size(const std::vector<FileEntry>& files);

std::uintmax_t wasted_bytes(const std::vector<DuplicateGroup>& groups);

std::vector<DuplicateGroup>
find_duplicates(const std::vector<FileEntry>& files);

}   