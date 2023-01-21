#ifndef JAMTEMPLATE_GROUP_VOLUME_SETTER_INTERFACE_HPP
#define JAMTEMPLATE_GROUP_VOLUME_SETTER_INTERFACE_HPP

#include <string>

namespace jt {
class GroupVolumeSetterInterface {
public:
    virtual void setGroupVolume(std::string const& groupName, float volume) = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_GROUP_VOLUME_SETTER_INTERFACE_HPP
