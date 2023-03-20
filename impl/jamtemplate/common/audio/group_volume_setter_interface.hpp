#ifndef JAMTEMPLATE_GROUP_VOLUME_SETTER_INTERFACE_HPP
#define JAMTEMPLATE_GROUP_VOLUME_SETTER_INTERFACE_HPP

#include <string>
#include <vector>

namespace jt {
class GroupVolumeSetterInterface {
public:
    /// Set volume for a group
    /// \param groupName name to identify the volume group
    /// \param volume new volume for this specific group
    virtual void setGroupVolume(std::string const& groupName, float volume) = 0;

    /// Get all group names
    /// \return vector of volume group names
    virtual std::vector<std::string> getAllGroupNames() const = 0;

    virtual ~GroupVolumeSetterInterface() = default;

    // no copy, no move. Avoid slicing.
    GroupVolumeSetterInterface(const GroupVolumeSetterInterface&) = delete;
    GroupVolumeSetterInterface(GroupVolumeSetterInterface&&) = delete;
    GroupVolumeSetterInterface& operator=(const GroupVolumeSetterInterface&) = delete;
    GroupVolumeSetterInterface& operator=(GroupVolumeSetterInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    GroupVolumeSetterInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_GROUP_VOLUME_SETTER_INTERFACE_HPP
