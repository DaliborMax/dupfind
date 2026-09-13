#include <iostream>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

namespace dupfind
{

    std::uintmax_t get_file_size(fs::path path);

}
