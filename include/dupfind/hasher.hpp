#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>

namespace dupfind {

inline constexpr std::uint64_t fnv_offset_basis = 14695981039346656037ULL;
inline constexpr std::uint64_t fnv_prime = 1099511628211ULL;

std::uint64_t hash_bytes(const void* data, std::size_t size, std::uint64_t seed = fnv_offset_basis);

std::optional<std::uint64_t> hash_file(const std::filesystem::path& path, std::size_t max_bytes = 0);

std::string to_hex(std::uint64_t value);

}