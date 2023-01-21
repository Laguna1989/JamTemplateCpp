#ifndef JAMTEMPLATE_VOLUME_PROVIDER_INTERFACE_HPP
#define JAMTEMPLATE_VOLUME_PROVIDER_INTERFACE_HPP

#include <string>

namespace jt {
class GroupVolumeGetterInterface {
public:
    virtual float getVolume(std::string const& groupName) const = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_VOLUME_PROVIDER_INTERFACE_HPP
