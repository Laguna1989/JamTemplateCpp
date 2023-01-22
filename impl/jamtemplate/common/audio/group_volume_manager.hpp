#ifndef JAMTEMPLATE_GROUP_VOLUME_MANAGER_HPP
#define JAMTEMPLATE_GROUP_VOLUME_MANAGER_HPP

#include <audio/group_volume_setter_interface.hpp>
#include <audio/volume_provider_interface.hpp>
#include <map>

namespace jt {

class GroupVolumeManager : public jt::GroupVolumeGetterInterface,
                           public jt::GroupVolumeSetterInterface {
public:
    float getVolume(std::string const& groupName) const override;
    void setGroupVolume(std::string const& groupName, float volume) override;
    std::vector<std::string> getAllGroupNames() const override;

private:
    mutable std::map<std::string, float> m_volumeGroups;
};

} // namespace jt

#endif // JAMTEMPLATE_GROUP_VOLUME_MANAGER_HPP
