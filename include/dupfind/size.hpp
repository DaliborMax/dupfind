#pragma once

#include <cstdint>
#include <filesystem>

namespace dupfind {

    std::uintmax_t get_file_size(const std::filesystem::path& path);

}