#pragma once

#include <string>

namespace jt {

class BuildInfo {
public:
    static std::string gitCommitHash();
    static std::string gitTagName();
    static std::string timestamp();
};

} // namespace jt
