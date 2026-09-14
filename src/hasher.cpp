#include "dupfind/hasher.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

namespace dupfind {

std::uint64_t hash_bytes(const void* data, std::size_t size, std::uint64_t seed) {
    std::uint64_t hash = seed;

    const std::uint8_t* bytes = static_cast<const std::uint8_t*>(data);

    for (std::size_t i = 0; i < size; ++i) {
        hash ^= static_cast<std::uint64_t>(bytes[i]);
        hash *= fnv_prime;
    }

    return hash;
}

std::optional<std::uint64_t> hash_file(const std::filesystem::path& path,
                                       std::size_t max_bytes) {
    std::error_code ec;
    if (!std::filesystem::exists(path, ec) || ec) {
        return std::nullopt;
    }

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return std::nullopt;
    }

    std::uint64_t current_hash = fnv_offset_basis;

    constexpr std::size_t buffer_size = 8192;
    std::vector<char> buffer(buffer_size);

    std::size_t total_bytes_read = 0;

    while (file) {
        std::size_t bytes_to_read = buffer_size;

        if (max_bytes > 0) {
            if (total_bytes_read >= max_bytes) {
                break;
            }
            bytes_to_read = std::min(buffer_size, max_bytes - total_bytes_read);
        }

        file.read(buffer.data(), static_cast<std::streamsize>(bytes_to_read));
        std::size_t bytes_read = static_cast<std::size_t>(file.gcount());

        if (bytes_read == 0) {
            break;
        }

        current_hash = hash_bytes(buffer.data(), bytes_read, current_hash);
        total_bytes_read += bytes_read;
    }

    return current_hash;
}

}