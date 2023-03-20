#ifndef JAMTEMPLATE_GROUP_VOLUME_GETTER_INTERFACE_HPP
#define JAMTEMPLATE_GROUP_VOLUME_GETTER_INTERFACE_HPP

#include <string>

namespace jt {
class GroupVolumeGetterInterface {
public:
    /// Get volume for a group
    /// \param groupName name to identify the volume group
    /// \return volume for this specific group
    virtual float getVolume(std::string const& groupName) const = 0;

    virtual ~GroupVolumeGetterInterface() = default;

    // no copy, no move
    GroupVolumeGetterInterface(const GroupVolumeGetterInterface&) = delete;
    GroupVolumeGetterInterface(GroupVolumeGetterInterface&&) = delete;
    GroupVolumeGetterInterface& operator=(const GroupVolumeGetterInterface&) = delete;
    GroupVolumeGetterInterface& operator=(GroupVolumeGetterInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    GroupVolumeGetterInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_GROUP_VOLUME_GETTER_INTERFACE_HPP
