#include <iostream>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

namespace dupfind
{

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

}