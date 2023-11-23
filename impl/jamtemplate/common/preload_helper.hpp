#ifndef JAMTEMPLATE_PRELOAD_HELPER_HPP
#define JAMTEMPLATE_PRELOAD_HELPER_HPP

#include <filesystem>
#include <string>

namespace jt {
namespace PreloadHelper {

// define a concept to avoid stupid duck typing via Templates
template <typename T>
concept HasGet = requires(T & t, std::string const& fileName)
{
    t.get(fileName);
};

void preloadAllFrom(HasGet auto& cache, std::string const& folder, std::string const& extension,
    bool recursive = true)
{
    if (!std::filesystem::is_directory(folder)) {
        throw std::invalid_argument { "folder '" + folder + "' is not a directory" };
    }
    auto ext = extension;
    if (!ext.starts_with(".")) {
        ext = "." + ext;
    }

    auto const fun = [&](auto f) {
        std::string const path = f.path().string();
        if (path.ends_with(extension)) {
            cache.get(path);
        }
    };

    if (recursive) {
        for (auto file : std::filesystem::recursive_directory_iterator { folder }) {
            fun(file);
        }
    } else {
        for (auto file : std::filesystem::directory_iterator { folder }) {
            fun(file);
        }
    }
}

} // namespace PreloadHelper
} // namespace jt

#endif // JAMTEMPLATE_PRELOAD_HELPER_HPP
