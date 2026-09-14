#include "dupfind/size.hpp"

#include <system_error>

namespace dupfind {

std::uintmax_t get_file_size(const std::filesystem::path& path) {
    std::error_code ec;
    auto size = std::filesystem::file_size(path, ec);
    if (ec) {
        return 0;
    }
    return size;
}

}