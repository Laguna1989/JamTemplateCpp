#ifndef JAMTEMPLATE_GIT_VERSION_HPP
#define JAMTEMPLATE_GIT_VERSION_HPP

#include <string>

namespace jt {

class BuildInfo {
public:
    static std::string gitCommitHash();
    static std::string gitTagName();
    static std::string timestamp();
};

} // namespace jt

#endif // JAMTEMPLATE_GIT_VERSION_HPP
