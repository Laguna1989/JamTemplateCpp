#include "system_helper.hpp"
#include <filesystem>

bool jt::SystemHelper::checkForValidFile(std::string const& filename)
{
    return std::filesystem::is_regular_file(filename);
}
